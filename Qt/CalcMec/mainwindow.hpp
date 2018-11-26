#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "lib/calcMec.hpp"
#include "lib/qcustomplot.hpp"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Metodos basicos
    void setValidador();
    void setData();
    void getData(conf &);
    void clearData();
    void calcula(const conf &);
    void plota(const QVector<double> &, const QVector<double> &, QPointer<QCustomPlot> &);

  private slots:
    void on_botaoReset_clicked();
    void on_botaoCalcular_clicked();
    void on_botaoLimpar_clicked();
    void on_lineNFeixe_returnPressed();
    void on_lineDiametroFeixe_returnPressed();
    void on_lineComprimentoVao_returnPressed();
    void on_lineAlturaTorreA_returnPressed();
    void on_lineAlturaTorreB_returnPressed();
    void on_lineEDS_returnPressed();
    void on_lineTemperaturaAmbiente_returnPressed();
    void on_lineTemperturaAmbienteMaxima_returnPressed();
    void on_lineTemperaturaAmbienteMinima_returnPressed();
    void on_lineVentoMedio_returnPressed();
    void on_lineFaseAx_returnPressed();
    void on_lineFaseBx_returnPressed();
    void on_lineFaseCx_returnPressed();
    void on_lineSecaoTransversal_returnPressed();
    void on_lineDiametroCondutor_returnPressed();
    void on_lineMassaCondutor_returnPressed();
    void on_lineCargaRuptura_returnPressed();
    void on_lineCoeficienteDilatacao_returnPressed();
    void on_lineModuloElasticidade_returnPressed();
    void on_lineTemperaturaOperacao_returnPressed();

  private:
    Ui::MainWindow *ui;
    void calc0();

    // Caracteristicas do vao
    const int ncfeixe{4};        // numero de condutores no feixe
    const double dfeixe{0.457};  // diametro do feixe
    const double cvao{300.0};    // comprimento do vao [m]
    // const double h0 {25.0};         // altura de partida (torre)
    const double hA{25.0};
    const double hB{25.0};
    const double eds{20.0};      // condicao de temperatura media sem efeito do vento (EDS) [%]
    const double nl{30.0};       // numero de divisoes na catenaria (para o tricamp)
    const double tensao{765e3};  // nivel de tensao [V]
    const double tmax{39.2};     // temperatura maxima ambiente
    const double tmin{-0.3};     // temperatura minima ambiente

    // Condições para calculo da Ampacidade
    const double tcop{75.0};     // Temperatura(operacao) do condutor
    const double tamb{25.0};     // Temperatura ambiente
    const double ventomed{1.0};  // Velocidade do vento, com som [m/s]

    const std::vector<double> gfeixe{-14.34, 0.0, 14.34};

    // TODO -> Criar uma lista com alguns cabos
    // Caracteristicas do cabo BLUEJAY - 1229 Amperes
    const double secao{604.39};  // *(1e-6) Secao transversal do condutor [mm² -> m²]
    const double phi{31.98};     // *(1e-3) Diametro do condutor [mm -> m]
    const double massa{1870.6};  // *(1e-3) [kg/km -> kg/m]
    const double trup{13526.0};  // Carga de ruptuta (Classe A) [kgf]

    // Caracteristicas de Tensao e Deformacao para Cabos T-CAA (45/7)
    const double alphafinal{20.9e-6};  // Coeficiente de dilatacao linear final [ºC^-1]
    const double elastfinal{6679.0};   // *(1e6) Modulo de elasticidade final [kgf/mm² -> kgf/m² ]
    const double pminimo{76.0};
    const double pmaximo{108.0};

    QValidator *intVal  = new QIntValidator(0, 100, this);
    QValidator *doubVal = new QDoubleValidator(0, 2000, 2, this);
};

#endif  // MAINWINDOW_HPP
