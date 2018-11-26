#include "mainwindow.hpp"
#include "lib/calcMec.hpp"
#include "ui_mainwindow.h"
#include <iostream>
#include <memory>  //std::unique_ptr

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->botaoCalcular->setDisabled(true);
    setValidador();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setValidador()
{
    // Caracteristicas Mecanicas
    ui->lineNFeixe->setValidator(intVal);
    ui->lineDiametroFeixe->setValidator(new QDoubleValidator(0, 1, 2, this));
    ui->lineComprimentoVao->setValidator(doubVal);
    ui->lineAlturaTorreA->setValidator(doubVal);
    ui->lineAlturaTorreB->setValidator(doubVal);
    ui->lineEDS->setValidator(new QDoubleValidator(0, 100, 2, this));
    ui->lineTemperaturaAmbiente->setValidator(new QDoubleValidator(-100, 100, 2, this));
    ui->lineTemperturaAmbienteMaxima->setValidator(new QDoubleValidator(-100, 100, 2, this));
    ui->lineTemperaturaAmbienteMinima->setValidator(new QDoubleValidator(-100, 100, 2, this));
    ui->lineVentoMedio->setValidator(new QDoubleValidator(0, 100, 2, this));

    ui->lineFaseAx->setValidator(new QDoubleValidator(-100, 100, 2, this));
    ui->lineFaseBx->setValidator(new QDoubleValidator(-100, 100, 2, this));
    ui->lineFaseCx->setValidator(new QDoubleValidator(-100, 100, 2, this));

    // Caracteristicas do cabo
    ui->lineSecaoTransversal->setValidator(doubVal);
    ui->lineDiametroCondutor->setValidator(doubVal);
    ui->lineMassaCondutor->setValidator(new QDoubleValidator(0, 10e4, 2, this));
    ui->lineCargaRuptura->setValidator(new QDoubleValidator(0, 10e6, 2, this));
    ui->lineCoeficienteDilatacao->setValidator(new QDoubleValidator(0, 1, 2, this));
    ui->lineModuloElasticidade->setValidator(new QDoubleValidator(0, 10e6, 2, this));
    ui->lineTemperaturaOperacao->setValidator(new QDoubleValidator(-100, 100, 2, this));
}

// ------------- METODOS -------------- //

void MainWindow::setData()
{

    // Caracteristicas Mecanicas
    ui->lineNFeixe->setText(QString::number(ncfeixe, 'f', 0));
    ui->lineDiametroFeixe->setText(QString::number(dfeixe, 'f', 3));
    ui->lineComprimentoVao->setText(QString::number(cvao, 'f', 2));
    ui->lineAlturaTorreA->setText(QString::number(hA, 'f', 2));
    ui->lineAlturaTorreB->setText(QString::number(hB, 'f', 2));
    ui->lineEDS->setText(QString::number(eds, 'f', 2));
    ui->lineTemperaturaAmbiente->setText(QString::number(tamb, 'f', 1));
    ui->lineTemperturaAmbienteMaxima->setText(QString::number(tmax, 'f', 1));
    ui->lineTemperaturaAmbienteMinima->setText(QString::number(tmin, 'f', 1));
    ui->lineVentoMedio->setText(QString::number(ventomed, 'f', 2));

    ui->lineFaseAx->setText(QString::number(gfeixe[0], 'f', 2));
    ui->lineFaseBx->setText(QString::number(gfeixe[1], 'f', 2));
    ui->lineFaseCx->setText(QString::number(gfeixe[2], 'f', 2));

    // Caracteristicas do cabo
    ui->lineSecaoTransversal->setText(QString::number(secao, 'f', 2));
    ui->lineDiametroCondutor->setText(QString::number(phi, 'f', 2));
    ui->lineMassaCondutor->setText(QString::number(massa, 'f', 2));
    ui->lineCargaRuptura->setText(QString::number(trup, 'f', 2));
    ui->lineCoeficienteDilatacao->setText(QString::number(alphafinal, 'e', 2));
    ui->lineModuloElasticidade->setText(QString::number(elastfinal, 'e', 2));
    ui->lineTemperaturaOperacao->setText(QString::number(tcop, 'f', 2));

    foreach (QLineEdit *le, findChildren<QLineEdit *>()) {
        le->setDisabled(false);
    }
}

