#include "mainwindow.h"
#include <QtWidgets/QMainWindow>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    MainWindow *window = new MainWindow();

    w.setCentralWidget(window);
    w.resize(1000, 300);
    w.show();

    return a.exec();
}
