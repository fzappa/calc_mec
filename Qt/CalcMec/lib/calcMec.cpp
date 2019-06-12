#include "calcMec.hpp"
#include <boost/math/constants/constants.hpp>
#include <algorithm>  //lambda
#include <cmath>
#include <iostream>

#define MAXIT 10e4
#define ERRO 10e-6

// http://boost-sandbox.sourceforge.net/libs/math_constants/doc/html/
typedef boost::math::policies::policy<boost::math::policies::digits2<15>> ndigitos;

const double PI    = boost::math::constants::pi<double, ndigitos>();
const double RAIZ3 = boost::math::constants::root_three<double, ndigitos>();

// ---- INICIO --- Calculo da maxima corrente nos cabos para-raios ---//

// Para EHS considera-se tmax de 370C
// tcurto geralmente em 30 ciclos (0.5s)
double iEHS(const conf &caso, const double &tcurto)
{

    double A0{8.88e3 * caso.secao};
    double A1{sqrt((1.0 / tcurto) * log(1 + 0.0031 * (caso.tmax - caso.tamb)))};

    return A0 * A1;
}

// Para Alumoweld considera-se tmax de 370C
// tcurto geralmente em 30 ciclos (0.5s)
double iAlumoweld(const conf &caso, const double &tcurto)
{

    double A0{1.03e4 * caso.secao};
    double A1{sqrt((1.0 / tcurto) * log(1 + 0.0036 * (caso.tmax - caso.tamb)))};

    return A0 * A1;
}

// Para ACRS considera-se tmax de 170C
// tcurto geralmente em 30 ciclos (0.5s)
double iACRS(const conf &caso, const double &tcurto)
{

    double A0{1.50e4 * caso.secao};
    double A1{sqrt((1.0 / tcurto) * log(1 + 0.0040 * (caso.tmax - caso.tamb)))};

    return A0 * A1;
}

// ---- FIM --- Calculo da maxima corrente nos cabos para-raios ---//

/**
    Função para calculo da altura de segurança
    @param V: Nível de tensão em V
    @param MIN(caso.hA,caso.hB): Altura do ponto mais baixo dos condutores em
   metros
    @return Altura de segurança em metros
*/
double alturaSeg(const conf &caso)
{
    using namespace boost::math::constants;
    return MIN(caso.hA, caso.hB) + 0.01 * (((caso.tensao / 1000.0) / RAIZ3) - 50.0);
}

