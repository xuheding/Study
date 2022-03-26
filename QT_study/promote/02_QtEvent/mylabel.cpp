#include "mylabel.h"
#include<QDebug>
#include<QEvent>
#include<QMouseEvent>
myLabel::myLabel(QWidget *parent)
    : QLabel{parent}
{
    //设置鼠标追踪状态
//    setMouseTracking(true);

}
//鼠标进入事件
void myLabel::enterEvent(QEnterEvent *event){
    //qDebug()<<"the mouse entered";
};
//鼠标离开事件
void myLabel::leaveEvent(QEvent *event){
    //qDebug()<<"the mouse left";

};

//鼠标按下
void myLabel::mousePressEvent(QMouseEvent *ev){

    //当鼠标左键按下
    if(ev->button()==Qt::LeftButton){
        QString str = QString("the mouse pressed x=%1  y=%2  globalX=%3  globalY=%4")
                .arg(ev->pos().x()).arg(ev->pos().y()).arg(ev-> globalPosition().x()).arg(ev->globalPosition().y());//(可以文档搜索arg用法,链式编程）
        qDebug()<<str;
    }


};
//鼠标释放
void myLabel::mouseReleaseEvent(QMouseEvent *ev){
    //鼠标点击和释放是一种瞬时状态，用button(文档中button:Returns the button that caused the event)
    if(ev->button()==Qt::LeftButton){
        QString str = QString("the mouse released x=%1  y=%2  globalX=%3  globalY=%4")
                .arg(ev->pos().x()).arg(ev->pos().y()).arg(ev-> globalPosition().x()).arg(ev->globalPosition().y());
        qDebug()<<str;
    }
};
//鼠标移动
void myLabel::mouseMoveEvent(QMouseEvent *ev){
    //由于鼠标移动是一种状态，因此要用buttons，只是其中包含了左键按下这个状态。因此要用&。（文档中Returns the button state when the event was generated. The button state is a combination ）
    if(ev->buttons()&Qt::LeftButton){
        QString str = QString("the mouse moved x=%1  y=%2  globalX=%3  globalY=%4")
                .arg(ev->pos().x()).arg(ev->pos().y()).arg(ev-> globalPosition().x()).arg(ev->globalPosition().y());
        qDebug()<<str;
    }
};

bool myLabel::event(QEvent *e){
    //如果是鼠标按下，在event事件分发中做拦截
    if(e->type()==QEvent::MouseButtonPress){
        QMouseEvent* ev= static_cast<QMouseEvent*>(e);
        QString str = QString("Event the mouse pressed x=%1  y=%2  globalX=%3  globalY=%4")
                .arg(ev->pos().x()).arg(ev->pos().y()).arg(ev-> globalPosition().x()).arg(ev->globalPosition().y());//(可以文档搜索arg用法,链式编程）
        qDebug()<<str;

        return true;//true代表用户自己处理这个事件，不向下分发(也就是说不会执行void myLabel::mousePressEvent)
    }
    //其他事件 交给父类处理（默认处理）
    return QLabel::event(e);
}

