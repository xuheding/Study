#include "widget.h"
#include <QApplication>//包含一个应用程序类的头文件
#include <QLocale>
#include <QTranslator>

//main程序入口 argc命令行变量数量  argv命令行变量数组
int main(int argc, char *argv[])
{
    //a应用程序对象,在Qt中，应用程序对象 有且仅有一个
    QApplication a(argc, argv);

    //窗口对象 Widget父类->Qwidget
    Widget w;
    //窗口对象 默认不会显示，必须要调用show方法显示窗口
    w.show();
    //让应用程序对象进入消息循环(让代码阻塞到这行)
    return a.exec();

}

//1.Qt简介
// 1.1跨平台图形引擎
// 1.2历史
// 1.3优点
//  1.3.1跨平台
//  1.3.2接口简单，容易上手
//  1.3.3一定程度上简化了内存回收
// 1.4版本(商业、开源)
// 1.5成功案例
//2.创建第一个Qt项目
// 2.1点击创建项目，名称不能有中文和空格，路径不能有中文
// 2.2默认创建有3个窗口类
// 2.3main函数
//   2.3.1 QApplication a 应用程序对象，有且仅有一个
//   2.3.2 myWidget w;实例化窗口对象
//   2.3.3 w.show();调用show函数 显示窗口
//   2.3.4 return a.exec(); 让应用程序进入消息循环机制中，代码阻塞到当前行
