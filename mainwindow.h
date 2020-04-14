#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>
#include <QPixmap>
#include <QObject>
#include <QPainter>
#include <QRectF>
#include <QPainter>
#include "level_1.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    void mapGen();
    explicit MainWindow(QWidget *parent = nullptr);
    void character_turn_back();
    void character_turn_front();
    void character_turn_left();
    void character_turn_right();
    void drawBackground(QPainter *painter, const QRectF &rect);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::MainWindow *ui;
     short int const arrdata[10][10]={
        {0 , 2 , 2 , 2 , 2 , 0 , 0 , 0 , 0 , 0},
        {0 , 2 , 1 , 1 , 2 , 2 , 2 , 2 , 2 , 0},
        {0 , 2 , 4 , 1 , 1 , 1 , 4 , 1 , 2 , 0},
        {0 , 2 , 1 , 3 , 2 , 3 , 1 , 1 , 2 , 0},
        {2 , 2 , 1 , 2 , 2 , 2 , 1 , 2 , 2 , 0},
        {2 , 1 , 4 , 3 , 2 , 3 , 1 , 2 , 0 , 0},
        {2 , 1 , 5 , 1 , 1 , 1 , 4 , 2 , 0 , 0},
        {2 , 2 , 2 , 2 , 2 , 1 , 1 , 2 , 0 , 0},
        {0 , 0 , 0 , 0 , 2 , 2 , 2 , 2 , 0 , 0},
        {0 , 0 , 0 , 0 , 2 , 2 , 2 , 2 , 0 , 0}};
    QPixmap* ground[100];
    QPixmap* wall[100];
    QPixmap* target[100];
    QPixmap* box[100];
    QPixmap* player[1];

    QLabel* Ground[100];
    QLabel* Wall[100];
    QLabel* Target[100];
    QLabel* Box[100];
    QLabel* Player[1];
    int px;
    int py;
    int steps=0;
    int idx_ground;
    int idx_wall;
    int idx_target;
    int idx_box;
    QLabel *mainplayer;
    QLabel *player_facing;
    QPixmap *walked;
    QLabel *Walked;
    QPixmap *front;
    QPixmap *back;
    QPixmap *left;
    QPixmap *right;
    void keyPressEvent( QKeyEvent *event );
};

#endif // MAINWINDOW_H
