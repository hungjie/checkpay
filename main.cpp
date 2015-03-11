#include "mainwindow.h"
#include <QApplication>

#include <QTextCodec>

#include <iostream>

#include "jsonencode.h"

int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    MainWindow* w = MainWindow::Instance();

    w->show();

    int status = a.exec();

    //qDebug() << w->myCookie()->save();

    delete w;

    std::cout << status;

    return status;
}
