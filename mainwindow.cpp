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
    mainmenu();

}

void MainWindow::init(short int (&arr)[10][10]){
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
    //character
    player_facing = new QLabel(this);
    player_facing -> setGeometry(50*px,50*py,50,50);
    player_facing -> setPixmap(*front);
    player_facing -> setScaledContents(true);
}

void MainWindow::mainmenu() {

    mainmenu_image = new QPixmap(":/res/background.jpg");
    mainmenu_BG = new QLabel(this);
    mainmenu_BG->setPixmap(*mainmenu_image);
    mainmenu_BG->setGeometry(0,0,500,500);
    mainmenu_BG->setScaledContents(true);
    first_run = 1;

    Start_btn = new QPushButton("Start", this);
    Start_btn->raise();
    Start_btn->setFont(QFont("Courier New", 14, QFont::Bold));
    Start_btn->setGeometry(10,30,100,150);
    connect(Start_btn, SIGNAL(clicked()), this, SLOT(hide_menu()));

    Exit_btn = new QPushButton("Quit", this);
    Exit_btn->raise();
    Exit_btn->setFont(QFont("Courier New", 14, QFont::Bold));
    Exit_btn->setGeometry(10,200,100,150);
    connect(Exit_btn, SIGNAL(clicked()), this, SLOT(quit()));
    Exit_btn->show();
}

void MainWindow::input_map_name() {
    input_level = new QLineEdit(this);
    input_level -> setGeometry(10 , 10 , 300 , 30);
    input_level -> setInputMask("00");
    input_level -> show();
    Input_Rule = new QLabel(this);
    Input_Rule -> setGeometry(10 , 50 , 300 , 60);
    Input_Rule -> setText("Input any two digit number, which indicates the level to load\n Leave blank if you want to load first level.");
    Input_Rule -> show();
    Input_btn = new QPushButton(this);
    Input_btn -> setText("Confirm");
    Input_btn -> setGeometry(350 , 10 , 80 , 30);
    Input_btn -> show();
    connect(Input_btn , SIGNAL(clicked()) , this , SLOT(map_preprocessor()));
}

void MainWindow::hide_menu(){
    mainmenu_BG -> hide();
    //mainmenu_BG -> lower();
    Start_btn -> hide();
    //Start_btn -> lower();
    Exit_btn -> hide();
    //Exit_btn -> lower();
    input_map_name();
}
void MainWindow::quit() {
    exit(0);
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
                msg.close();
                clear_map();
                level_count++;
                map_preprocessor();
                px=0;py=0;
                Walked->setGeometry(50*px,50*py,50,50);
                Walked -> raise();
                Walked -> showNormal();
                player_facing->setGeometry(50*px,50*py,50,50);
                player_facing->showNormal();
                player_facing->raise();
    }
}

