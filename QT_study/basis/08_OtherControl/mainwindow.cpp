#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QMovie>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //栈控件使用

    //设置默认页面
    ui->stackedWidget->setCurrentIndex(0);

    //按钮->切换页面
    connect(ui->btn_scrollArea,&QPushButton::clicked,[=](){//scrollArea按钮
       ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->btn_toolBox,&QPushButton::clicked,[=](){//toolBox按钮
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->btn_tabWidget,&QPushButton::clicked,[=](){//tabWidget按钮
        ui->stackedWidget->setCurrentIndex(2);
    });

    //下拉框
    ui->comboBox->addItem("奔驰");
    ui->comboBox->addItem("宝马");
    ui->comboBox->addItem("拖拉机");


    connect(ui->btn_select,&QPushButton::clicked,[=](){
//        ui->comboBox->setCurrentIndex(2);
        ui->comboBox->setCurrentText("拖拉机");
    });

    //利用QLabel显示图片
    ui->lbl_image->setPixmap(QPixmap(":/image/1.png"));

    //利用QLabel显示gif动态图片
    QMovie *movie = new QMovie(":/image/2.gif");
    ui->lbl_image->setMovie(movie);
    //播放动图
    movie->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

