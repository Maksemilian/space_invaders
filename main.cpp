#include "main_window.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<"Main";
    MainWindow w;
    w.show();

    return a.exec();
}
