#include "widget.h"
#include "./ui_widget.h"
#include<QPixmap>
#include<QPainter>
#include<QPicture>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//    //Pixmap绘图设备（专门为平台做了显示优化）
//    QPixmap pix(300,300);
//    //填充颜色(背景)
//    pix.fill(Qt::white);
//    //声明画家
//    QPainter painter(&pix);
//    painter.setPen(QPen(Qt::green));
//    //画圆
//    painter.drawEllipse(QPoint(150,150),100,100);
//    //保存图片
//    pix.save("E:\\1.png");

//    //QImage 绘图设备 (可以对像素进行访问)
//    QImage img(300,300,QImage::Format_RGB32);
//    img.fill(Qt::white);
//    QPainter painter(&img);
//    painter.setPen(QPen(Qt::green));
//    painter.drawEllipse(QPoint(150,150),100,100);
//    img.save("E:\\2.png");


    //QPicture 绘图设备 （可以记录和重现绘图指令）
    QPicture pic;//无参构造不要加括号，否则会被当作成函数声明
    QPainter painter;
    painter.begin(&pic);//开始画画(可以指定设备。这行和上面这行等效于QPainter painter(&pic);)
    painter.setPen(QPen(Qt::cyan));
    painter.drawEllipse(QPoint(150,150),100,100);
    painter.end();//结束画画

    //保存到磁盘
    pic.save("E:\\pic.zt");//里面记录着所有绘图的指令



}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPicture pic;
    pic.load("E:\\pic.zt");
    painter.drawPicture(0,0,pic);
}
