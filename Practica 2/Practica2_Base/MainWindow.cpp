
#include "MainWindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->mainTabs->setCurrentIndex(0);

    // Codi necessari per adaptar el projecte a la versio 330 de gl
    QGLFormat glfModern=QGLFormat::defaultFormat();
    glfModern.setVersion(3,3);
    glfModern.setProfile(QGLFormat::CoreProfile);
    glfModern.setSampleBuffers(true);
    glfModern.setSwapInterval(0);
    glfModern.setDefaultFormat(glfModern);
    glWidget = new GLWidget(glfModern);
    // Construcció del Builder

    builder = new Builder(glWidget);

    setCentralWidget(ui->centralWidget);

    ui->gridLayout_2->addWidget(glWidget, 0, 0);
    changes = true;

    // Construcció del Builder

    builder = new Builder(glWidget);

    // Construcció del nou Dialeg per a llegir les dades
    dialog = new Dialog(this);

    // connexio dels menus amb els mètodes corresponents

    connect(this->ui->action_obre_fitxer, SIGNAL(triggered()), builder, SLOT(newObjFromFile()));
    connect(this->ui->action_obre_escena, SIGNAL(triggered()), builder, SLOT(newStaticScene()));
    connect(this->ui->action_obre_dades, SIGNAL(triggered()), this, SLOT(newDialogDades()));
    connect(this->ui->action_save_frame_as_image, SIGNAL(triggered()), glWidget, SLOT(saveImage()));
    connect(this->ui->action_start_and_save_animation, SIGNAL(triggered()), glWidget, SLOT(saveAnimation()));
    connect(this->ui->action_gouraud, SIGNAL(triggered()), glWidget, SLOT(activaGouraudShader()));
    connect(this->ui->action_phong, SIGNAL(triggered()), glWidget, SLOT(activaPhongShader()));
    connect(this->ui->action_toon, SIGNAL(triggered()), glWidget, SLOT(activaToonShader()));
    connect(this->ui->actionPhong_Indirect_Shader, SIGNAL(triggered()), glWidget, SLOT(activaPhongTexIndirecteShader()));
    connect(this->ui->action_activa_background, SIGNAL(triggered()), glWidget, SLOT(activaBackground()));
    connect(this->ui->action_phong_tex, SIGNAL(triggered()), glWidget, SLOT(activaPhongTex()));
    connect(this->ui->action_bump_mapping, SIGNAL(triggered()), glWidget, SLOT(activaBumpMapping()));
    connect(this->ui->action_environmental_mapping, SIGNAL(triggered()), glWidget, SLOT(activaEnvMapping()));
    connect(this->ui->action_transparencies, SIGNAL(triggered()), glWidget, SLOT(activaTransparency()));

    // Sincronització del canvi de paràmetres de la camera amb el ratolí
    connect(glWidget, SIGNAL(ObsCameraChanged(Camera*)), this, SLOT(setObsCamera(Camera *)));
    connect(glWidget, SIGNAL(FrustumCameraChanged(Camera*)), this, SLOT(setFrustumCamera(Camera *)));

    connect(builder, SIGNAL(newObj(Object*)), glWidget, SLOT(updateObject(Object *)));
    connect(builder, SIGNAL(newScene(Scene*)), glWidget, SLOT(updateScene(Scene *)));

    connect(dialog, SIGNAL(newSceneFromData(QString, QString, QString, float, float, float, float, float, float)),
            builder, SLOT(newData(QString,QString,QString,float,float,float,float,float,float)));

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newDialogDades() {
    dialog->show();

}
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}


void MainWindow::on_persVerticalAngleSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
         glWidget->setPerspective(ui->persVerticalAngleSpin->value(),
                                    ui->persNearSpin->value(),
                                    ui->persFarSpin->value());

}

void MainWindow::on_persNearSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
         glWidget->setPerspective(ui->persVerticalAngleSpin->value(),
                                    ui->persNearSpin->value(),
                                    ui->persFarSpin->value());

}

void MainWindow::on_persFarSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
         glWidget->setPerspective(ui->persVerticalAngleSpin->value(),
                                    ui->persNearSpin->value(),
                                    ui->persFarSpin->value());

}

void MainWindow::on_lookEyeXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void MainWindow::on_lookEyeYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void MainWindow::on_lookEyeZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void MainWindow::on_lookCenterXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void MainWindow::on_lookCenterYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void MainWindow::on_lookCenterZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void MainWindow::on_lookUpXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void MainWindow::on_lookUpYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void MainWindow::on_lookUpZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void MainWindow::on_scaleSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setTranslation(ui->translateXSpin->value(),
                                    ui->translateYSpin->value(),
                                    ui->translateZSpin->value());
}

