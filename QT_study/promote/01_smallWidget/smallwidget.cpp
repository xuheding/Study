#include "smallwidget.h"
#include "ui_smallwidget.h"

smallWidget::smallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::smallWidget)
{
    ui->setupUi(this);
    //QSpinBox移动  QSlider跟着移动
    connect(ui->spinBox,&QSpinBox::valueChanged,ui->horizontalSlider,&QSlider::setValue);//查阅信号和槽函数文档即可
    //QSlider滑动  QSpinBox数字跟着改变
    connect(ui->horizontalSlider,&QSlider::valueChanged,ui->spinBox,&QSpinBox::setValue);

}

void smallWidget::setNum(int num){
    ui->spinBox->setValue(num);
}
int smallWidget::getNum(){
    return ui->spinBox->value();
}

smallWidget::~smallWidget()
{
    delete ui;
}
