#include "mainwindow.h"
#include <QApplication>
#include "GraphWidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("GAZORPAZORPFIELD");
    MainWindow w;
    w.setWindowTitle("GAZORPAZORPFIELD");
    w.show();

    return a.exec();
}