void MainWindow::on_translateXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setScale(ui->scaleSpin->value());
}

void MainWindow::on_translateYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setScale(ui->scaleSpin->value());
}

void MainWindow::on_translateZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setScale(ui->scaleSpin->value());
}

void MainWindow::on_rotateAngleSpin_valueChanged(double arg1)
{
    ui->rotateAngleSlider->setValue(arg1 * 10);
    glWidget->setRotation(ui->rotateAngleSpin->value(),
                                 ui->rotateXSpin->value(),
                                 ui->rotateYSpin->value(),
                                 ui->rotateZSpin->value());
}

void MainWindow::on_rotateXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setRotation(ui->rotateAngleSpin->value(),
                                 ui->rotateXSpin->value(),
                                 ui->rotateYSpin->value(),
                                 ui->rotateZSpin->value());
}

void MainWindow::on_rotateYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setRotation(ui->rotateAngleSpin->value(),
                                 ui->rotateXSpin->value(),
                                 ui->rotateYSpin->value(),
                                 ui->rotateZSpin->value());
}

void MainWindow::on_rotateZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setRotation(ui->rotateAngleSpin->value(),
                                 ui->rotateXSpin->value(),
                                 ui->rotateYSpin->value(),
                                 ui->rotateZSpin->value());
}

void MainWindow::on_lightPosXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setLighting(QVector3D(ui->lightPosXSpin->value(),
                                           ui->lightPosYSpin->value(),
                                           ui->lightPosZSpin->value()),
                                 QVector3D(ui->lightIa1Spin->value(),
                                           ui->lightIa2Spin->value(),
                                           ui->lightIa3Spin->value()),
                                 QVector3D(ui->lightId1Spin->value(),
                                           ui->lightId2Spin->value(),
                                           ui->lightId3Spin->value()),
                                 QVector3D(ui->lightIs1Spin->value(),
                                           ui->lightIs2Spin->value(),
                                           ui->lightIs3Spin->value()),
                                 QVector3D(ui->lightCoefA->value(),
                                           ui->lightCoefB->value(),
                                            ui->lightCoefC->value())
                                 );
}

void MainWindow::on_lightPosYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setLighting(QVector3D(ui->lightPosXSpin->value(),
                                           ui->lightPosYSpin->value(),
                                           ui->lightPosZSpin->value()),
                                 QVector3D(ui->lightIa1Spin->value(),
                                           ui->lightIa2Spin->value(),
                                           ui->lightIa3Spin->value()),
                                 QVector3D(ui->lightId1Spin->value(),
                                           ui->lightId2Spin->value(),
                                           ui->lightId3Spin->value()),
                                 QVector3D(ui->lightIs1Spin->value(),
                                           ui->lightIs2Spin->value(),
                                           ui->lightIs3Spin->value()),
                                 QVector3D(ui->lightCoefA->value(),
                                           ui->lightCoefB->value(),
                                            ui->lightCoefC->value())
                                 );
}

void MainWindow::on_lightPosZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setLighting(QVector3D(ui->lightPosXSpin->value(),
                                           ui->lightPosYSpin->value(),
                                           ui->lightPosZSpin->value()),
                                 QVector3D(ui->lightIa1Spin->value(),
                                           ui->lightIa2Spin->value(),
                                           ui->lightIa3Spin->value()),
                                 QVector3D(ui->lightId1Spin->value(),
                                           ui->lightId2Spin->value(),
                                           ui->lightId3Spin->value()),
                                 QVector3D(ui->lightIs1Spin->value(),
                                           ui->lightIs2Spin->value(),
                                           ui->lightIs3Spin->value()),
                                  QVector3D(ui->lightCoefA->value(),
                                            ui->lightCoefB->value(),
                                            ui->lightCoefC->value())
                                 );
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}


void MainWindow::on_action_exit_triggered()
{
    close();
}

void MainWindow::on_persVerticalAngleSlider_valueChanged(int value)
{
    ui->persVerticalAngleSpin->setValue(double(value) / 100.0);
}

void MainWindow::on_persNearSlider_valueChanged(int value)
{
    ui->persNearSpin->setValue(double(value) / 100.0);
}

void MainWindow::on_persFarSlider_valueChanged(int value)
{
    ui->persFarSpin->setValue(double(value) / 100.0);
}

