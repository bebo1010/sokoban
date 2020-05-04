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
#include <QMessageBox>

#include <QPushButton>
#include <QApplication>
#include <QFont>

#include "level_1.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    explicit MainWindow(QWidget *parent = nullptr , bool startup_flag = 0);
    void mainmenu();
    void hide_menu();

    void character_turn_back();
    void character_turn_front();
    void character_turn_left();
    void character_turn_right();

    void drawBackground(QPainter *painter, const QRectF &rect);

    void checkWin();
    void checkDead();

    level_1 lvl1;
    ~MainWindow();

    int idx_ground;
    int idx_wall;
    int idx_target;
    int idx_box;

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

    QLabel *mainplayer;
    QLabel *player_facing;
    QPixmap *walked;
    QLabel *Walked;
    QPixmap *front;
    QPixmap *back;
    QPixmap *left;
    QPixmap *right;

    QLabel * setLabel(QLabel *label);
  public slots:
    void quit();
  protected:
    //void paintEvent(QPaintEvent *event);
  private:
    Ui::MainWindow *ui;
    QLabel *mainmenu_BG;
    QPixmap *mainmenu_image;
    int steps=0;

    QPushButton *Start_btn;
    QPushButton *Exit_btn;


    void keyPressEvent( QKeyEvent *event );
};

#endif // MAINWINDOW_H