void MainWindow::getData(conf &caso)
{

    caso.ncfeixe  = QVariant(ui->lineNFeixe->text()).toDouble();
    caso.dfeixe   = QVariant(ui->lineDiametroFeixe->text()).toDouble();
    caso.cvao     = QVariant(ui->lineComprimentoVao->text()).toDouble();
    caso.hA       = QVariant(ui->lineAlturaTorreA->text()).toDouble();
    caso.hB       = QVariant(ui->lineAlturaTorreB->text()).toDouble();
    caso.eds      = QVariant(ui->lineEDS->text()).toDouble();
    caso.tamb     = QVariant(ui->lineTemperaturaAmbiente->text()).toDouble();
    caso.tmax     = QVariant(ui->lineTemperaturaAmbienteMinima->text()).toDouble();
    caso.tmin     = QVariant(ui->lineTemperaturaAmbienteMinima->text()).toDouble();
    caso.ventomed = QVariant(ui->lineVentoMedio->text()).toDouble();
    caso.nl       = caso.cvao;  // numero de divisoes (para o tricamp)
    caso.tensao   = 765e3;

    caso.gfeixe[0] = QVariant(ui->lineFaseAx->text()).toDouble();
    caso.gfeixe[1] = QVariant(ui->lineFaseBx->text()).toDouble();
    caso.gfeixe[2] = QVariant(ui->lineFaseCx->text()).toDouble();

    // Converte para metro
    caso.secao      = QVariant(ui->lineSecaoTransversal->text()).toDouble() * (1e-6);
    caso.phi        = QVariant(ui->lineDiametroCondutor->text()).toDouble() * (1e-3);
    caso.massa      = QVariant(ui->lineMassaCondutor->text()).toDouble() * (1e-3);
    caso.trup       = QVariant(ui->lineCargaRuptura->text()).toDouble() / 100.0;
    caso.alphafinal = QVariant(ui->lineCoeficienteDilatacao->text()).toDouble();
    caso.elastfinal = QVariant(ui->lineModuloElasticidade->text()).toDouble() * (1e6);
    caso.tcop       = QVariant(ui->lineTemperaturaOperacao->text()).toDouble();
    caso.pminimo    = 76.0;
    caso.pmaximo    = 108.0;
}

void MainWindow::clearData()
{
    foreach (QLineEdit *le, findChildren<QLineEdit *>()) {
        le->clear();
        le->setDisabled(true);
    }
}

void MainWindow::calcula(const conf &caso)
{
    const double hmax{MAX(caso.hA, caso.hB)};
    const double S{caso.cvao};
    double lcabo{0.0};  // comprimento total do cabo (maior do que o vão)
    double lflecha{0.0};
    double flechax{0.0};
    double flechay{0.0};

    // Chama a funcao catenaria e retorna o comprimento do cabo
    // e a matriz posicao x altura
    std::unique_ptr<Eigen::MatrixXd> ptrMxy{new Eigen::MatrixXd};  // Inicializa o ponteiro

    ptrMxy = catenaria(caso, lcabo, lflecha, flechax, flechay);

    QString texto1 = "Comprimento do cabo: " + QString::number(lcabo, 'f', 2) + " [m]           ";
    QString texto2 =
        "Comprimento da flecha: " + QString::number(lflecha, 'f', 2) + " [m]           ";
    QString texto3 = "Posição da flecha: ( " + QString::number(flechax, 'f', 2) + ", " +
                     QString::number(flechay, 'f', 2) + " ) [m]";
    ui->statusBar->showMessage(texto1 + texto2 + texto3);

    // Inicializa os ponteiros
    std::unique_ptr<QVector<double>> ptrPx{new QVector<double>()};
    std::unique_ptr<QVector<double>> ptrPy{new QVector<double>()};

    // Converte os pontos para um vetor (QCustomPlot)
    // Ao inves de fazer a copia dos dados, aponta
    // o endereco da memoria em que estao armazenados
    ptrPx->clear();
    ptrPy->clear();
    for (int i = 0; i < ptrMxy->rows(); i++) {
        ptrPx->push_back(double(ptrMxy->coeffRef(i, 0)));
        ptrPy->push_back(double(ptrMxy->coeffRef(i, 1)));
    }

    // Plota campo catenaria
    QPointer<QCustomPlot> customPlot1 = ui->widgetVao;

    customPlot1->addGraph();
    customPlot1->graph(0)->setPen(QPen(Qt::blue));  // line color blue for first graph
    customPlot1->graph(0)->setBrush(
        QBrush(QColor(0, 0, 255, 20)));  // first graph will be filled with translucent blue

    customPlot1->addGraph();
    customPlot1->graph(1)->setPen(QPen(Qt::red));
    customPlot1->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 6));
    std::unique_ptr<QVector<double>> x{new QVector<double>()};
    std::unique_ptr<QVector<double>> y{new QVector<double>()};

    x->push_back(flechax);
    y->push_back(flechay);
    customPlot1->graph(1)->setData(*x, *y);

    customPlot1->xAxis->setLabel("Posição no vão [m]");
    customPlot1->yAxis->setLabel("Altura [m]");

    customPlot1->xAxis->setRange(-S / 2.0, S / 2.0);
    customPlot1->yAxis->setRange(0, hmax + 10);
    customPlot1->yAxis2->setRange(0, hmax + 10);

    plota(*ptrPx, *ptrPy, customPlot1);

    std::unique_ptr<Eigen::MatrixXd> eqEstado{std::make_unique<Eigen::MatrixXd>()};
    eqEstado = eqEstadoTemperatura(caso);

    // std::cout << *eqEstado << std::endl;
}

