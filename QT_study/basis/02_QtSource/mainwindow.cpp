#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->actionNew->setIcon(QIcon("E:\\code\\QT_study\\02_QtSource\\Image\\1.jpg"));
    //使用添加Qt资源 ":+前缀名+文件名"
    ui->actionNew->setIcon(QIcon(":/Image/1.jpg"));
    ui->actionOpen->setIcon(QIcon(":/Image/2.png"));//再设置一个icon试试
}

MainWindow::~MainWindow()
{
    delete ui;
}

