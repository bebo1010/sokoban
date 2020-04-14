#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVarLengthArray>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Pixmap Pathes
    front = new QPixmap(":/res/main_character(front).png");
    back = new QPixmap(":/res/main_character(back).png");
    left = new QPixmap(":/res/main_character(left).png");
    right = new QPixmap(":/res/main_character(right).png");

    mapGen();
    walked = new QPixmap(":/res/stone_ground.jpg");
    Walked = new QLabel(this);
    Walked -> setPixmap(*walked);
    Walked -> setScaledContents(true);
    Walked -> setGeometry(50*px,50*py,50,50);
    //Character Object
    player_facing = new QLabel(this);
    player_facing->setGeometry(50*px,50*py,50,50);
    player_facing->setPixmap(*front);
    player_facing->setScaledContents(true);


}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    for(int i = 50 ; i < 500 ; i = i + 50){
        painter.drawLine(i , 0 , i , 500);
        painter.drawLine(0 , i , 500 , i);
    }
    return;
}
void MainWindow::keyPressEvent(QKeyEvent* key){

    if(key->key() == Qt::Key_Up){
        steps++;

        emit character_turn_back();
        if(player_facing->y()>=50)
            player_facing->move(player_facing->x(),player_facing->y()-50);
    }
    if(key->key() == Qt::Key_Down){
        steps++;

        emit character_turn_front();
        if(player_facing->y()<=MainWindow::size().height()-100)
            player_facing->move(player_facing->x(),player_facing->y()+50);
    }
    if(key->key() == Qt::Key_Left){
        steps++;
        emit character_turn_left();
        if(player_facing->x()>=50)
            player_facing->move(player_facing->x()-50,player_facing->y());
    }
    if(key->key() == Qt::Key_Right){
        steps++;
        emit character_turn_right();
        if(player_facing->x()<=MainWindow::size().width()-100)
        player_facing->move(player_facing->x()+50,player_facing->y());
    }
}
void MainWindow::mapGen(){

    int idx_ground = 0;
    int idx_wall = 0;
    int idx_target = 0;
    int idx_box = 0;

    for(int x = 0; x<10;x++){
        for(int y =0;y<10;y++){

            switch(arrdata[x][y]){
                case 1:
                    ground[idx_ground] = new QPixmap(":/res/stone_ground.jpg");
                    Ground[idx_ground] = new QLabel(this);
                    Ground[idx_ground] -> setPixmap(*ground[idx_ground]);
                    Ground[idx_ground] -> setScaledContents(true);
                    Ground[idx_ground] -> setGeometry(50*x,50*y,50,50);
                    break;
                case 2:
                    wall[idx_wall] = new QPixmap(":/res/brick.jpg");
                    Wall[idx_wall] = new QLabel(this);
                    Wall[idx_wall] -> setPixmap(*wall[idx_wall]);
                    Wall[idx_wall] -> setScaledContents(true);
                    Wall[idx_wall] -> setGeometry(50*x,50*y,50,50);
                    break;
                case 3:
                    target[idx_target] = new QPixmap(":/res/target_ground.jpg");
                    Target[idx_target] = new QLabel(this);
                    Target[idx_target] -> setPixmap(*target[idx_target]);
                    Target[idx_target] -> setScaledContents(true);
                    Target[idx_target] -> setGeometry(50*x,50*y,50,50);
                    break;
                case 4:
                    box[idx_box] = new QPixmap(":/res/wooden_box.png");
                    Box[idx_box] = new QLabel(this);
                    Box[idx_box] -> setPixmap(*box[idx_box]);
                    Box[idx_box] -> setScaledContents(true);
                    Box[idx_box] -> setGeometry(50*x,50*y,50,50);
                    break;
                case 5:
                    px=x;
                    py=y;
                    break;
                default:
                    break;
            }
        }
    }

}
void MainWindow::character_turn_back(){
    player_facing->setPixmap(*back);
}
void MainWindow::character_turn_front(){
    player_facing->setPixmap(*front);
}
void MainWindow::character_turn_left(){
    player_facing->setPixmap(*left);
}
void MainWindow::character_turn_right(){
    player_facing->setPixmap(*right);
}
MainWindow::~MainWindow()
{
    delete ui;
}




