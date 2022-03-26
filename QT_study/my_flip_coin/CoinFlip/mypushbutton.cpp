#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget *parent)
    : QPushButton{parent}
{

}

MyPushButton::MyPushButton(QString normalImg,QString pressImg){
    normalImgPath=normalImg;
    pressedImgPath=pressImg;
    QPixmap pixmap;
    bool ret=pixmap.load(normalImgPath);
    if(!ret){
        qDebug()<<normalImg<<"load img fail";
    }
    //设置图片固定尺寸
    this->setFixedSize(pixmap.width(),pixmap.height());
    //设置不规则图片的样式表
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pixmap);
    //设置图标大小
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));

}

//向下弹跳动画
void MyPushButton::zoom1(){
    //创建动画对象
    QPropertyAnimation *animation1=new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animation1->setDuration(200);
    //设置起始位置
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置缓和曲线
    animation1->setEasingCurve(QEasingCurve::OutBounce);//弹跳效果
    //开始执行动画
    animation1->start();
}

//向上弹跳动画
void MyPushButton::zoom2(){
    //创建动画对象
    QPropertyAnimation *animation1=new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animation1->setDuration(200);
    //设置起始位置
    animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //创建结束位置
    animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置缓和曲线
    animation1->setEasingCurve(QEasingCurve::OutBounce);//弹跳效果
    //开始执行动画
    animation1->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *event){
    if(pressedImgPath!=""){
        QPixmap pixmap;
        bool ret=pixmap.load(pressedImgPath);
        if(!ret){
            qDebug()<<pressedImgPath<<"load img fail";
            return;
        }
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    //交给父类执行按下事件
    return QPushButton::mousePressEvent(event);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *event){
    if(normalImgPath!=""){
        QPixmap pixmap;
        bool ret=pixmap.load(normalImgPath);
        if(!ret){
            qDebug()<<normalImgPath<<"load img fail";
            return;
        }
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    //交给父类执行按下事件
    return QPushButton::mouseReleaseEvent(event);
}


