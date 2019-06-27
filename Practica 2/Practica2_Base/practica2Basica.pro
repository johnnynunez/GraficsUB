#-------------------------------------------------
#
# Project created by QtCreator 2012-02-07T16:04:09
#
#-------------------------------------------------

QT       += core gui opengl
QT       += widgets

TARGET = practica2Basica
TEMPLATE = app

SOURCES +=\
    Camera.cpp \
    Light.cpp \
    Material.cpp \
    MainWindow.cpp \
    Main.cpp \
    GLWidget.cpp \
    library/Common.cpp \
    objects/cara.cpp \
    objects/Object.cpp \
    objects/plane.cpp \
    scenes/Scene.cpp \
    scenes/SceneFactory.cpp \
    scenes/SceneFactoryAnimation.cpp \
    scenes/SceneFactoryBasica.cpp \
    TG/TG.cpp \
    TG/Trans.cpp \
    TG/Sca.cpp \
    animations/Animation.cpp \
    Builder.cpp \
    Dialog.cpp \
    colormaps/ColorMapStatic.cpp \
    scenes/SceneFactoryStatic.cpp \
    scenes/SceneFactoryTemporal.cpp

HEADERS  += \
    library/vec.h \
    library/mat.h \
    library/Common.h \
    Camera.h \
    Light.h \
    Material.h \
    MainWindow.h \
    objects/cara.h \
    objects/plane.h \
    objects/Object.h \
    scenes/Scene.h \
    scenes/SceneFactory.h \
    scenes/SceneFactoryAnimation.h \
    scenes/SceneFactoryBasica.h \
    GLWidget.h \
    TG/TG.h \
    TG/Trans.h \
    TG/Sca.h \
    animations/Animation.h \
    Builder.h \
    Dialog.h \
    colormaps/ColorMap.h \
    colormaps/ColorMapStatic.h \
    scenes/SceneFactoryStatic.h \
    scenes/SceneFactoryTemporal.h

FORMS    += mainwindow.ui \
    dialog.ui

OTHER_FILES += \
    vshader1.glsl \
    fshader1.glsl

RESOURCES += resources.qrc

DISTFILES += \
    resources/textures/europa.png


