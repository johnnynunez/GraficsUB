#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtWidgets>

#include "Builder.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QString fitxerDades;
    QString fitxerObj;
    QString fitxerColorMap;
    int xmin, xmax, ymin, ymax, zmin, zmax;

signals:
    void newSceneFromData(QString, QString, QString, float, float, float, float, float, float);

private slots:
    void on_accepted();
    void on_rejected();
    void on_fitxerDades_returnPressed();
    void on_pushButton_FitxerDades_pressed();
    void on_fitxerObj_returnPressed();
    void on_pushButton_Obj_pressed();
    void on_colorMap_returnPressed();
    void on_pushButton_ColorMap_pressed();

    void on_xmin_valueChanged(double valor);
    void on_xmax_valueChanged(double valor);
    void on_ymin_valueChanged(double valor);
    void on_ymax_valueChanged(double valor);
    void on_zmin_valueChanged(double valor);
    void on_zmax_valueChanged(double valor);

};


#endif // DIALOG_H
