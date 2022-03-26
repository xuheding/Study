#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include "mypushbutton.h"
#include<QTimer>
#include<QSound> //多媒体模块下的音效，需要在.pro 中加入 QT += multimedia 模块，详见帮助文档


MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //1.配置主场景

    setFixedSize(320,588);/*设置固定大小*/
    setWindowIcon(QIcon(":/res/window.png"));/*设置背景图片*/
    setWindowTitle("金币案例");/*设置标题*/
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });/*退出按钮实现*/

    //准备开始按钮的音效
    QSound* startSound=new QSound(":/res/BackButtonSound.wav",this);



    MyPushButton* startBtn=new MyPushButton(":/res/MenuSceneStartButton.png");/*开始按钮*/
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);/*宽度：屏幕宽度一半减去按钮宽度的一半，高度：水边设置*/


    //实例化选择关卡场景
    chooseScene=new ChoseLevelSense;
    /*监听选择关卡的返回按钮的信号*/
    connect(chooseScene,&ChoseLevelSense::choseScenseBack,this,[=](){
       this->setGeometry(chooseScene->geometry());
        chooseScene->hide();//将选择的关卡场景 隐藏掉
        this->show();
    });


    connect(startBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"点击开始";

        // 播放开始音效资源
        startSound->play();
        //弹起特效
        startBtn->zoom1();
        startBtn->zoom2();
        //延时进入到选择关卡场景中 自身隐藏
        QTimer::singleShot(500,this,[=](){
            chooseScene->setGeometry(this->geometry());//每次切换场景都保持位置一致
            this->hide();/*自身隐藏*/
            chooseScene->show();/*选择关卡场景*/
        });

    });

}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter resPainter(this);
//    QPixmap pix;
//    pix.load(":/res/MenuSceneBg.png");
    resPainter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/res/mainBg1.png"));

    //画背景图标
    QPixmap pix;
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.8,pix.height()*0.8);
    resPainter.drawPixmap(10,30,pix);


}

