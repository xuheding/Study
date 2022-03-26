#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QDebug>
#include<QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString butImg);//代表图片路径

    int posX;//x坐标
    int posY;//y坐标
    bool flag;//正反标志


    void changeFlag();//改变标志，执行翻转效果
    void mousePressEvent(QMouseEvent *event);


    QTimer *timer1;
    QTimer *timer2;
    int min=1;//最小图片编号
    int max=8;//最大图片编号
    bool isAnimation=false;//在做翻转金币动画时，不能再进行翻转

    bool isWin=false;//胜利标志(胜利后要禁用按钮)
signals:

};

#endif // MYCOIN_H
