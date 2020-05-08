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
    front = new QPixmap(":/res/main_character(front).png");
    back = new QPixmap(":/res/main_character(back).png");
    left = new QPixmap(":/res/main_character(left).png");
    right = new QPixmap(":/res/main_character(right).png");

    timer = new QTimer(this);
    mainmenu();

}

void MainWindow::init(short int arr[10][10]){
    mapGen(arr);
    setFocusPolicy(Qt::StrongFocus);
    steps = 0;
    player_facing -> raise();
    playing = 1;

    timer->start(1000);
    real_time_timer = new QLabel(this);
    real_time_timer->setText("Time : 0");
    real_time_timer->setFont(QFont("Courier New", 14));
    real_time_timer->setGeometry(20,505,100,50);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_timer()));
    real_time_step_counter = new QLabel(this);
    real_time_step_counter->setText("Steps : 0");
    real_time_step_counter->setFont(QFont("Courier New", 14));
    real_time_step_counter->setGeometry(270,505,200,50);
    real_time_timer->show();
    real_time_step_counter->show();

}

void MainWindow::update_timer(){
    QString timer_text = "Time : ";
    back_end_timer = back_end_timer + 1;
    timer_text.append(QVariant(back_end_timer).toString());
    real_time_timer->setText(timer_text);
    timer->start(1000);
}

void MainWindow::update_step_counter(){
    steps++;
    QString steps_text = "Steps : ";
    steps_text.append(QVariant(steps).toString());
    real_time_step_counter->setText(steps_text);
}
void MainWindow::mainmenu() {

    mainmenu_image = new QPixmap(":/res/background.jpg");
    mainmenu_BG = new QLabel(this);
    mainmenu_BG->setPixmap(*mainmenu_image);
    mainmenu_BG->setGeometry(0,0,550,550);
    mainmenu_BG->setScaledContents(true);


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
    Input_Rule -> setGeometry(10 , 40 , 400 , 100);
    Input_Rule -> setFont(QFont("Courier New", 14));
    Input_Rule -> setText("Input any integer(0~99),\n which indicates the level\n to be loaded.\n Leave blank if you want to\n load the first level.");
    Input_Rule -> show();
    Input_btn = new QPushButton(this);
    Input_btn -> setText("Confirm");
    Input_btn -> setFont(QFont("Courier New", 14, QFont::Bold));
    Input_btn -> setGeometry(350 , 10 , 80 , 30);
    Input_btn -> show();
    connect(Input_btn , SIGNAL(clicked()) , this , SLOT(map_preprocessor()));
}

void MainWindow::hide_menu(){
    mainmenu_BG -> hide();
    Start_btn -> hide();
    Exit_btn -> hide();
    input_map_name();
}

void MainWindow::hide_map(){
    timer->stop();
    Walked -> hide();
    player_facing -> hide();
    for(int i = 0;i<idx_box;i++){
      Box[i] -> hide();
    }
    for(int i = 0;i<idx_ground;i++){
        Ground[i] -> hide();
    }
    for(int i = 0;i<idx_target;i++){
        Target[i] -> hide();
    }
    for(int i = 0;i<idx_wall;i++){
        Wall[i] -> hide();
    }
    reset_menu();
}

void MainWindow::show_map(){
    delete Reset_btn;
    delete Reset_Rule;
    delete Cancel_reset_btn;
    Walked -> show();
    player_facing -> show();
    for(int i = 0;i<idx_box;i++){
      Box[i] -> show();
    }
    for(int i = 0;i<idx_ground;i++){
        Ground[i] -> show();
    }
    for(int i = 0;i<idx_target;i++){
        Target[i] -> show();
    }
    for(int i = 0;i<idx_wall;i++){
        Wall[i] -> show();
    }
    playing = 1;
    timer->start();
}

