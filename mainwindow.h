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
namespace Ui {
    class MainWindow;
    class player;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
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
    QLabel *Wall;
    QPixmap *wall;
    QLabel *mainplayer;
    QLabel *player_facing;
    QPixmap *front;
    QPixmap *back;
    QPixmap *left;
    QPixmap *right;
    void keyPressEvent( QKeyEvent *event );
};

#endif // MAINWINDOW_H
