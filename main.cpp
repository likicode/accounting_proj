#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    //QTextCodec::setCodeForTr(QTextCodec::codecForLocale());
    Q_INIT_RESOURCE(images);
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