void MainWindow::reset_menu(){
    playing = 0;
    Reset_btn = new QPushButton(this);
    Reset_btn -> setText("CONFIRM");
    Reset_btn -> setFont(QFont("Courier New", 14, QFont::Bold));
    Reset_btn -> setGeometry(100 , 350 , 100 , 30);
    Reset_btn -> show();
    Cancel_reset_btn = new QPushButton(this);
    Cancel_reset_btn -> setText("CANCEL");
    Cancel_reset_btn -> setFont(QFont("Courier New" , 14 , QFont::Bold));
    Cancel_reset_btn -> setGeometry(300 , 350 , 100 , 30);
    Cancel_reset_btn -> show();
    Reset_Rule = new QLabel(this);
    Reset_Rule -> setFont(QFont("Courier New", 14));
    Reset_Rule -> setText("If you wish to reset the level.\nClick the CONFIRM button below.");
    Reset_Rule -> setGeometry(50 , 200 , 350 , 80);
    Reset_Rule -> show();
    connect(Reset_btn , SIGNAL(clicked()) , this , SLOT(reset_preprocessor()));
    connect(Cancel_reset_btn , SIGNAL(clicked()) , this , SLOT(show_map()));
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
        if(!checkWin()){
            if(player_facing->y()>=50&&movable) {
                player_facing->move(player_facing->x(),player_facing->y()-50);
                update_step_counter();
            }
        }
    }
    //###########DOWN############
    if(key->key() == Qt::Key_Down) {
        bool movable = true;
        bool box_movable = true;
        emit character_turn_front();
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
        if(!checkWin()){
            if(player_facing->y()<=MainWindow::size().height()-100&&movable) {
                player_facing->move(player_facing->x(),player_facing->y()+50);
                update_step_counter();
            }
        }
    }
    //##################LEFT#############
    if(key->key() == Qt::Key_Left) {
        bool box_movable = true;
        bool movable = true;
        emit character_turn_left();
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
        if(!checkWin()){
            if(player_facing->x()>=50&&movable) {
                player_facing->move(player_facing->x()-50,player_facing->y());
                update_step_counter();
            }
        }
    }
    //#################RIGHT##############
    if(key->key() == Qt::Key_Right) {
        bool box_movable = true;
        bool movable = true;
        emit character_turn_right();
        for(int i = 0; i < idx_wall; i++) {
            if(player_facing->x()+50==Wall[i]->x()&&player_facing->y()==Wall[i]->y()) {
                movable = false; //to prevent character from walking into the wall
            }
        }

        for(int i = 0; i < idx_box; i++) {
            if(player_facing->x()+50==Box[i]->x()&&player_facing->y()==Box[i]->y()) {

                for(int j = 0; j < idx_box; j++) {
                    if(Box[i]->x()+50==Box[j]->x()&&Box[i]->y()==Box[j]->y()) {
                        box_movable=false;
                        movable=false;
                    }

                }

                for(int j = 0; j < idx_wall; j++) {
                    if(Box[i]->x()+50==Wall[j]->x()&&Box[i]->y()==Wall[j]->y()) {
                        box_movable=false;
                        movable=false;
                    }
                }


            }
            if(player_facing->x()+50==Box[i]->x()&&player_facing->y()==Box[i]->y()&&box_movable) {
                Box[i]->raise();
                Box[i]->move(Box[i]->x()+50,Box[i]->y());
            }
        }
        if(!checkWin()){
            if(player_facing->x()<=MainWindow::size().width()-100&&movable) {
                player_facing->move(player_facing->x()+50,player_facing->y());
                update_step_counter();
            }
        }
    }
    if(key->key() == Qt::Key_X){
        if(playing == 1){
                emit hide_map();
        }
    }
}

void MainWindow::clear_map(){
    delete walked;
    delete Walked;
    delete player_facing;
    delete real_time_timer;
    delete real_time_step_counter;
    for (int i = 0 ; i < 10 ; i++ ) {
        for (int j = 0 ; j < 10 ; j++ ) {
            level_data[i][j] = 0;
        }
    }
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
bool MainWindow::checkWin() {
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
        return true;
   }
    return false;
}

