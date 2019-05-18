#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QPixmap(":/gamnashka"));
    MainWindow w;
    w.show();

    return a.exec();
}
