#include "widget.h"
#include<QPushButton> //按钮空间头文件
#include "mypushbutton.h"
#include "QDebug"
Widget::Widget(QWidget *parent)//实现构造函数
    : QWidget(parent)//初始化列表
{
    //创建一个按钮
    QPushButton *btn=new QPushButton();
    //btn->show();//show以顶层得方式弹出空间
    //让button对象 依赖在widget窗口中
    btn->setParent(this); //this就是当前对象的指针

    //显示文本
    btn->setText("第一个按钮");

    //创建第二个按钮  按照按钮的大小创建窗口(会影响窗口widget)
    QPushButton *btn2=new QPushButton("第二个按钮",this);

    //移动btn2按钮
    btn2->move(100,100);

    //设置按钮大小
    btn2->resize(50,50);

    //设置窗口大小(用户可以拖拽)
    resize(600,400);

    //设置固定窗口大小
    setFixedSize(600,400);

    //设置窗口标题
    setWindowTitle("第一个窗口");

    //创建一个自己的按钮对象
    MyPushButton *myBtn=new MyPushButton;
    myBtn->setText("我自己的按钮");
    myBtn->move(200,0);
    myBtn->setParent(this);//设置到对象树中


    //需求:点击我的按钮 关闭窗口
    //参数1:信号的发送者   参数2：发送的信号（函数地址）  参数3： 信号的接收者   参数4： 处理的槽函数
    connect(myBtn,&QPushButton::clicked,this,&QWidget::close);
//    connect(myBtn,&MyPushButton::clicked,this,&Widget::close);//因为继承关系，也可以直接通过这种调用信号和槽函数




}

Widget::~Widget()
{
    qDebug()<<"widget destructor";
}

//命名：
//   类名：首字母大写， 单词和单词之间首字母大写
//   函数名：首字母小写，单词和单词之间首字母大写

//快捷键
//  注释  ctrl+/
//  运行 ctrl+R
//  编译 ctrl+B
//  字体缩放 ctrl+鼠标滚轮
//  查找 ctrl+F
//  整行移动 ctrl + shift + ↑或者↓
//  帮助文档 选中代码+F1(点两次F1进入全屏，Esc退出)
//  自动对齐 ctrl+i
//  同名之间 .h和.cpp切换  F4


//帮助文档 第一种方式 F1  第二种 左侧按钮  第三种  直接去安装目录找文档 D:\QT\6.2.2\mingw_64\bin
