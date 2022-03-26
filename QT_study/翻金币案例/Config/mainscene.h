#ifndef MAINSCENE_H
#define MAINSCENE_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include "choselevelsense.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //重写paintEvent事件  画背景图
    void paintEvent(QPaintEvent *);

    ChoseLevelSense *chooseScene=NULL;

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
