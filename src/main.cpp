#include <QApplication>
#include "mainwindow.h"
#include "ztextcodec.h"
#include "mplib.h"

class A{

};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMsgHandler(ZMsgHandler);
    ZTextCodec codec;
    codec.init("");
    MainWindow w;
    QFile file(":/stylesheet.css");
    if(file.open(QIODevice::ReadOnly))
    {
        qDebug()<<QString("���ļ�<%1>�ɹ�").arg(file.fileName());
        qApp->setStyleSheet(file.readAll());
    }
    else
    {
        qDebug()<<QString("���ļ�<%1>ʧ��").arg(file.fileName());
    }
//    int* a = 0;
//    qDebug()<<"sizeof "<<sizeof(A);
//    return -1;
    w.show();
    return a.exec();
}
