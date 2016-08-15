#include "widget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include "Global.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if 1
    QSize sizeTmp=a.desktop()->size();
    qDebug()<<"phone ui size : "<<sizeTmp;
    GLOBAL().g_sizeWindow=QSize(sizeTmp.width(),sizeTmp.height()-76);

#ifdef Q_OS_MAC
    GLOBAL().g_sizeWindow=QSize(sizeTmp.width(),sizeTmp.height());
#endif







    float fTitleH=float(WIDONW_H*0.1);
    TOP_MENU_H=fTitleH;
#else
    GLOBAL().g_sizeWindow=QSize(1080,1776)*4/10;
    float fTitleH=float(WIDONW_H*0.1);
    TOP_MENU_H=fTitleH*0.7;
#endif

    Widget w;
    w.resize(GLOBAL().g_sizeWindow);
    w.show();

    return a.exec();
}
