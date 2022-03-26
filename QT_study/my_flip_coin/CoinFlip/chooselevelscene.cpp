#include "chooselevelscene.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    //设置窗口固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar *bar=this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu *startMenu=bar->addMenu("开始");
    //创建按钮菜单项
    QAction *quitAction=startMenu->addAction("退出");
    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){this->close();});

    //创建返回按钮
    MyPushButton* closeBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width()-closeBtn->width(),this->height()-closeBtn->height());
    connect(closeBtn,&MyPushButton::clicked,[=](){
//        closeBtn->zoom1();
//        closeBtn->zoom2();

        QTimer::singleShot(500,this,[=](){
           this->hide();
           emit this->chooseSceneBack();
        });
    });

    //创建关卡按钮
    for(int i=0;i<20;i++){
        MyPushButton *menuBtn=new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4)*70,130+(i/4)*70);
        //按钮上的文字
        QLabel *label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label->move(25+(i%4)*70,130+(i/4)*70);
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);//?????
        //监听选择关卡按钮的信号槽
        connect(menuBtn,&MyPushButton::clicked,[=](){
           if(pScene==NULL){
               QTimer::singleShot(500,this,[=](){
                   this->hide();
                   pScene=new PlayScene(i+1);//将选择的关号 传入给PlayerScene
                   pScene->show();
                   //监听PlayScene的返回信号,删除scene并且将指针指向空
                   connect(pScene,&PlayScene::playSceneBack,[=](){
                       this->show();
                       delete pScene;
                       pScene=NULL;
                   });
               });
           }
        });
    }



}

void ChooseLevelScene::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap(this->width()*0.5-pix.width()*0.5,30,pix.width(),pix.height(),pix);

}