/**
    Função que calcula a flecha de um cabo
        Autor: Alan Franco

        @param MASSA Massa do cabo [kg]
        @param VAO Comprimento do vao [m]
        @param T0 Tração inicial [N]
        @param PHI Angulo de balanço [graus]
        @param VENTO_MED Vento medio [m/s]
        @return Retorna um vector na forma: (Flecha, Balanco, Flecha Vento,
   Esforco lateral)

        #%%%%%%%%%%%%%%%%%%%%%% Equações %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        #%%% (Livro: Projetos Mecânicos das Linhas Aéreas de Transmissão)
        #%%% Labegalini, Fuchs, Almeida. Pg 21, 2ª edição
        #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/
std::unique_ptr<std::vector<double>> forcasExternas(const conf &caso)
{

    std::unique_ptr<std::vector<double>> ptrSaida{new std::vector<double>(4)};

    // 2.3.3 - Determinacao da pressao do vento - Pagina 116 - Fuchs - Projetos
    // Mecanicos
    double rho, altitude, temp;
    altitude = 0.0;        // nivel do mar [m]
    temp     = caso.tamb;  // temperatura ambiente [graus C]

    // Massa especifica do ar EQ 2.10  - Pagina 116 - Fuchs - Projetos Mecanicos
    rho = (1.293 / (1 + 0.00367 * temp)) *
          ((16000 + 64 * temp - altitude) / (16000 + 64 * temp + altitude));  // [kg/m^3]

    // Pressao que o vento exerce EQ 2.9  - Pagina 116 - Fuchs - Projetos
    // Mecanicos
    double q0, ventomed;
    ventomed = caso.ventomed;                        // velocidade do vento do projeto [m/s]
    q0       = (0.5) * rho * (ventomed * ventomed);  // [N/m^2]

    // Forca do vento exerce EQ 3.59  - Pagina 195 - Fuchs - Projetos Mecanicos
    double fv, d;
    d  = caso.phi;  // diametro do condutor [m]
    fv = q0 * d;    // forca do vento [kgf/m]

    // Pressao do vento EQ 3.61  - Pagina 196 - Fuchs - Projetos Mecanicos
    double pr, p;
    p  = caso.massa;                 // peso proprio do condutor
    pr = sqrt((p * p) + (fv * fv));  // peso virtual do cabo devido a pressao do vento

    // Nova flecha devido ao vento EQ 3.62  - Pagina 196 - Fuchs - Projetos
    // Mecanicos
    double S = caso.cvao;
    double flechaNova;
    const double T0{caso.trup * caso.eds};
    const double T02{(T0 / pr)};
    flechaNova = (pr * (S * S)) / (8 * T02);  // nova flecha

    // TODO -> Pagina 202

    //    flecha = (T0 / caso.massa) * (cosh((caso.cvao * caso.massa) / (2 * T0))
    //    - 1);  // flecha [m] forv   = (caso.phi / 2.0) * (caso.ventomed *
    //    caso.ventomed);     // forca do vento [kgf] bal    = atan(forv /
    //    caso.massa) * (180 / M_PI);                 // angulo de balaco [graus]
    //    foreq  = pow(((caso.massa * caso.massa) + (forv * forv)), 0.5);  //
    //    forca equivalente [kgf] flev   = (foreq * (caso.cvao * caso.cvao)) / (8
    //    * T0);           // flecha devido ao vento [m] esfl   = ((foreq *
    //    caso.cvao) / 2.0); // esforco lateral [kgf]

    ptrSaida->at(0) = flechaNova;
    ptrSaida->at(1) = 0.0;
    ptrSaida->at(2) = 0.0;
    ptrSaida->at(3) = 0.0;

    return ptrSaida;
}

// Resolve a catenaria
std::unique_ptr<Eigen::MatrixXd> catenaria(const conf &caso, double &LCABO, double &LFLECHA,
                                           double &FLECHA_X, double &FLECHA_Y)
{

    // Eigen Multithead
    Eigen::setNbThreads(6);

    const double hmax{MAX(caso.hA, caso.hB)};
    const double hmin{MIN(caso.hA, caso.hB)};

    const double T0{caso.trup * caso.eds};
    const double p{caso.massa};
    const double C1{(T0 / p)};

    const double H{abs(hmax - hmin)};
    const double S{caso.cvao};

    // Calcula do comprimento da flecha
    LFLECHA = (S * S) / (8 * C1);  // EQ 3.46  - Pagina 174 - Fuchs - Projetos Mecanicos

    // Comprimento do cabo
    LCABO = sqrt((H * H) +
                 ((4 * (C1 * C1)) *
                  (sinh(S / (2 * C1)) *
                   sinh(S / (2 * C1)))));  // EQ 3.38  - Pagina 171 - Fuchs - Projetos Mecanicos

    //------------ Parte 2 - Calculo da catenaria --------------//

    // Utiliza o metodo Newton–Raphson para calcular (x, y) que cubra o
    // comprimento do cabo de acordo com as caracteristicas do vao. Discussao:
    // http://mathhelpforum.com/calculus/96398-catenary-cable-different-heights.html
    // expressao lambda para f(x)
    auto f = [&](double x) -> double {
        return (2.0 * x * sinh(S / (2.0 * x)) - sqrt((LCABO * LCABO) - (H * H)));
    };

    // expressao lambda para df(x)
    auto df = [&](double x) -> double {
        return (2.0 * sinh(S / (2.0 * x)) - S * cosh(S / (2.0 * x)) / x);
    };

    double x0 = 1;
    double x  = 0.0;
    x         = NewtonRaphson(f, df, x0);

    const double H2{caso.hB - caso.hA};
    double x1 = 0.5 * (x * log((LCABO + H2) / (LCABO - H2)) - S);

    double k = x1 - (-S / 2.0);
    double m = caso.hA - x * cosh(x1 / x);

    std::unique_ptr<Eigen::MatrixXd> ptrMxy{new Eigen::MatrixXd};

    int i = 0;
    for (double px = (-S / 2.0); px <= (S / 2.0); px += (S / caso.nl), ++i) {
        ptrMxy->resize(i + 1, 2);
    }

    ptrMxy->setZero();

    i = 0;
    for (double px = (-S / 2.0); px <= (S / 2.0); px += (S / caso.nl), i++) {
        (*ptrMxy)(i, 0) = px;
        (*ptrMxy)(i, 1) = x * cosh((px + k) / x) + m;
    }

    int r, c;  // salvar as coordenadas de posicao da tabela

    FLECHA_Y = ptrMxy->col(1).minCoeff(&r, &c);
    FLECHA_X = (*ptrMxy)(r, c);

    return ptrMxy;
}

std::unique_ptr<Eigen::MatrixXd> eqEstadoTemperatura(const conf &caso)
{
    // Eigen Multithead
    Eigen::setNbThreads(6);

    const double passo{0.1};
    const double T1{caso.trup * caso.eds};
    const double C1{T1 / caso.massa};
    const double A{caso.cvao * caso.massa};

    // Passando por referencia, para facilitar a leitura
    const double max{caso.pminimo + passo * ((caso.pmaximo - caso.pminimo) / passo)};
    const double min{((caso.pmaximo - caso.pminimo) / passo) + 1};
    const double step{caso.pminimo};

    // Inicializa o ponteiro T2
    Eigen::VectorXd T2;
    T2 = Eigen::VectorXd::LinSpaced(long(min), step, max).transpose();

    Eigen::VectorXd C2{T2 / caso.massa};
    Eigen::VectorXd deltaTheta{C2};
    deltaTheta.setZero();

    std::unique_ptr<Eigen::MatrixXd> saida{std::make_unique<Eigen::MatrixXd>()};
    saida->setZero(C2.rows(), 2);

    // Termos da equacao
    Eigen::VectorXd A0{deltaTheta};
    Eigen::VectorXd A1{deltaTheta};
    Eigen::VectorXd A2{deltaTheta};

    for (int i = 1; i < T2.rows(); ++i) {
        A0[i] = C2(i) * sinh(A / (2.0 * C2(i)));
        A1[i] = C1 * sinh(A / (2.0 * C1));
        A2[i] = (1.0 / (caso.elastfinal * caso.secao)) * (T2(i) - T1);

        deltaTheta[i] = (1.0 / caso.alphafinal) * ((A0(i) / A1(i)) - 1.0 - A2(i));
    }

    saida->col(0) = T2;
    saida->col(1) = deltaTheta;

    return saida;
}

double eqTermicaCabo(const conf &caso)
{
    const double tOpK{caso.tcop + 273.15};
    const double tAmbK{caso.tamb + 273.16};
    const double emissividade = 0.5;  // Emissividade -  0.3 (novos); 0.5 (velho); 0.9 (sujo)

    const double QS{204 * caso.phi};
    const double QR{(179.2e3) * (emissividade) * (caso.phi) *
                    (pow(tOpK / 1000.0, 4) - pow(tAmbK / 1000.0, 4))};
    const double QC{(945.6e-4) * (caso.tcop - caso.tamb) *
                    (0.32 + 0.43 * pow(45946.8 * caso.phi * caso.ventomed, 0.52))};
    const double R_THETA{0.00025 * caso.tcop + 0.069};

    double saida;

    saida = pow(((QR + QC - QS) * (10e3) / R_THETA), (0.5));

    return saida;
}

//--------- NEWTON-RAPHSON ----------//

double NewtonRaphson(std::function<double(double)> const &f,
                     std::function<double(double)> const &df, const double &x0)
{
    double x     = x0 - f(x0) / df(x0);
    double x_ant = x0;

    for (int i = 0; i <= MAXIT; i++) {
        if (abs(x - x_ant) >= ERRO) {
            x_ant = x;
            x     = x - f(x) / df(x);
        }
    }
    return x;
}
