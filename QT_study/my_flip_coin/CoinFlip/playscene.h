#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QMenuBar>
#include<QMenu>
#include<QPainter>
#include"mypushbutton.h"
#include<QPaintEvent>
#include<QTimer>
#include<QLabel>
#include<mycoin.h>
#include"dataconfig.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);
    //有参构造
    PlayScene(int index);

    //记录关卡索引
    int levelIndex;
    void paintEvent(QPaintEvent *e);

    int gameArray[4][4];//二维数组数据

    MyCoin *coinBtn[4][4];//金币按钮数组
    bool isWin=true;//是否胜利
signals:
    void playSceneBack();
};

#endif // PLAYSCENE_H
