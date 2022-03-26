#include "choselevelsense.h"
#include "mypushbutton.h"


#include<QMenuBar>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<QSound>

ChoseLevelSense::ChoseLevelSense(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡闯将
    this->setFixedSize(320,588);

    //设置图标
    this->setWindowIcon(QPixmap(":/res/window.png"));
    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar * bar=menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu=bar->addMenu("开始");

    //创建退出菜单项
    QAction * quitAciton=startMenu->addAction("退出");

    //点击退出实现退出游戏
    connect(quitAciton,&QAction::triggered,[=](){
        this->close();
    });

    QSound *mysound=new QSound(":/res/TapButtonSound.wav",this);
    //返回按钮
    MyPushButton * btnBack=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    btnBack->setParent(this);
    btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());

    //点击返回
    connect(btnBack,&QPushButton::clicked,[=](){
        qDebug()<<"点击了返回按钮";
        //告诉主场景  我返回了，主场景监听 ChooseLevelScence 的返回按钮
        QTimer::singleShot(500,this,[=](){
             emit this->choseScenseBack();
        });
    });

    //创建选择关卡的按钮
    for(int i=0;i<20;i++)
    {
        MyPushButton *btnMenu=new MyPushButton(":/res/LevelIcon.png");
        btnMenu->setParent(this);
        btnMenu->move(25+i%4*70,130+i/4*70);

        //监听每个按钮的点击事件
        connect(btnMenu,&MyPushButton::clicked,[=](){
            mysound->play();
            qDebug()<<QString("您选择的是第 %1 关").arg(i+1);

            // 进入到游戏场景
            this->hide();//将选关场景隐藏
            play =new PlaySence(i+1);
            //设置游戏场景的初始位置
            play->setGeometry(this->geometry());
            play->show();

            connect(play,&PlaySence::choseScenseBack,[=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play=NULL;
            });


        });

        //布局并显示按钮
        QLabel * label=new QLabel;
        label->setParent(this);
        label->setFixedSize(btnMenu->width(),btnMenu->height());
        label->setText(QString::number(i+1));
        label->setStyleSheet("QLabel{color:rgba(250, 0, 0, 255);}");
        label->move(25+i%4*70,130+i/4*70);
        label->setAlignment(Qt::AlignCenter);

        //让鼠标穿透label
        label->setAttribute(Qt::WA_TransparentForMouseEvents);



    }
}

void ChoseLevelSense::paintEvent(QPaintEvent *)
{
    // 加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/mainBg1.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    // 加载标题
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.8,pix.height()*0.8);
    painter.drawPixmap(10,30,pix);
//    pix.load(":/res/Title.png");
//    pix=pix.scaled(pix.width()*0.8,pix.height()*0.8);
//    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}