void MainWindow::on_lightId1Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setLighting(QVector3D(ui->lightPosXSpin->value(),
                                           ui->lightPosYSpin->value(),
                                           ui->lightPosZSpin->value()),
                                 QVector3D(ui->lightIa1Spin->value(),
                                           ui->lightIa2Spin->value(),
                                           ui->lightIa3Spin->value()),
                                 QVector3D(ui->lightId1Spin->value(),
                                           ui->lightId2Spin->value(),
                                           ui->lightId3Spin->value()),
                                 QVector3D(ui->lightIs1Spin->value(),
                                           ui->lightIs2Spin->value(),
                                           ui->lightIs3Spin->value()),
                                 QVector3D(ui->lightCoefA->value(),
                                           ui->lightCoefB->value(),
                                           ui->lightCoefC->value())
                                 );
}

void MainWindow::on_lightId2Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setLighting(QVector3D(ui->lightPosXSpin->value(),
                                           ui->lightPosYSpin->value(),
                                           ui->lightPosZSpin->value()),
                                 QVector3D(ui->lightIa1Spin->value(),
                                           ui->lightIa2Spin->value(),
                                           ui->lightIa3Spin->value()),
                                 QVector3D(ui->lightId1Spin->value(),
                                           ui->lightId2Spin->value(),
                                           ui->lightId3Spin->value()),
                                 QVector3D(ui->lightIs1Spin->value(),
                                           ui->lightIs2Spin->value(),
                                           ui->lightIs3Spin->value()),
                                 QVector3D(ui->lightCoefA->value(),
                                           ui->lightCoefB->value(),
                                           ui->lightCoefC->value())
                                 );
}

void MainWindow::on_lightId3Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setLighting(QVector3D(ui->lightPosXSpin->value(),
                                           ui->lightPosYSpin->value(),
                                           ui->lightPosZSpin->value()),
                                 QVector3D(ui->lightIa1Spin->value(),
                                           ui->lightIa2Spin->value(),
                                           ui->lightIa3Spin->value()),
                                 QVector3D(ui->lightId1Spin->value(),
                                           ui->lightId2Spin->value(),
                                           ui->lightId3Spin->value()),
                                 QVector3D(ui->lightIs1Spin->value(),
                                           ui->lightIs2Spin->value(),
                                           ui->lightIs3Spin->value()),
                                 QVector3D(ui->lightCoefA->value(),
                                           ui->lightCoefB->value(),
                                           ui->lightCoefC->value())
                                 );
}

void MainWindow::on_lightIa1Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setLighting(QVector3D(ui->lightPosXSpin->value(),
                                           ui->lightPosYSpin->value(),
                                           ui->lightPosZSpin->value()),
                                 QVector3D(ui->lightIa1Spin->value(),
                                           ui->lightIa2Spin->value(),
                                           ui->lightIa3Spin->value()),
                                 QVector3D(ui->lightId1Spin->value(),
                                           ui->lightId2Spin->value(),
                                           ui->lightId3Spin->value()),
                                 QVector3D(ui->lightIs1Spin->value(),
                                           ui->lightIs2Spin->value(),
                                           ui->lightIs3Spin->value()),
                                 QVector3D(ui->lightCoefA->value(),
                                           ui->lightCoefB->value(),
                                           ui->lightCoefC->value())
                                 );
}

void MainWindow::on_lightIa2Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setLighting(QVector3D(ui->lightPosXSpin->value(),
                                           ui->lightPosYSpin->value(),
                                           ui->lightPosZSpin->value()),
                                 QVector3D(ui->lightIa1Spin->value(),
                                           ui->lightIa2Spin->value(),
                                           ui->lightIa3Spin->value()),
                                 QVector3D(ui->lightId1Spin->value(),
                                           ui->lightId2Spin->value(),
                                           ui->lightId3Spin->value()),
                                 QVector3D(ui->lightIs1Spin->value(),
                                           ui->lightIs2Spin->value(),
                                           ui->lightIs3Spin->value()),
                                 QVector3D(ui->lightCoefA->value(),
                                           ui->lightCoefB->value(),
                                           ui->lightCoefC->value())
                                 );
}

void MainWindow::on_lightIa3Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setLighting(QVector3D(ui->lightPosXSpin->value(),
                                           ui->lightPosYSpin->value(),
                                           ui->lightPosZSpin->value()),
                                 QVector3D(ui->lightIa1Spin->value(),
                                           ui->lightIa2Spin->value(),
                                           ui->lightIa3Spin->value()),
                                 QVector3D(ui->lightId1Spin->value(),
                                           ui->lightId2Spin->value(),
                                           ui->lightId3Spin->value()),
                                 QVector3D(ui->lightIs1Spin->value(),
                                           ui->lightIs2Spin->value(),
                                           ui->lightIs3Spin->value()),
                                 QVector3D(ui->lightCoefA->value(),
                                           ui->lightCoefB->value(),
                                           ui->lightCoefC->value())
                                 );
}

