#include "playsence.h"
#include "mypushbutton.h"
#include "mycoin.h"
#include<QMenuBar>
#include<QPainter>
#include<QIcon>
#include<QTimer>
#include<QLabel>
#include<QPropertyAnimation>
#include<QSound>

//PlaySence::PlaySence(QWidget *parent) : QMainWindow(parent)
//{

//}

PlaySence::PlaySence(int levelNum)
{
   qDebug()<<QString("进入了第 %1 关").arg(levelNum);
   this->levelIndex=levelNum;

   //初始化游戏场景
   this->setFixedSize(320,588);/*设置固定大小*/
   this->setWindowIcon(QPixmap(":/res/Coin0001.png"));/*设置图标*/
   this->setWindowTitle(QString("游戏场景 %1").arg(levelNum));

   //创建菜单栏
   QMenuBar * bar=menuBar();
   setMenuBar(bar);
   //创建开始菜单
   QMenu * startMenu=bar->addMenu("开始");

   //创建退出菜单项
   QAction * quitAciton=startMenu->addAction("退出");

   //音效
   QSound *mysound=new QSound(":/res/ConFlipSound.wav",this);
   QSound *winsound=new QSound(":/res/LevelWinSound.wav",this);

//   QMediaPlayer * player = new QMediaPlayer;
//   player->setMedia(QUrl::fromLocalFile("F:/QTproj/data820/learn/Config/res/winGain.mp3"));
//   player->setVolume(50);
//   player->play();
   endPlayer=new QMediaPlayer(this);




   //点击退出实现退出游戏
   connect(quitAciton,&QAction::triggered,[=](){
       this->close();
   });

   //返回按钮
   MyPushButton * btnBack=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
   btnBack->setParent(this);
   btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());

   //点击返回
   connect(btnBack,&QPushButton::clicked,[=](){
       qDebug()<<"游戏场景中点击了返回按钮";
       //告诉主场景  我返回了，主场景监听 ChooseLevelScence 的返回按钮
       QTimer::singleShot(500,this,[=](){
            emit this->choseScenseBack();
       });
   });


   //显示当前关卡数
   QLabel *label=new QLabel;
   label->setParent(this);
   QFont font;
   font.setFamily("华为新魏");
   font.setPointSize(15);
   //将字体设置到标签控件中
   label->setFont(font);
   label->setText(QString("Level:%1").arg(this->levelIndex));
//   label->setStyleSheet("QLabel{border-radius: 4px;color:rgb(0,199,140);}");
//   label->setStyleSheet("QLabel{color:rgb(0,199,140);}");
   label->setStyleSheet("QLabel{background:rgba(255,0,0,128);}");
   label->setGeometry(50,this->height()-30,110,30);
   //label->move(100,500);


   dataConfig config;
  //初始化每个关卡的二维数组
   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
       }
   }


   //胜利图片的显示
   QLabel *winLabel=new QLabel;
   QPixmap tmpPix;
   tmpPix.load(":/res/LevelCompletedDialogBg.png");
   winLabel->setParent(this);
   winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
   winLabel->setPixmap(tmpPix);
   winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());

   //显示金币的背景图
   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           //绘制背景图片
           QPixmap pix=QPixmap(":/res/BoardNode(1).png");
           QLabel *label=new QLabel;
           label->setGeometry(0,0,50,50);
           label->setPixmap(pix);
           label->setParent(this);
           label->move(57+i*50,200+j*50);

           //创建金币
           QString str;
           if(this->gameArray[i][j]==1)
           {
               //显示金币
               str=":/res/Coin0001.png";

           }
           else{
               str=":/res/Coin0008.png";
           }

           MyCoin *coin=new MyCoin(str);
           coin->setParent(this);
           coin->move(59+i*50,204+j*50);

           //给金币的属性赋值
           coin->posX=i;
           coin->posY=j;
           coin->flag=this->gameArray[i][j]; //  1正面 0反面

           //将金币放入到金币的二维数组里面 以便于后期的维护
           coinBtn[i][j]=coin;


           //点击金币进行翻转
           connect(coin,&MyCoin::clicked,[=](){
               coin->changeFlag();
               mysound->play();
               this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;

               QTimer::singleShot(300,this,[=](){
                   // 翻转周围硬币的操作，延时翻转
                   if(coin->posX+1<=3){// 周围的右侧硬币翻转的条件
                       coinBtn[coin->posX+1][coin->posY]->changeFlag();
                       this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0?1:0;

                   }
                   if(coin->posX-1>=0) // 周围左侧硬币的翻转条件
                   {
                       coinBtn[coin->posX-1][coin->posY]->changeFlag();
                       this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0?1:0;
                   }
                   if(coin->posY+1<=3) // 周围下侧硬币的翻转条件
                   {
                       coinBtn[coin->posX][coin->posY+1]->changeFlag();
                       this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0?1:0;
                   }
                   if(coin->posY-1>=0) // 周围上侧硬币的翻转条件
                   {
                       coinBtn[coin->posX][coin->posY-1]->changeFlag();
                       this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0?1:0;
                   }

                   //判断是否胜利
                   this->isWin=true;
                   for(int i=0;i<4;i++)
                   {
                       for(int j=0;j<4;j++){
                           if(coinBtn[i][j]->flag==false){
                               this->isWin=false;
                               break;
                           }
                       }
                   }

                   if(this->isWin==true){
                       //胜利了
                       qDebug()<<"游戏胜利";
                       //winsound->play();
                       endPlayer->setMedia(QUrl::fromLocalFile("F:/QTproj/data820/learn/Config/res/bkmusic.mp3"));
                       endPlayer->setMedia(QUrl("qrc:/res/bkmusic.mp3"));
                       endPlayer->setVolume(100);
                       endPlayer->play();






                       //将所有按钮胜利的标志改为 true,如果再次点击按钮直接return
                       for(int i=0;i<4;i++)
                       {
                           for(int j=0;j<4;j++){
                               coinBtn[i][j]->isWin=true;
                           }
                       }

                       //将胜利的图片移动下来
                       QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
                       //设置时间间隔
                       animation->setDuration(1000);

                       //设置开始位置
                       animation->setStartValue(QRect(QPoint(winLabel->x(),winLabel->y()),QPoint(winLabel->x()+winLabel->width(),winLabel->height())));
                       //设置结束位置
                       animation->setEndValue(QRect(QPoint(winLabel->x(),winLabel->y()+120),QPoint(winLabel->x()+winLabel->width(),winLabel->height()+120)));

                       //设置缓和曲线
                       animation->setEasingCurve(QEasingCurve::OutBounce);
                       //执行动画
                       animation->start();
                       //


                   }

               });

           });

       }
   }





}

void PlaySence::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    icomShow(":/res/mainBg1.png",":/res/Title.png",&painter);

}

void PlaySence::icomShow(QString path1,QString path2,QPainter* painter)
{
    QPixmap pix;
    bool ret=pix.load(path1);
    if(!ret){
        qDebug()<<"图片加载失败";
        return;
    }

    painter->drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(path2);
    pix=pix.scaled(pix.width()*0.8,pix.height()*0.8);
    painter->drawPixmap(10,30,pix.width(),pix.height(),pix);
}
