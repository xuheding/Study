#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include"mypushbutton.h"
#include"playscene.h"
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    PlayScene *pScene = NULL;

signals:
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
