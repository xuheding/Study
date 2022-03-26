#include "widget.h"
#include "./ui_widget.h"
#include<QPainter>//画家 类
#include<QTimer>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    //点击移动按钮   移动图片
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        //如果要手动调用绘图事件  用update更新
        posX+=20;
        update();
    });

    QTimer* timer=new QTimer(this);
    timer->start(1000);
    connect(timer,&QTimer::timeout,[=](){
        posX+=20;
        update();
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent *event){
//    //实例化画家对象   this指定的是绘图的设备(当前窗口)
//    QPainter painter(this);

//    //设置画笔
//    QPen pen(QColor(255,0,0));//创建画笔 （颜色）
//    pen.setWidth(3);//设置画笔宽度
//    pen.setStyle(Qt::DashLine);//设置画笔风格（帮助文档查看）


//    //设置画刷(填充)
//    QBrush brush(QColor(0,255,0));//或者可以直接输入颜色Qt::cyan
//    brush.setStyle(Qt::Dense6Pattern);//设置画刷风格

//    //让画家使用画笔/画刷
//    painter.setPen(pen);
//    painter.setBrush(brush);


//    //画线
//    painter.drawLine(QPoint(0,0),QPoint(100,100));
//    //画圆(圆就是特殊的椭圆)
//    painter.drawEllipse(QPoint(100,100),50,50);
//    //画矩形
//    painter.drawRect(QRect(20,20,50,50)); //左上角x,y,和w，h
//    //画文字
//    painter.drawText(QRect(10,200,100,50),"好好学习");//如果文本框的宽度不够会自动换行

    ////////////////////高级设置///////////////////////////

//    QPainter painter(this);

//    painter.drawEllipse(QPoint(100,50),50,50);

//    //设置 抗锯齿  效率较低
//    painter.setRenderHint(QPainter::Antialiasing);

//    painter.drawEllipse(QPoint(200,50),50,50);



//    painter.drawRect(QRect(20,20,50,50));//画矩形

//    painter.translate(100,0);//移动画家(整体向右平移100)

//    //保存画家状态(画家的位置)
//    painter.save();

//    painter.drawRect(QRect(20,20,50,50));//画矩形

//    painter.translate(100,0);//移动画家

//    //还原画家状态(画家回到保存点)
//    painter.restore();

//    painter.drawRect(QRect(20,20,50,50));//画矩形

//    //最后可以发现只有2个矩形，因为有2个矩形重叠了

    ////////////////////利用画家 画资源图片///////////////
    QPainter painter(this);

    //如果超出屏幕 从0开始
    if(posX>this->width()){
        posX=0;
    }
    painter.drawPixmap(posX,100,QPixmap(":/images/1.jpg").scaled(250,200));


}
