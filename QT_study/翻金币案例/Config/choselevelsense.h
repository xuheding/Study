#ifndef CHOSELEVELSENSE_H
#define CHOSELEVELSENSE_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include "playsence.h"

class ChoseLevelSense : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChoseLevelSense(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent* );

    //游戏场景的绘图指针
    PlaySence *play=NULL;

signals:
    //写一个自定义信号，告诉主场景 点击了返回
    void choseScenseBack();


};

#endif // CHOSELEVELSENSE_H