void MainWindow::on_lightIs1Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setLighting(QVector3D(ui->lightPosXSpin->value(),
                                           ui->lightPosYSpin->value(),
                                           ui->lightPosZSpin->value()),
                                 QVector3D(ui->lightIa1Spin->value(),
                                           ui->lightIa2Spin->value(),
                                           ui->lightIa3Spin->value()),
                                 QVector3D(ui->lightId1Spin->value(),
                                           ui->lightId2Spin->value(),
                                           ui->lightId3Spin->value()),
                                 QVector3D(ui->lightIs1Spin->value(),
                                           ui->lightIs2Spin->value(),
                                           ui->lightIs3Spin->value()),
                                 QVector3D(ui->lightCoefA->value(),
                                           ui->lightCoefB->value(),
                                           ui->lightCoefC->value())
                                 );
}

void MainWindow::on_lightIs2Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setLighting(QVector3D(ui->lightPosXSpin->value(),
                                           ui->lightPosYSpin->value(),
                                           ui->lightPosZSpin->value()),
                                 QVector3D(ui->lightIa1Spin->value(),
                                           ui->lightIa2Spin->value(),
                                           ui->lightIa3Spin->value()),
                                 QVector3D(ui->lightId1Spin->value(),
                                           ui->lightId2Spin->value(),
                                           ui->lightId3Spin->value()),
                                 QVector3D(ui->lightIs1Spin->value(),
                                           ui->lightIs2Spin->value(),
                                           ui->lightIs3Spin->value()),
                                 QVector3D(ui->lightCoefA->value(),
                                           ui->lightCoefB->value(),
                                           ui->lightCoefC->value())
                                 );
}

void MainWindow::on_lightIs3Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    glWidget->setLighting(QVector3D(ui->lightPosXSpin->value(),
                                           ui->lightPosYSpin->value(),
                                           ui->lightPosZSpin->value()),
                                 QVector3D(ui->lightIa1Spin->value(),
                                           ui->lightIa2Spin->value(),
                                           ui->lightIa3Spin->value()),
                                 QVector3D(ui->lightId1Spin->value(),
                                           ui->lightId2Spin->value(),
                                           ui->lightId3Spin->value()),
                                 QVector3D(ui->lightIs1Spin->value(),
                                           ui->lightIs2Spin->value(),
                                           ui->lightIs3Spin->value()),
                                 QVector3D(ui->lightCoefA->value(),
                                           ui->lightCoefB->value(),
                                           ui->lightCoefC->value())
                                 );
}

void MainWindow::on_textureFileEdit_returnPressed()
{
    glWidget->setTextureFile(ui->textureFileEdit->text());

}

void MainWindow::on_browseTextureBtn_pressed()
{
    QString file = QFileDialog::getOpenFileName(this,
                                                "Open Texture",
                                                QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0),
                                                "*.jpg *.png *.tif *.bmp");
    ui->textureFileEdit->setText(file);
    on_textureFileEdit_returnPressed();
}

void MainWindow::on_rotateAngleSlider_valueChanged(int value)
{
    ui->rotateAngleSpin->setValue(double(value) / 10.0);
}

void MainWindow::setObsCamera(Camera *cam)
{
    changes = false;
    ui->lookEyeXSpin->setValue((float)cam->origin.x);
    ui->lookEyeYSpin->setValue((float)cam->origin.y);
    ui->lookEyeZSpin->setValue((float) cam->origin.z);

    ui->lookCenterXSpin->setValue(cam->vrp.x);
    ui->lookCenterYSpin->setValue(cam->vrp.y);
    ui->lookCenterZSpin->setValue(cam->vrp.z);

    ui->lookUpXSpin->setValue(cam->vUp.x);
    ui->lookUpYSpin->setValue(cam->vUp.y);
    ui->lookUpZSpin->setValue(cam->vUp.z);
    changes = true;
}

void MainWindow::setFrustumCamera(Camera *cam)
{
    changes = false;
    ui->persVerticalAngleSpin->setValue(cam->vfovRadians * 180.0/PI);
    ui->persFarSpin->setValue(cam->dpost);
    ui->persNearSpin->setValue(cam->dant);

    ui->persVerticalAngleSlider->setValue(cam->vfovRadians * 180.0/PI*100);
    ui->persFarSlider->setValue(cam->dpost*100);
    ui->persNearSlider->setValue(cam->dant*100);
    changes = true;

}
