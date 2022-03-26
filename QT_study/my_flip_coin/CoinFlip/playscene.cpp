#include "playscene.h"

PlayScene::PlayScene(QWidget *parent)
    : QMainWindow{parent}
{

}

PlayScene::PlayScene(int index){
    this->levelIndex=index;
    //设置窗口固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币");

    //创建菜单栏
    QMenuBar *bar=this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu *startMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction *quitAction = startMenu->addAction("退出");
    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){this->close();});


    //返回按钮
    MyPushButton* closeBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width()-closeBtn->width(),this->height()-closeBtn->height());
    //返回按钮的功能实现
    connect(closeBtn,&MyPushButton::clicked,[=](){
        QTimer::singleShot(500,this,[=](){
            this->hide();
            //触发自定义信号，关闭自身，该信号写到signals下做声明
            emit this->playSceneBack();
        });
    });

    //当前关卡标题
    QLabel *label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str=QString("Level:%1").arg(this->levelIndex);
    label->setText(str);
    label->setGeometry(QRect(30,this->height()-50,120,50));//设置位置和大小

    //提前创建胜利的图片
    QLabel *winLabel=new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());//先隐藏好，如果触发胜利了，将图片弹下来就好

    dataConfig config;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            //绘制金币背景图片
            QLabel *label=new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);

            //金币对象
            gameArray[i][j]=config.mData[this->levelIndex][i][j];
            QString img;
            if(gameArray[i][j]==1){
                img=":/res/Coin0001.png";
            }
            else{
                img=":/res/Coin0008.png";
            }
            MyCoin *coin=new MyCoin(img);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->posX=i;//记录x坐标
            coin->posY=j;//记录y坐标
            coin->flag=gameArray[i][j];//标记正反标志

            coinBtn[i][j]=coin;//记录每个金币按钮
            connect(coin,&MyCoin::clicked,[=](){//建立翻转金币的信号槽
               coin->changeFlag();//翻转金币
               gameArray[i][j]=gameArray[i][j]==0?1:0;//数组记录的标志同步修改
               //翻动其他周围硬币
               QTimer::singleShot(300,this,[=](){
                  if(coin->posX+1<=3){
                      coinBtn[coin->posX+1][coin->posY]->changeFlag();
                      gameArray[coin->posX+1][coin->posY]==0?1:0;
                  }
                  if(coin->posX-1>=0){
                      coinBtn[coin->posX-1][coin->posY]->changeFlag();
                      gameArray[coin->posX-1][coin->posY]==0?1:0;
                  }
                  if(coin->posY+1<=3){
                      coinBtn[coin->posX][coin->posY+1]->changeFlag();
                      gameArray[coin->posX][coin->posY+1]==0?1:0;
                  }
                  if(coin->posY-1>=0){
                      coinBtn[coin->posX][coin->posY-1]->changeFlag();
                      gameArray[coin->posX][coin->posY-1]==0?1:0;
                  }

                  //判断是否胜利
                  this->isWin=true;
                  for(int i=0;i<4;i++){
                      for(int j=0;j<4;j++){
                          if(coinBtn[i][j]->flag==false){
                              this->isWin=false;
                              break;
                          }
                      }
                  }
                  //如果胜利
                  if(this->isWin){
                      qDebug()<<"win";
                      QPropertyAnimation *animation1=new QPropertyAnimation(winLabel,"geometry");
                      animation1->setDuration(1000);
                      animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                      animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                      animation1->setEasingCurve(QEasingCurve::OutBounce);
                      animation1->start();
                      for(int i=0;i<4;i++){
                          for(int j=0;j<4;j++){
                              coinBtn[i][j]->isWin=true;
                          }
                      }
                  }
               });


            });

        }
    }




}


void PlayScene::paintEvent(QPaintEvent *e){
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
