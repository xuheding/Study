#include "mainscene.h"
#include "./ui_mainscene.h"
#include<QPainter>
#include"mypushbutton.h"
#include"chooselevelscene.h"
#include<QTimer>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //设置固定大小
    this->setFixedSize(320,588);
    //设置应用图片
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle("倪心愿来翻硬币啦");
    //点击退出，退出程序
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    //创建开始按钮
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

// 音效搞不出来
//    QMediaPlayer *startSound = new QMediaPlayer(this);
//    QAudioOutput *startSoundOutput = new QAudioOutput(this);
//    startSound->setAudioOutput(startSoundOutput);
//    connect(startSound, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
//    startSound->setSource(QUrl(":/res/LevelWinSound.wav"));
//    startSoundOutput->setVolume(50);



    connect(startBtn,&MyPushButton::clicked,[=](){
//       startSound->play();
       startBtn->zoom1();//向下跳跃
       startBtn->zoom2();//向上跳跃
       //选择关卡场景
       ChooseLevelScene *chooseScene = new ChooseLevelScene;
       //0.5秒后，进入选择场景
       QTimer::singleShot(500,this,[=](){
          this->hide();
          chooseScene->show();
       });
       connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
           this->show();
       });
    });


}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *event){
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/res/PlayLevelSceneBg.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    //缩放图片
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    //绘制标题
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);


}
