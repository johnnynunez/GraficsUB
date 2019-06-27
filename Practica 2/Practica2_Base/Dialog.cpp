#include "Dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    xmin = -5.0;
    ymin = -5.0;
    zmin = -5.0;
    xmax = 5.0;
    ymax = 5.0;
    zmax = 5.0;

    connect(this->ui->act_llegir_Dades, SIGNAL(accepted()), this, SLOT(on_accepted()));
    connect(this->ui->act_llegir_Dades, SIGNAL(rejected()), this, SLOT(on_rejected()));
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_fitxerDades_returnPressed()
{
    fitxerDades = ui->fitxerDades->text();
}

void Dialog::on_pushButton_FitxerDades_pressed()
{
    QString file = QFileDialog::getOpenFileName(this,
                                                "Open Data File txt",
                                                QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0),
                                                "*.txt ");
    ui->fitxerDades->setText(file);
    on_fitxerDades_returnPressed();
}

void Dialog::on_fitxerObj_returnPressed()
{
    fitxerObj = ui->fitxerObj->text();
}

void Dialog::on_pushButton_Obj_pressed()
{
    QString file = QFileDialog::getOpenFileName(this,
                                                "Open Boundary Object",
                                                QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0),
                                                "*.obj");
    ui->fitxerObj->setText(file);
    on_fitxerObj_returnPressed();
}

void Dialog::on_colorMap_returnPressed()
{
    fitxerColorMap = ui->colorMap->text();
}

void Dialog::on_pushButton_ColorMap_pressed()
{
    QString file = QFileDialog::getOpenFileName(this,
                                                "Open Color Map",
                                                QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0),
                                                "*.gpl");
    ui->colorMap->setText(file);
    on_colorMap_returnPressed();
}

void Dialog::on_xmin_valueChanged(double valor)
{
    Q_UNUSED(valor);
    xmin = valor;
}

void Dialog::on_xmax_valueChanged(double valor)
{
    Q_UNUSED(valor);
    xmax = valor;
}
void Dialog::on_ymin_valueChanged(double valor)
{
    Q_UNUSED(valor);
    ymin = valor;
}

void Dialog::on_ymax_valueChanged(double valor)
{
    Q_UNUSED(valor);
    ymax = valor;
}
void Dialog::on_zmin_valueChanged(double valor)
{
    Q_UNUSED(valor);
    zmin = valor;
}

void Dialog::on_zmax_valueChanged(double valor)
{
    Q_UNUSED(valor);
    zmax = valor;
}

void Dialog::on_accepted()
{
    emit newSceneFromData(fitxerDades, fitxerObj, fitxerColorMap, xmin, xmax, ymin, ymax, zmin, zmax);
}

void Dialog::on_rejected() {
    xmin = -5.0;
    ymin = -5.0;
    zmin = -5.0;
    xmax = 5.0;
    ymax = 5.0;
    zmax = 5.0;

    // Podeu modificar el path segons on tingueu els arxius o el desplegament del projecte

    ui->fitxerDades->setText("../practica2Basica/resources/data/dades0.txt");
    ui->fitxerObj->setText("../practica2Basica/resources/obj/cube.obj");
    ui->colorMap->setText("../practica2Basica/resources/data/colorMap0.gpl");

}
