#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.setWindowTitle("GiVD 2ona pràctica: GPU 2018-19");
    w.show();

    return a.exec();
}
