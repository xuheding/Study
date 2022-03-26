#include "widget.h"
#include "./ui_widget.h"
#include<QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建一个老师对象
    this->zt=new Teacher(this);
    //创建一个学生对象
    this->st=new Student(this);

//    //老师饿了  学生请客的连接
//    connect(zt,&Teacher::hungry,st,&Student::treat);
//    //调用下课函数
//    classIsOver();

    //连接带参数的 信号和槽
    void(Teacher::*teacherSignal)(QString) = &Teacher::hungry;//定义一个函数指针,指向有参的
    void(Student::*studentSlot)(QString) = &Student::treat;
//    connect(zt,&Teacher::hungry,st,&Student::treat);如果直接传这个会产生二义性，因为重载了一个有参的。如果没有重载，可以这么用
    connect(zt,teacherSignal,st,studentSlot);

//    classIsOver();

    //点击一个 下课按钮，再触发下课
    QPushButton *btn = new QPushButton("classOver",this);
    //重置窗口大小
    this->resize(600,400);
    //点击按钮  触发下课
//    connect(btn,&QPushButton::clicked,this,&Widget::classIsOver);

    //无参信号和槽连接
    void(Teacher::*teacherSignal2)(void) = &Teacher::hungry;
    void(Student::*studentSlot2)(void) = &Student::treat;
    connect(zt,teacherSignal2,st,studentSlot2);
    //信号连接信号
    connect(btn,&QPushButton::clicked,zt,teacherSignal2);

    //断开信号(参数是和connect一样的)
//    disconnect(zt,teacherSignal2,st,studentSlot2);

    //扩展
    //1。信号是可以连接信号
    //2.一个信号 可以连接 多个槽函数
    //3.多个信号 可以连接 同一个槽函数
    //4.信号和槽函数的参数  必须类型一一对应
    //5.信号和槽的参数个数是不是要一致？ 信号参数的个数 可以多余槽参数个数。 反之不行

    connect(btn,&QPushButton::clicked,this,&Widget::close);


    //lambda表达式作为信号槽连接的槽函数 (mutable关键字，用于修饰值传递变量，使得值传递拷贝的结果可以修改)
    QPushButton* btn2=new QPushButton("second btn",this);
    btn2->move(100,100);
    int m=100;
    connect(btn2,&QPushButton::clicked,this,[m]()mutable{m=m+10;qDebug()<<m;});

    //lambda表达式，如果返回int, 返回值用->int。直接加括号可以调用
    int ret=[m]()->int{return m;}();
    qDebug()<<"ret = "<<ret;

    //利用lambda表示，实现点击按钮，关闭窗口
    QPushButton *btn3=new QPushButton("close widget",this);
    btn3->move(300,100);
    connect(btn3,&QPushButton::clicked,this,[this](){
        emit zt->hungry("chicken");
        this->close();
    });

    //如果第3个参数是this，使用lambda表达式，可以省略第三个参数,直接输入lambda表达式就行
    connect(btn3,&QPushButton::clicked,[this](){
        emit zt->hungry("chicken");
        this->close();
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::classIsOver()
{
    //下课函数，调用  出发老师饿了信号
//    emit zt->hungry();//emit表示发射信号的意思

    emit zt->hungry("chicken");
}