void MainWindow::mapGen(short int arrdata[10][10]) {
    idx_ground = 0;
    idx_wall = 0;
    idx_target = 0;
    idx_box = 0;

    for(int x = 0; x<10; x++) {
        for(int y =0; y<10; y++) {

            switch(arrdata[x][y]) {
            case 1: //ground
                ground[idx_ground] = new QPixmap(":/res/stone_ground.jpg");
                Ground[idx_ground] = new QLabel(this);
                Ground[idx_ground] -> setPixmap(*(ground[idx_ground]));
                Ground[idx_ground] -> setScaledContents(true);
                Ground[idx_ground] -> setGeometry(50*x,50*y,50,50);
                Ground[idx_ground] -> raise();
                Ground[idx_ground] -> showNormal();
                idx_ground++;
                break;
            case 2: //wall
                wall[idx_wall] = new QPixmap(":/res/brick.jpg");
                Wall[idx_wall] = new QLabel(this);
                Wall[idx_wall] -> setPixmap(*(wall[idx_wall]));
                Wall[idx_wall] -> setScaledContents(true);
                Wall[idx_wall] -> setGeometry(50*x,50*y,50,50);
                Wall[idx_wall] -> raise();
                Wall[idx_wall] -> showNormal();
                idx_wall++;
                break;
            case 3: //target
                target[idx_target] = new QPixmap(":/res/target_ground.jpg");
                Target[idx_target] = new QLabel(this);
                Target[idx_target] -> setPixmap(*(target[idx_target]));
                Target[idx_target] -> setScaledContents(true);
                Target[idx_target] -> setGeometry(50*x,50*y,50,50);
                Target[idx_target] -> raise();
                Target[idx_target] -> showNormal();
                idx_target++;
                break;
            case 4: //box
                ground[idx_ground] = new QPixmap(":/res/stone_ground.jpg");
                Ground[idx_ground] = new QLabel(this);
                Ground[idx_ground] -> setPixmap(*(ground[idx_ground]));
                Ground[idx_ground] -> setScaledContents(true);
                Ground[idx_ground] -> setGeometry(50*x,50*y,50,50);
                Ground[idx_ground] -> raise();
                Ground[idx_ground] -> showNormal();
                idx_ground++;

                box[idx_box] = new QPixmap(":/res/wooden_box.png");
                Box[idx_box] = new QLabel(this);
                Box[idx_box] -> setPixmap(*(box[idx_box]));
                Box[idx_box] -> setScaledContents(true);
                Box[idx_box] -> setGeometry(50*x,50*y,50,50);
                Box[idx_box] -> raise();
                Box[idx_box] -> showNormal();
                idx_box++;
                break;
            case 5: //player
                walked = new QPixmap(":/res/stone_ground.jpg");
                Walked = new QLabel(this);
                Walked -> setPixmap(*walked);
                Walked -> setScaledContents(true);
                Walked -> setGeometry(50*x,50*y,50,50);
                Walked -> show();
                //character
                player_facing = new QLabel(this);
                player_facing -> setPixmap(*front);
                player_facing -> setScaledContents(true);
                player_facing -> setGeometry(50*x,50*y,50,50);
                player_facing -> show();
                break;
            case 6: //player + target
                walked = new QPixmap(":/res/stone_ground.jpg");
                Walked = new QLabel(this);
                Walked -> setPixmap(*walked);
                Walked -> setScaledContents(true);
                Walked -> setGeometry(50*x,50*y,50,50);
                Walked -> show();
                //character
                player_facing = new QLabel(this);
                player_facing -> setPixmap(*front);
                player_facing -> setScaledContents(true);
                player_facing -> setGeometry(50*x,50*y,50,50);
                player_facing -> show();
                target[idx_target] = new QPixmap(":/res/target_ground.jpg");
                Target[idx_target] = new QLabel(this);
                Target[idx_target] -> setPixmap(*(target[idx_target]));
                Target[idx_target] -> setScaledContents(true);
                Target[idx_target] -> setGeometry(50*x,50*y,50,50);
                Target[idx_target] -> showNormal();
                idx_target++;
                break;
            case 7: //box + target
                box[idx_box] = new QPixmap(":/res/wooden_box.png");
                Box[idx_box] = new QLabel(this);
                Box[idx_box] -> setPixmap(*(box[idx_box]));
                Box[idx_box] -> setScaledContents(true);
                Box[idx_box] -> setGeometry(50*x,50*y,50,50);
                Box[idx_box] -> showNormal();
                idx_box++;

                target[idx_target] = new QPixmap(":/res/target_ground.jpg");
                Target[idx_target] = new QLabel(this);
                Target[idx_target] -> setPixmap(*(target[idx_target]));
                Target[idx_target] -> setScaledContents(true);
                Target[idx_target] -> setGeometry(50*x,50*y,50,50);
                Target[idx_target] -> showNormal();
                idx_target++;
                Box[idx_box-1] -> raise();
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


void MainWindow::reset_preprocessor(){
    delete Reset_btn;
    delete Reset_Rule;
    delete Cancel_reset_btn;
    clear_map();
    map_preprocessor();
}

void MainWindow::map_preprocessor() {
    loaded_level = QVariant(":").toString() + QDir::separator() + QVariant("mapdata").toString() + QDir::separator() + QVariant("level_").toString();
    if(first_run == 0){
        delete Input_Rule;
        input_level -> hide();
        delete Input_btn;
    }
    if(input_level->text().isEmpty() || first_run != 0){
        loaded_level = loaded_level + QVariant(level_count).toString() + QVariant(".txt").toString();
    }
    else{
        loaded_level = loaded_level + input_level->text() + QVariant(".txt").toString();
        level_count = input_level->text().toInt();

    }
    first_run = 1;
    load_map();
}

void MainWindow::load_map(){

    QFile level_loader(loaded_level);
    if(!level_loader.open(QIODevice::ReadOnly)){
        QMessageBox::information(this, tr("Unable to open file") , level_loader.errorString());
    }
    QTextStream in(&level_loader);
    in.setIntegerBase(10);
    for (int i = 0 ; i < 10 ; i++ ) {
        for (int j = 0 ; j < 10 ; j++ ) {
            in >> level_data[i][j];
            //qDebug() << level_data[i][j];
        }
    }
    init(level_data);
}
MainWindow::~MainWindow() {
    delete ui;
}
