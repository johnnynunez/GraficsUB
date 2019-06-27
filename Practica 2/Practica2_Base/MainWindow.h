#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "GLWidget.h"
#include "Builder.h"
#include "Dialog.h"


QT_BEGIN_NAMESPACE
class QSlider;
class GLWidget;
QT_END_NAMESPACE

namespace Ui {
   class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool changes; // Variable de control d
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    Builder        *builder;
    GLWidget       *glWidget;
    Dialog         *dialog;   // Dialeg per a llegir el fitxer de dades.txt


private slots:

    void newDialogDades();

    void on_persVerticalAngleSpin_valueChanged(double arg1);

    void on_persNearSpin_valueChanged(double arg1);

    void on_persFarSpin_valueChanged(double arg1);

    void on_lookEyeXSpin_valueChanged(double arg1);

    void on_lookEyeYSpin_valueChanged(double arg1);

    void on_lookEyeZSpin_valueChanged(double arg1);

    void on_lookCenterXSpin_valueChanged(double arg1);

    void on_lookCenterYSpin_valueChanged(double arg1);

    void on_lookCenterZSpin_valueChanged(double arg1);

    void on_lookUpXSpin_valueChanged(double arg1);

    void on_lookUpYSpin_valueChanged(double arg1);

    void on_lookUpZSpin_valueChanged(double arg1);

    void on_scaleSpin_valueChanged(double arg1);

    void on_translateXSpin_valueChanged(double arg1);

    void on_translateYSpin_valueChanged(double arg1);

    void on_translateZSpin_valueChanged(double arg1);

    void on_rotateAngleSpin_valueChanged(double arg1);

    void on_rotateXSpin_valueChanged(double arg1);

    void on_rotateYSpin_valueChanged(double arg1);

    void on_rotateZSpin_valueChanged(double arg1);

    void on_lightPosXSpin_valueChanged(double arg1);

    void on_lightPosYSpin_valueChanged(double arg1);

    void on_lightPosZSpin_valueChanged(double arg1);

    void on_actionAbout_Qt_triggered();

    void on_action_exit_triggered();

    void on_persVerticalAngleSlider_valueChanged(int value);

    void on_persNearSlider_valueChanged(int value);

    void on_persFarSlider_valueChanged(int value);

    void on_lightId1Spin_valueChanged(double arg1);

    void on_lightId2Spin_valueChanged(double arg1);

    void on_lightId3Spin_valueChanged(double arg1);

    void on_lightIa1Spin_valueChanged(double arg1);

    void on_lightIa2Spin_valueChanged(double arg1);

    void on_lightIa3Spin_valueChanged(double arg1);

    void on_lightIs1Spin_valueChanged(double arg1);

    void on_lightIs2Spin_valueChanged(double arg1);

    void on_lightIs3Spin_valueChanged(double arg1);

    void on_textureFileEdit_returnPressed();

    void on_browseTextureBtn_pressed();

    void on_rotateAngleSlider_valueChanged(int value);

    void setObsCamera(Camera *cam);

    void setFrustumCamera(Camera *cam);


};

#endif // MAINWINDOW_H
