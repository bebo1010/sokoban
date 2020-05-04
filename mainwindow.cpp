#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVarLengthArray>
#include <QDebug>
#include<iostream>

MainWindow::MainWindow(QWidget *parent ,  bool startup_flag) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle("Sokoban");
    //Pixmap Pathes
    front = new QPixmap(":/res/main_character(front).png");
    back = new QPixmap(":/res/main_character(back).png");
    left = new QPixmap(":/res/main_character(left).png");
    right = new QPixmap(":/res/main_character(right).png");
    if(startup_flag == 0)
        mainmenu();

    /*walked = new QPixmap(":/res/stone_ground.jpg");
    Walked = setLabel(Walked);
    Walked -> setPixmap(*walked);
    Walked -> setScaledContents(true);
    Walked -> setGeometry(50*px,50*py,50,50);
    //Character Object
    player_facing = setLabel(player_facing);
    player_facing->setGeometry(50*px,50*py,50,50);
    player_facing->setPixmap(*front);
    player_facing->setScaledContents(true);*/


}

void MainWindow::mainmenu() {

    mainmenu_image = new QPixmap(":/res/background.jpg");
    mainmenu_BG = new QLabel(this);
    mainmenu_BG->setPixmap(*mainmenu_image);
    mainmenu_BG->setGeometry(0,0,500,500);
    mainmenu_BG->setScaledContents(true);

    Start_btn = new QPushButton("Start", this);
    Start_btn->raise();
    Start_btn->setFont(QFont("Courier New", 14, QFont::Bold));
    Start_btn->setGeometry(10,30,100,150);
    connect(Start_btn, SIGNAL(clicked()), &lvl1, SLOT(mapGen()));

    Exit_btn = new QPushButton("Quit", this);
    Exit_btn->raise();
    Exit_btn->setFont(QFont("Courier New", 14, QFont::Bold));
    Exit_btn->setGeometry(10,200,100,150);
    connect(Exit_btn, SIGNAL(clicked()), this, SLOT(quit()));
    Exit_btn->show();
}

void MainWindow::hide_menu(){
    mainmenu_BG -> hide();
    Start_btn -> hide();
    Exit_btn -> hide();
}
void MainWindow::quit() {
    exit(0);
}
QLabel * MainWindow::setLabel(QLabel *label) {
    label = new QLabel(this);
    return label;
}

