#include "mainscene.h"


#include <QApplication>
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScene w;
    w.show();

    //测试关卡数据
//    dataConfig config;
//    for(int i=0;i<4;i++)
//    {
//        for(int j=0;j<4;j++)
//        {
//            qDebug()<<config.mData[1][i][j];
//        }
//        qDebug()<<"";
//    }

//       QMediaPlayer * player = new QMediaPlayer;
//       player->setMedia(QUrl::fromLocalFile("F:/QTproj/data820/learn/Config/res/winGain.mp3"));
//       player->setVolume(50);
//       player->play();
//    QMediaPlayer *endPlayer1=new QMediaPlayer;
//    endPlayer1->setMedia(QUrl("qrc:/res/bkmusic.mp3"));// 设置相对路径
//    endPlayer1->setVolume(50);
//    endPlayer1->play();

    return a.exec();
}
