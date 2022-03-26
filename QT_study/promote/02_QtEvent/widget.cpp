#include "widget.h"
#include "./ui_widget.h"
#include<QTimerEvent>
#include<QTimer>//定时器类
#include<QMouseEvent>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //启动定时器
    id1 = startTimer(1000);  //参数1：间隔(单位毫秒)
    id2 = startTimer(2000);

    //定时器第二种方式
    QTimer *timer = new QTimer(this);
    //启动定时器
    timer->start(500);//500毫秒

    connect(timer,&QTimer::timeout,[=](){
        static int num=1;
        //label4 每隔0.5秒+1
        ui->label_4->setText(QString::number(num++));
    });

    //点击暂停按钮  实现停止定时器
    connect(ui->btn,&QPushButton::clicked,[=](){
        timer->stop();
    });

    //给label1 安装事件过滤器
    //步骤1：安装事件过滤器
    ui->label->installEventFilter(this);

}

//步骤2：重写eventfilter
bool Widget::eventFilter(QObject *watched, QEvent *event){
    if(watched==ui->label){
        if(event->type()==QEvent::MouseButtonPress){
            QMouseEvent* ev= static_cast<QMouseEvent*>(event);
            QString str = QString("EventFilter the mouse pressed x=%1  y=%2  globalX=%3  globalY=%4")
                    .arg(ev->pos().x()).arg(ev->pos().y()).arg(ev-> globalPosition().x()).arg(ev->globalPosition().y());//(可以文档搜索arg用法,链式编程）
            qDebug()<<str;

            return true;//true代表用户自己处理这个事件，不向下分发(也就是说不会执行void myLabel::mousePressEvent)
        }
    }
    //其他默认处理(交给父类处理)
    return QWidget::eventFilter(watched,event);
}


Widget::~Widget()
{
    delete ui;
}


void Widget::timerEvent(QTimerEvent *e){

    if(e->timerId()==id1){
        //int num=1;  //如果不是静态变量，这个局部变量导致最终label显示的文本都是1
        static int num=1; //变量初始化调用一次，后面不会再调用。单例模式就是用这个来的
        //设置文本(每隔1秒+1)
        ui->label_2->setText(QString::number(num++));//将int转为QString
    }
    else if(e->timerId()==id2){
        //设置文本(每隔2秒+1)
        static int num2=1;
        ui->label_3->setText(QString::number(num2++));//将int转为QString
    }
}