void MainWindow::plota(const QVector<double> &vx, const QVector<double> &vy,
                       QPointer<QCustomPlot> &plot)
{

    plot->xAxis2->setVisible(true);
    plot->xAxis2->setTickLabels(false);
    plot->yAxis2->setVisible(true);
    plot->yAxis2->setTickLabels(true);
    // plot->yAxis2->setLabel("Altura [m]");

    // qDebug() << qVecE << "\n";

    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));

    // qDebug() << "Plota" << "\n";
    plot->graph(0)->setData(vx, vy);

    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    plot->replot();
    plot->update();
}

void MainWindow::calc0()
{
    conf caso;
    getData(caso);
    calcula(caso);
}

void MainWindow::on_botaoReset_clicked()
{
    setData();
    ui->botaoCalcular->setDisabled(false);
}

void MainWindow::on_botaoLimpar_clicked()
{
    clearData();
    ui->botaoCalcular->setDisabled(true);
}

void MainWindow::on_botaoCalcular_clicked() { calc0(); }
void MainWindow::on_lineNFeixe_returnPressed() { calc0(); }
void MainWindow::on_lineDiametroFeixe_returnPressed() { calc0(); }
void MainWindow::on_lineComprimentoVao_returnPressed() { calc0(); }
void MainWindow::on_lineAlturaTorreA_returnPressed() { calc0(); }
void MainWindow::on_lineAlturaTorreB_returnPressed() { calc0(); }
void MainWindow::on_lineEDS_returnPressed() { calc0(); }
void MainWindow::on_lineTemperaturaAmbiente_returnPressed() { calc0(); }
void MainWindow::on_lineTemperturaAmbienteMaxima_returnPressed() { calc0(); }
void MainWindow::on_lineTemperaturaAmbienteMinima_returnPressed() { calc0(); }
void MainWindow::on_lineVentoMedio_returnPressed() { calc0(); }
void MainWindow::on_lineFaseAx_returnPressed() { calc0(); }
void MainWindow::on_lineFaseBx_returnPressed() { calc0(); }
void MainWindow::on_lineFaseCx_returnPressed() { calc0(); }
void MainWindow::on_lineSecaoTransversal_returnPressed() { calc0(); }
void MainWindow::on_lineDiametroCondutor_returnPressed() { calc0(); }
void MainWindow::on_lineMassaCondutor_returnPressed() {}
void MainWindow::on_lineCargaRuptura_returnPressed() { calc0(); }
void MainWindow::on_lineCoeficienteDilatacao_returnPressed() { calc0(); }
void MainWindow::on_lineModuloElasticidade_returnPressed() { calc0(); }
void MainWindow::on_lineTemperaturaOperacao_returnPressed() { calc0(); }
