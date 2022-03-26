#include "mycoin.h"

MyCoin::MyCoin(QWidget *parent)
    : QPushButton{parent}
{

}

MyCoin::MyCoin(QString butImg){
    QPixmap pixmap;
    bool ret=pixmap.load(butImg);
    if(!ret){
        qDebug()<<butImg<<"load img fail";
    }
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));

    //初始化定时器
    timer1=new QTimer(this);
    timer2=new QTimer(this);

    //翻转金币 正->反
    connect(timer1,&QTimer::timeout,[=](){
       QPixmap pixmap;
       QString str=QString(":/res/Coin000%1.png").arg(this->min++);
       pixmap.load(str);
       this->setFixedSize(pixmap.width(),pixmap.height());
       this->setStyleSheet("QPushButton{border:0px;}");
       this->setIcon(pixmap);
       this->setIconSize(QSize(pixmap.width(),pixmap.height()));
       if(this->min==this->max){
           this->min=1;
           isAnimation=false;//结束了翻转，因此还能翻转
           timer1->stop();
       }
    });

    //翻转金币 反->正
    connect(timer2,&QTimer::timeout,[=](){
       QPixmap pixmap;
       QString str=QString(":/res/Coin000%1.png").arg(this->max--);
       pixmap.load(str);
       this->setFixedSize(pixmap.width(),pixmap.height());
       this->setStyleSheet("QPushButton{border:0px;}");
       this->setIcon(pixmap);
       this->setIconSize(QSize(pixmap.width(),pixmap.height()));
       if(this->min==this->max){
           this->max=8;
           isAnimation=false;
           timer2->stop();
       }
    });
}

//改变标志，执行翻转效果
void MyCoin::changeFlag(){
    if(this->flag){//如果是正面，执行下列代码
        timer1->start(30);
        isAnimation=true;//启动翻转，因此要禁止再翻转
        this->flag=false;
    }
    else{//反面执行下列代表
        timer2->start(30);
        isAnimation=true;
        this->flag=true;
    }

}


void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation||isWin==true){//在翻动过程中或者胜利后，不能再按下按钮
        return;
    }
    else{
        return QPushButton::mousePressEvent(e);//触发了这个时间会触发信号click
    }
}