/*void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    for(int i = 50 ; i < 500 ; i = i + 50){
        painter.drawLine(i , 0 , i , 500);
        painter.drawLine(0 , i , 500 , i);
    }
    return;
}*/
void MainWindow::keyPressEvent(QKeyEvent* key) {
    //#############UP##################
    if(key->key() == Qt::Key_Up) {
        steps++;
        bool movable = true;
        bool box_movable = true;
        emit character_turn_back();
        for(int i = 0; i < idx_wall; i++) {
            if(player_facing->y()-50==Wall[i]->y()&&player_facing->x()==Wall[i]->x()) {
                movable = false; //to prevent character from walking into the wall
            }
        }
        for(int i = 0; i < idx_box; i++) {
            if(player_facing->y()-50==Box[i]->y()&&player_facing->x()==Box[i]->x()) {
                for(int j = 0; j < idx_box; j++) {
                    if(Box[i]->x()==Box[j]->x()&&Box[i]->y()-50==Box[j]->y()) {
                        box_movable=false;
                        movable=false;
                    }
                }
                for(int j = 0; j < idx_wall; j++) {
                    if(Box[i]->x()==Wall[j]->x()&&Box[i]->y()-50==Wall[j]->y()) {
                        movable = false;
                        box_movable = false;
                    }
                }
            }
            if(player_facing->y()-50==Box[i]->y()&&player_facing->x()==Box[i]->x()&&box_movable) {
                Box[i]->raise();
                Box[i]->move(Box[i]->x(),Box[i]->y()-50);
            }
        }
        checkWin();
        if(player_facing->y()>=50&&movable)
            player_facing->move(player_facing->x(),player_facing->y()-50);
    }
    //###########DOWN############
    if(key->key() == Qt::Key_Down) {
        steps++;
        bool movable = true;
        bool box_movable = true;
        for(int i = 0; i < idx_wall; i++) {
            if(player_facing->y()+50==Wall[i]->y()&&player_facing->x()==Wall[i]->x()) {
                movable = false; //to prevent character from walking into the wall
            }
        }
        for(int i = 0; i < idx_box; i++) {
            if(player_facing->y()+50==Box[i]->y()&&player_facing->x()==Box[i]->x()) {
                for(int j = 0; j < idx_box; j++) {
                    if(Box[i]->x()==Box[j]->x()&&Box[i]->y()+50==Box[j]->y()) {
                        box_movable=false;
                        movable=false;
                    }
                }
                for(int j = 0; j < idx_wall; j++) {
                    if(Box[i]->x()==Wall[j]->x()&&Box[i]->y()+50==Wall[j]->y()) {
                        movable = false;
                        box_movable = false;
                    }
                }
            }
            if(player_facing->y()+50==Box[i]->y()&&player_facing->x()==Box[i]->x()&&box_movable) {

                Box[i]->raise();
                Box[i]->move(Box[i]->x(),Box[i]->y()+50);
            }
        }
        checkWin();
        emit character_turn_front();
        if(player_facing->y()<=MainWindow::size().height()-100&&movable)
            player_facing->move(player_facing->x(),player_facing->y()+50);
    }
    //##################LEFT#############
    if(key->key() == Qt::Key_Left) {
        steps++;
        bool box_movable = true;
        bool movable = true;
        for(int i = 0; i < idx_wall; i++) {
            if(player_facing->x()-50==Wall[i]->x()&&player_facing->y()==Wall[i]->y()) {
                movable = false; //to prevent character from walking into the wall
            }
        }
        for(int i = 0; i < idx_box; i++) {
            if(player_facing->x()-50==Box[i]->x()&&player_facing->y()==Box[i]->y()) {
                for(int j = 0; j < idx_box; j++) {
                    if(Box[i]->x()-50==Box[j]->x()&&Box[i]->y()==Box[j]->y()) {
                        box_movable=false;
                        movable=false;
                    }
                }
                for(int j = 0; j < idx_wall; j++) {
                    if(Box[i]->x()-50==Wall[j]->x()&&Box[i]->y()==Wall[j]->y()) {
                        box_movable =false;
                        movable = false;
                    }
                }
            }
            if(player_facing->x()-50==Box[i]->x()&&player_facing->y()==Box[i]->y()&&box_movable) {
                Box[i]->raise();
                Box[i]->move(Box[i]->x()-50,Box[i]->y());
            }
        }
        checkWin();
        emit character_turn_left();
        if(player_facing->x()>=50&&movable)
            player_facing->move(player_facing->x()-50,player_facing->y());
    }
    //#################RIGHT##############
    if(key->key() == Qt::Key_Right) {
        steps++;
        bool box_movable = true;
        bool movable = true;
        for(int i = 0; i < idx_wall; i++) {
            if(player_facing->x()+50==Wall[i]->x()&&player_facing->y()==Wall[i]->y()) {
                movable = false; //to prevent character from walking into the wall
                //QMessageBox msg;
                //QString box1_x = QString::fromStdString(std::to_string(player_facing->x()));
                //QString box2_x = QString::fromStdString(std::to_string(Wall[i]->x()));
                //msg.setText(box1_x+" "+box2_x);
                //msg.exec();
            }
        }

        for(int i = 0; i < idx_box; i++) {
            if(player_facing->x()+50==Box[i]->x()&&player_facing->y()==Box[i]->y()) {

                for(int j = 0; j < idx_box; j++) {
                    if(Box[i]->x()+50==Box[j]->x()&&Box[i]->y()==Box[j]->y()) {
                        box_movable=false;
                        movable=false;
                        //QMessageBox msg;
                        //QString box1_x = QString::fromStdString(std::to_string(Box[i]->x()));
                        //QString box2_x = QString::fromStdString(std::to_string(Box[j]->x()));
                        //msg.setText(box1_x+" "+box2_x);
                        //msg.exec();
                    }

                }

                for(int j = 0; j < idx_wall; j++) {
                    if(Box[i]->x()+50==Wall[j]->x()&&Box[i]->y()==Wall[j]->y()) {
                        box_movable=false;
                        movable=false;
                        //QMessageBox msg;
                        //QString box1_x = QString::fromStdString(std::to_string(Box[i]->x()));
                        //QString wall_x = QString::fromStdString(std::to_string(Wall[j]->x()));
                        //msg.setText(box1_x+" "+wall_x);
                        //msg.exec();

                    }
                }


            }
            if(player_facing->x()+50==Box[i]->x()&&player_facing->y()==Box[i]->y()&&box_movable) {
                Box[i]->raise();
                Box[i]->move(Box[i]->x()+50,Box[i]->y());
            }
        }
        checkWin();
        emit character_turn_right();
        if(player_facing->x()<=MainWindow::size().width()-100&&movable) {
            player_facing->move(player_facing->x()+50,player_facing->y());
        }

    }
}

void MainWindow::checkWin() {
    int win=0;
    for(int i = 0; i<idx_target; i++) {
        for(int j = 0; j<idx_box; j++) {
            if(Target[i]->x()==Box[j]->x()&&Target[i]->y()==Box[j]->y()) {
                win++;
            }
        }
    }
    if(win>=idx_target) {
        QMessageBox msg;
        QString steps_str = QString::fromStdString(std::to_string(steps));
        msg.setText("you win!!!!!!\nUsed Steps: "+steps_str+"\n");
        msg.exec();
    }
}

void MainWindow::checkDead() {

}

void MainWindow::character_turn_back() {
    player_facing->setPixmap(*back);
}
void MainWindow::character_turn_front() {
    player_facing->setPixmap(*front);
}
void MainWindow::character_turn_left() {
    player_facing->setPixmap(*left);
}
void MainWindow::character_turn_right() {
    player_facing->setPixmap(*right);
}
MainWindow::~MainWindow() {
    delete ui;
}
/*
                        QMessageBox a(this);
                        //QString box_x= QString::fromStdString(std::to_string(Box[a]->x()));
                        QString wall_x= QString::fromStdString(std::to_string(Wall[j]->x()));
                        a.setText(wall_x);
                        a.exec();

*/
