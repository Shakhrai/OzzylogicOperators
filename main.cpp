#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.setWindowTitle("Operators Viewer");
    mainWindow.resize(800,600);
    mainWindow.show();

    return app.exec();
}
