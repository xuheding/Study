#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置单选按钮  “男”默认选中
    ui->rBtnMan->setChecked(true);

    //选中单选按钮“女”  打印信息
    connect(ui->rBtnWoman,&QRadioButton::clicked,[=](){
       qDebug()<<"select woman!";
    });

    //多选按钮  2是选中， 0是未选中
    connect(ui->cBox,&QCheckBox::stateChanged,[=](int state){
       qDebug()<<state;
    });

    //利用listWidget写诗
    QListWidgetItem *item = new QListWidgetItem("锄禾日当午");
    //将一行的诗放入listWidget控件中
    ui->listWidget->addItem(item);
    //设置listWidgetitem的对齐格式
    item->setTextAlignment(Qt::AlignHCenter);//（查阅文档）

    //在listWidget中利用addItems一次性加入多行。
    QStringList list;
    list<<"锄禾日当午"<<"汗滴禾下土"<<"谁知盘中餐"<<"粒粒皆辛苦";//QStringList重载了<<运算符，每次都会自动换行
    ui->listWidget->addItems(list);

}

Widget::~Widget()
{
    delete ui;
}

