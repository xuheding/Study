#include "mainwindow.h"
#include<QMenuBar>
#include<QToolBar>
#include<QPushButton>
#include<QStatusBar>
#include<QLabel>
#include<QDebug>
#include<QDockWidget>
#include<QTextEdit>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //重置窗口大小
    this->resize(600,400);




    /*菜单栏创建(只能有一个)*/
    QMenuBar *bar = menuBar();
    //将菜单栏放入到窗口中 (此时还没添加内容，因此看起来是空的)
    this->setMenuBar(bar);
    //创建菜单
    QMenu *fileMenu = bar->addMenu("文件");
    QMenu *editMenu = bar->addMenu("编辑");
    //创建菜单项
    QAction* newAct = fileMenu->addAction("新建");
    fileMenu->addSeparator();//添加分隔线
    QAction* openAct = fileMenu->addAction("打开");




    /*工具栏(可以有多个)*/
    QToolBar *toolBar = new QToolBar(this);
    this->addToolBar(Qt::LeftToolBarArea,toolBar);//qt中所有的枚举值，都是Qt::开头的,可以查看帮助文档
    //后期设置  只允许左边停靠
    toolBar->setAllowedAreas(Qt::LeftToolBarArea|Qt::RightToolBarArea);
    //设置不能浮动(只能停靠)
    toolBar->setFloatable(false);
    //设置移动(总开关)
    toolBar->setMovable(false);
    //工具栏中可以设置内容
    toolBar->addAction(newAct);
    toolBar->addSeparator();//添加分割线
    toolBar->addAction(openAct);
    //工具栏中添加控件
    QPushButton* btn = new QPushButton("aa",this);
    toolBar->addWidget(btn);





    /*状态栏（最多只有一个）*/
    QStatusBar* stBar = statusBar();
    //QStatusBar* stBar = new QStatusBar();//new也是可以的
    //设置到窗口中
    this->setStatusBar(stBar);
    //放标签控件
    QLabel *label1 = new QLabel("提示信息",this);
    stBar->addWidget(label1);
    QLabel *label2 = new QLabel("右侧提示信息",this);
    stBar->addPermanentWidget(label2);





    /*铆接部件(浮动窗口) （可以有多个）*/
    QDockWidget* dockWidget = new QDockWidget("浮动",this);
    this->addDockWidget(Qt::BottomDockWidgetArea,dockWidget);//是在中心部件的下方，(如果中心部件为空，可能导致看起来是在上方)
    //设置后期停靠区域,只允许上下
    dockWidget->setAllowedAreas(Qt::TopDockWidgetArea|Qt::BottomDockWidgetArea);





    /*设置中心部件(只能有一个)*/
    QTextEdit* edit = new QTextEdit(this);
    this->setCentralWidget(edit);


}

MainWindow::~MainWindow()
{
}

