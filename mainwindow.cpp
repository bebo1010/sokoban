#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVarLengthArray>
#include <QDebug>
#include<iostream>
#include<QLayoutItem>
#include<QFlags>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init(arrdata);

}
void MainWindow::init(short int const arr[10][10]){
    //Pixmap Pathes
    front = new QPixmap(":/res/main_character(front).png");
    back = new QPixmap(":/res/main_character(back).png");
    left = new QPixmap(":/res/main_character(left).png");
    right = new QPixmap(":/res/main_character(right).png");

    mapGen(arr);
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
    //#############UP##################
    if(key->key() == Qt::Key_Up){
        steps++;
        bool movable = true;
        bool box_movable = true;
        emit character_turn_back();
        for(int a = 0;a < idx_wall;a++){
            if(player_facing->y()-50==Wall[a]->y()&&player_facing->x()==Wall[a]->x()){
                movable = false;
            }
        }
        for(int a = 0;a < idx_box;a++){
            if(player_facing->y()-50==Box[a]->y()&&player_facing->x()==Box[a]->x()){
                for(int c = 0;c < idx_box;c++){
                    if(Box[a]->x()==Box[c]->x()&&Box[a]->y()-50==Box[c]->y()){
                        box_movable=false;
                        movable=false;
                    }
                }
                for(int b = 0;b < idx_wall;b++){
                    if(Box[a]->x()==Wall[b]->x()&&Box[a]->y()-50==Wall[b]->y()){
                        movable = false;
                        box_movable = false;
                    }
                }
            }
            if(player_facing->y()-50==Box[a]->y()&&player_facing->x()==Box[a]->x()&&box_movable){
                Box[a]->raise();
                Box[a]->move(Box[a]->x(),Box[a]->y()-50);
            }
        }
        checkWin();
        if(player_facing->y()>=50&&movable)
            player_facing->move(player_facing->x(),player_facing->y()-50);
    }
    //###########DOWN############
    if(key->key() == Qt::Key_Down){
        steps++;
        bool movable = true;
        bool box_movable = true;
        for(int a = 0;a < idx_wall;a++){
            if(player_facing->y()+50==Wall[a]->y()&&player_facing->x()==Wall[a]->x()){
                movable = false;
            }
        }
        for(int a = 0;a < idx_box;a++){
            if(player_facing->y()+50==Box[a]->y()&&player_facing->x()==Box[a]->x()){
                for(int c = 0;c < idx_box;c++){
                    if(Box[a]->x()==Box[c]->x()&&Box[a]->y()+50==Box[c]->y()){
                        box_movable=false;
                        movable=false;
                    }
                }
                for(int b = 0;b < idx_wall;b++){
                    if(Box[a]->x()==Wall[b]->x()&&Box[a]->y()+50==Wall[b]->y()){
                        movable = false;
                        box_movable = false;
                    }
                }
            }
            if(player_facing->y()+50==Box[a]->y()&&player_facing->x()==Box[a]->x()&&box_movable){

                Box[a]->raise();
                Box[a]->move(Box[a]->x(),Box[a]->y()+50);
            }
        }
        checkWin();
        emit character_turn_front();
        if(player_facing->y()<=MainWindow::size().height()-100&&movable)
            player_facing->move(player_facing->x(),player_facing->y()+50);
    }
    //##################LEFT#############
    if(key->key() == Qt::Key_Left){
        steps++;
        bool box_movable = true;
        bool movable = true;
        for(int a = 0;a < idx_wall;a++){
            if(player_facing->x()-50==Wall[a]->x()&&player_facing->y()==Wall[a]->y()){
                movable = false;
            }
        }
        for(int a = 0;a < idx_box;a++){
            if(player_facing->x()-50==Box[a]->x()&&player_facing->y()==Box[a]->y()){
                for(int c = 0;c < idx_box;c++){
                    if(Box[a]->x()-50==Box[c]->x()&&Box[a]->y()==Box[c]->y()){
                        box_movable=false;
                        movable=false;
                    }
                }
                for(int b = 0;b < idx_wall;b++){
                    if(Box[a]->x()-50==Wall[b]->x()&&Box[a]->y()==Wall[b]->y()){
                        box_movable =false;
                        movable = false;
                    }
                }
            }
            if(player_facing->x()-50==Box[a]->x()&&player_facing->y()==Box[a]->y()&&box_movable){
                Box[a]->raise();
                Box[a]->move(Box[a]->x()-50,Box[a]->y());
            }
        }
        checkWin();
        emit character_turn_left();
        if(player_facing->x()>=50&&movable)
            player_facing->move(player_facing->x()-50,player_facing->y());
    }
    //#################RIGHT##############
    if(key->key() == Qt::Key_Right){
        steps++;
        bool box_movable = true;
        bool movable = true;
        for(int a = 0;a < idx_wall;a++){
            if(player_facing->x()+50==Wall[a]->x()&&player_facing->y()==Wall[a]->y()){
                movable = false;
                //QMessageBox msg;
                //QString box1_x = QString::fromStdString(std::to_string(player_facing->x()));
                //QString box2_x = QString::fromStdString(std::to_string(Wall[a]->x()));
                //msg.setText(box1_x+" "+box2_x);
                //msg.exec();
            }
        }

        for(int a = 0;a < idx_box;a++){
            if(player_facing->x()+50==Box[a]->x()&&player_facing->y()==Box[a]->y()){

                for(int c = 0;c < idx_box;c++){
                    if(Box[a]->x()+50==Box[c]->x()&&Box[a]->y()==Box[c]->y()){
                        box_movable=false;
                        movable=false;
                        //QMessageBox msg;
                        //QString box1_x = QString::fromStdString(std::to_string(Box[a]->x()));
                        //QString box2_x = QString::fromStdString(std::to_string(Box[c]->x()));
                        //msg.setText(box1_x+" "+box2_x);
                        //msg.exec();
                    }

                }

                for(int b = 0;b < idx_wall;b++){
                    if(Box[a]->x()+50==Wall[b]->x()&&Box[a]->y()==Wall[b]->y()){
                        box_movable=false;
                        movable=false;
                        //QMessageBox msg;
                        //QString box1_x = QString::fromStdString(std::to_string(Box[a]->x()));
                        //QString wall_x = QString::fromStdString(std::to_string(Wall[b]->x()));
                        //msg.setText(box1_x+" "+wall_x);
                        //msg.exec();

                    }
                }


            }
            if(player_facing->x()+50==Box[a]->x()&&player_facing->y()==Box[a]->y()&&box_movable){
                Box[a]->raise();
                Box[a]->move(Box[a]->x()+50,Box[a]->y());
            }
        }
        checkWin();
        emit character_turn_right();
        if(player_facing->x()<=MainWindow::size().width()-100&&movable){
            player_facing->move(player_facing->x()+50,player_facing->y());
        }

    }
}
void MainWindow::clear_map(){

    for(int i = 0;i<idx_box;i++){
        delete Box[i];
    }
    for(int i = 0;i<idx_ground;i++){
        delete Ground[i];
    }
    for(int i = 0;i<idx_target;i++){
        delete Target[i];
    }
    for(int i = 0;i<idx_wall;i++){
        delete Wall[i];
    }

}
void MainWindow::checkWin(){

    for(int i = 0; i<idx_target;i++){
        for(int j = 0; j<idx_box;j++){
            if(Target[i]->x()==Box[j]->x()&&Target[i]->y()==Box[j]->y()){
                win++;
            }
        }
    }
    if(win>=idx_target){
        QMessageBox msg;
        QString steps_str = QString::fromStdString(std::to_string(steps));
        msg.setText("you win!!!!!!\nUsed Steps: "+steps_str+"\n");
        msg.exec();
        msg.close();
        clear_map();

        mapGen(arrdata2);

        Walked -> raise();
        Walked -> showNormal();
        player_facing->showNormal();
        player_facing->raise();
    }
}

