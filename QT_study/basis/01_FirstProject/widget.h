#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>//包含头文件 QWidget 窗口类

class Widget : public QWidget
{
    Q_OBJECT  //Q_OBJECT宏，允许类中使用信号和槽的机制

public:
    Widget(QWidget *parent = nullptr);//有参构造函数
    ~Widget();//析构函数
};
#endif // WIDGET_H