void MainWindow::mapGen(short int (&arrdata)[10][10]) {
    idx_ground = 0;
    idx_wall = 0;
    idx_target = 0;
    idx_box = 0;

    for(int x = 0; x<10; x++) {
        for(int y =0; y<10; y++) {

            switch(arrdata[x][y]) {
            case 1: //ground
                ground[idx_ground] = new QPixmap(":/res/stone_ground.jpg");
                Ground[idx_ground] = new QLabel(Ground[idx_ground]);
                Ground[idx_ground] -> setPixmap(*(ground[idx_ground]));
                Ground[idx_ground] -> setScaledContents(true);
                Ground[idx_ground] -> setGeometry(50*x,50*y,50,50);
                Ground[idx_ground] -> raise();
                Ground[idx_ground] -> showNormal();
                idx_ground++;
                break;
            case 2: //wall
                wall[idx_wall] = new QPixmap(":/res/brick.jpg");
                Wall[idx_wall] = new QLabel(Wall[idx_wall]);
                Wall[idx_wall] -> setPixmap(*(wall[idx_wall]));
                Wall[idx_wall] -> setScaledContents(true);
                Wall[idx_wall] -> setGeometry(50*x,50*y,50,50);
                Wall[idx_wall] -> raise();
                Wall[idx_wall] -> showNormal();
                idx_wall++;
                break;
            case 3: //target
                target[idx_target] = new QPixmap(":/res/target_ground.jpg");
                Target[idx_target] = new QLabel(Target[idx_target]);
                Target[idx_target] -> setPixmap(*(target[idx_target]));
                Target[idx_target] -> setScaledContents(true);
                Target[idx_target] -> setGeometry(50*x,50*y,50,50);
                Target[idx_target] -> raise();
                Target[idx_target] -> showNormal();
                idx_target++;
                break;
            case 4: //box
                ground[idx_ground] = new QPixmap(":/res/stone_ground.jpg");
                Ground[idx_ground] = new QLabel(Ground[idx_ground]);
                Ground[idx_ground] -> setPixmap(*(ground[idx_ground]));
                Ground[idx_ground] -> setScaledContents(true);
                Ground[idx_ground] -> setGeometry(50*x,50*y,50,50);
                Ground[idx_ground] -> raise();
                Ground[idx_ground] -> showNormal();
                idx_ground++;

                box[idx_box] = new QPixmap(":/res/wooden_box.png");
                Box[idx_box] = new QLabel(Box[idx_box]);
                Box[idx_box] -> setPixmap(*(box[idx_box]));
                Box[idx_box] -> setScaledContents(true);
                Box[idx_box] -> setGeometry(50*x,50*y,50,50);
                Box[idx_box] -> raise();
                Box[idx_box] -> showNormal();
                idx_box++;
                break;
            case 5: //player
                px=x;
                py=y;
                break;
            case 6: //player + target
                px=x;
                py=y;

                target[idx_target] = new QPixmap(":/res/target_ground.jpg");
                Target[idx_target] = new QLabel(Target[idx_target]);
                Target[idx_target] -> setPixmap(*(target[idx_target]));
                Target[idx_target] -> setScaledContents(true);
                Target[idx_target] -> setGeometry(50*x,50*y,50,50);
                Target[idx_target] -> raise();
                Target[idx_target] -> showNormal();
                idx_target++;
                break;
            case 7: //box + target
                box[idx_box] = new QPixmap(":/res/wooden_box.png");
                Box[idx_box] = new QLabel(Box[idx_box]);
                Box[idx_box] -> setPixmap(*(box[idx_box]));
                Box[idx_box] -> setScaledContents(true);
                Box[idx_box] -> setGeometry(50*x,50*y,50,50);
                Box[idx_box] -> raise();
                Box[idx_box] -> showNormal();
                idx_box++;

                target[idx_target] = new QPixmap(":/res/target_ground.jpg");
                Target[idx_target] = new QLabel(Target[idx_target]);
                Target[idx_target] -> setPixmap(*(target[idx_target]));
                Target[idx_target] -> setScaledContents(true);
                Target[idx_target] -> setGeometry(50*x,50*y,50,50);
                Target[idx_target] -> raise();
                Target[idx_target] -> showNormal();
                idx_target++;
                break;
            default:
                break;
            }
        }
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

void MainWindow::map_preprocessor() {
    Input_Rule -> hide();
    input_level -> hide();
    Input_btn -> hide();
    if(input_level->text().isEmpty() || first_run != 0){
        loaded_level = loaded_level + static_cast<QString>(level_count) + ".txt";
    }
    else{
        loaded_level = loaded_level + static_cast<QString>(input_level->text()) + ".txt";
    }
    load_map();
}

void MainWindow::load_map(){

    QFile level_loader(loaded_level);
    if(!level_loader.open(QIODevice::ReadOnly)){
        QMessageBox::information(this, tr("Unable to open file"),level_loader.errorString());
    }
    QDataStream IN(&level_loader);
    IN.setVersion(QDataStream::Qt_4_8);
    for (int i = 0 ; i < 10 ; i++ ) {
        for (int j = 0 ; j < 10 ; j++ ) {
            IN >> level_data[i][j];
        }
    }
    init(level_data);
}
/*
                        QMessageBox a(this);
                        //QString box_x= QString::fromStdString(std::to_string(Box[a]->x()));
                        QString wall_x= QString::fromStdString(std::to_string(Wall[j]->x()));
                        a.setText(wall_x);
                        a.exec();

*/