void MainWindow::checkDead(){

}
void MainWindow::mapGen(short int const lvl[10][10]){

    idx_ground = 0;
    idx_wall = 0;
    idx_target = 0;
    idx_box = 0;

    for(int x = 0; x<10;x++){
        for(int y =0;y<10;y++){

            switch(lvl[x][y]){
            case 1:

                ground[idx_ground] = new QPixmap(":/res/stone_ground.jpg");
                Ground[idx_ground] = new QLabel(this);
                Ground[idx_ground] -> setPixmap(*ground[idx_ground]);
                Ground[idx_ground] -> setScaledContents(true);
                Ground[idx_ground] -> setGeometry(50*x,50*y,50,50);
                Ground[idx_ground]->raise();
                Ground[idx_ground]->showNormal();
                idx_ground++;
                break;
            case 2:

                wall[idx_wall] = new QPixmap(":/res/brick.jpg");
                Wall[idx_wall] = new QLabel(this);
                Wall[idx_wall] -> setPixmap(*wall[idx_wall]);
                Wall[idx_wall] -> setScaledContents(true);
                Wall[idx_wall] -> setGeometry(50*x,50*y,50,50);
                Wall[idx_wall] -> showNormal();
                idx_wall++;
                break;
            case 3:
                target[idx_target] = new QPixmap(":/res/target_ground.jpg");
                Target[idx_target] = new QLabel(this);
                Target[idx_target] -> setPixmap(*target[idx_target]);
                Target[idx_target] -> setScaledContents(true);
                Target[idx_target] -> setGeometry(50*x,50*y,50,50);
                Target[idx_target]->showNormal();
                idx_target++;
                break;
            case 4:
                ground[idx_ground] = new QPixmap(":/res/stone_ground.jpg");
                Ground[idx_ground] = new QLabel(this);
                Ground[idx_ground] -> setPixmap(*ground[idx_ground]);
                Ground[idx_ground] -> setScaledContents(true);
                Ground[idx_ground] -> setGeometry(50*x,50*y,50,50);
                Ground[idx_ground]->showNormal();
                idx_ground++;

                box[idx_box] = new QPixmap(":/res/wooden_box.png");
                Box[idx_box] = new QLabel(this);
                Box[idx_box] -> setPixmap(*box[idx_box]);
                Box[idx_box] -> setScaledContents(true);
                Box[idx_box] -> setGeometry(50*x,50*y,50,50);
                Box[idx_box]->showNormal();
                idx_box++;
                break;
            case 5:
                px=x;
                py=y;
                break;
            case 6:
                px=x;
                py=y;
                target[idx_target] = new QPixmap(":/res/target_ground.jpg");
                Target[idx_target] = new QLabel(this);
                Target[idx_target] -> setPixmap(*target[idx_target]);
                Target[idx_target] -> setScaledContents(true);
                Target[idx_target] -> setGeometry(50*x,50*y,50,50);
                Target[idx_target]->showNormal();
                idx_target++;
                break;
            case 7:
                win++;
                target[idx_target] = new QPixmap(":/res/target_ground.jpg");
                Target[idx_target] = new QLabel(this);
                Target[idx_target] -> setPixmap(*target[idx_target]);
                Target[idx_target] -> setScaledContents(true);
                Target[idx_target] -> setGeometry(50*x,50*y,50,50);
                Target[idx_target]->showNormal();
                idx_target++;

                box[idx_box] = new QPixmap(":/res/wooden_box.png");
                Box[idx_box] = new QLabel(this);
                Box[idx_box] -> setPixmap(*box[idx_box]);
                Box[idx_box] -> setScaledContents(true);
                Box[idx_box] -> setGeometry(50*x,50*y,50,50);
                Box[idx_box]->showNormal();
                idx_box++;
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
/*
                        QMessageBox a(this);
                        //QString box_x= QString::fromStdString(std::to_string(Box[a]->x()));
                        QString wall_x= QString::fromStdString(std::to_string(Wall[b]->x()));
                        a.setText(wall_x);
                        a.exec();

*/



