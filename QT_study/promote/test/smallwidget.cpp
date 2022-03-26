#include "smallwidget.h"
#include "ui_smallwidget.h"

smallWidget::smallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::smallWidget)
{
    ui->setupUi(this);
    connect(ui->spinBox,&QSpinBox::valueChanged,ui->horizontalSlider,&QSlider::setValue);
    connect(ui->horizontalSlider,&QSlider::valueChanged,ui->spinBox,&QSpinBox::setValue);

}

smallWidget::~smallWidget()
{
    delete ui;
}

void smallWidget::setNum(int num){
    ui->spinBox->setValue(num);
}
int smallWidget::getNum(){
    return ui->spinBox->value();
}
