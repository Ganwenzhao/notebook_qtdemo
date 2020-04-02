#include "mainwindow.h"
#include <QtDebug>
#include <QDesktopWidget>
#include <QTextCodec>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));//设置utf-8

    MainWindow w;

    QSettings setting("config.ini",QSettings::IniFormat);//生成配置文件
    setting.beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
    if(setting.value("status_bar").isNull())
        setting.setValue("status_bar",QVariant("1"));
    if(setting.value("auto_go_line").isNull())
        setting.setValue("auto_go_line",QVariant("1"));
    setting.endGroup();


    QDesktopWidget *desktop=QApplication::desktop();
    //居中显示
    w.move((desktop->width()-w.width())/2,(desktop->height()-w.height())/2);

    w.show();
    return a.exec();
}
