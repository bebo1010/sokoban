#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVarLengthArray>
#include <QDebug>
#include<iostream>
#include<QLayoutItem>
#include<QFlags>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    front = new QPixmap(":/res/main_character(front).png");
    back = new QPixmap(":/res/main_character(back).png");
    left = new QPixmap(":/res/main_character(left).png");
    right = new QPixmap(":/res/main_character(right).png");
    mainmenu();

}

void MainWindow::init(short int arr[10][10]) {
    mapGen(arr);
    setFocusPolicy(Qt::StrongFocus);
    steps = 0;
    back_end_timer = 0;
    player_facing -> raise();
    playing = 1;

    timer = new QTimer(this);
    timer->start(1000);
    real_time_timer = new QLabel(this);
    real_time_timer->setText("Time : 0");
    real_time_timer->setFont(QFont("Courier New", 14));
    real_time_timer->setGeometry(20,495,150,50);
    real_time_timer->setFont(QFont("Courier New", 14, QFont::Bold));
    real_time_timer->setStyleSheet(   "color: rgba(153, 44, 20, 1);"
                                "background-color: rgba(26, 101, 147, 0.5);"
                                "border-style: outset;"
                                "border-color: green;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "min-width: 8em;"
                                "border-color: beige;"
                                "padding: 6px;");
    connect(timer, SIGNAL(timeout()), this, SLOT(update_timer()));
    real_time_step_counter = new QLabel(this);
    real_time_step_counter->setText("Steps : 0");
    real_time_step_counter->setFont(QFont("Courier New", 14 , QFont::Bold));
    real_time_step_counter->setGeometry(320,495,150,50);
    real_time_step_counter->setStyleSheet(   "color: rgba(153, 44, 20, 1);"
                                "background-color: rgba(26, 101, 147, 0.5);"
                                "border-style: outset;"
                                "border-color: green;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "min-width: 8em;"
                                "border-color: beige;"
                                "padding: 6px;");
    real_time_timer->show();
    real_time_step_counter->show();

}

void MainWindow::update_timer() {
    QString timer_text = "Time : ";
    back_end_timer = back_end_timer + 1;
    timer_text.append(QVariant(back_end_timer).toString());
    real_time_timer->setText(timer_text);
    timer->start(1000);
}

void MainWindow::update_step_counter() {
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


    Start_btn = new QPushButton("START", this);
    Start_btn->raise();
    Start_btn->setFont(QFont("Courier New", 14, QFont::Bold));
    Start_btn->setGeometry(10,30,100,150);
    Start_btn->setStyleSheet(   "color: rgba(27, 108, 208, 1);"
                                "background-color: rgba(113, 247, 80, 0.9);"
                                "border-style: outset;"
                                "border-color: green;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: beige;"
                                "padding: 6px;");
    connect(Start_btn, SIGNAL(clicked()), this, SLOT(hide_menu()));

    Exit_btn = new QPushButton("QUIT", this);
    Exit_btn->raise();
    Exit_btn->setFont(QFont("Courier New", 14, QFont::Bold));
    Exit_btn->setGeometry(10,200,100,150);
    Exit_btn->setStyleSheet(    "color: rgba(221, 49, 49, 1);"
                                "background-color: rgba(25, 188, 225, 0.9);"
                                "border-style: outset;"
                                "border-color: green;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: beige;"
                                "padding: 6px;");
    connect(Exit_btn, SIGNAL(clicked()), this, SLOT(quit()));
    Exit_btn->show();

    Secret_btn = new QPushButton(this);
    Secret_btn->raise();
    Secret_btn->setGeometry(403,445,20,20);
    Secret_btn->setFlat(true);
    Secret_btn->setStyleSheet("background-color: rgba(251, 255, 15, 1);");
    connect(Secret_btn,SIGNAL(clicked()),this,SLOT(secret_menu()));

    Saved_game_btn = new QPushButton("SHOW\nRECORD" , this);
    Saved_game_btn->raise();
    Saved_game_btn->setFont(QFont("Courier New" , 14 , QFont::Bold));
    Saved_game_btn->setGeometry(10,370,100,100);
    Saved_game_btn->setStyleSheet(    "color: rgba(221, 49, 49, 1);"
                                "background-color: rgba(25, 188, 225, 0.9);"
                                "border-style: outset;"
                                "border-color: green;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: beige;"
                                "padding: 6px;");
    connect(Saved_game_btn,SIGNAL(clicked()),this,SLOT(load_saved_game()));
}

void MainWindow::secret_menu() {
    inputing_code = 1;
    setFocusPolicy(Qt::StrongFocus);
    Secret_menu_rule = new QLabel(this);
    Secret_menu_rule -> setGeometry(10, 100, 500, 200);
    Secret_menu_rule -> setFont(QFont("Courier New", 14));
    Secret_menu_rule -> setText("Input keys from keyboard.\nThe keys will be checked when 10 keys\n are pressed. Allowed keys are: \n english characters(uppercase or lowercase\n don't matter) , and arrow keys.\n");
    Secret_menu_rule -> show();
    Secret_menu_input = new QLabel(this);
    Secret_menu_input -> setGeometry(170, 50, 160, 30);
    Secret_menu_input -> setStyleSheet("border: 1px solid black");
    Secret_menu_input -> setTextFormat(Qt::PlainText);
    Secret_menu_input -> setText("");
    Secret_menu_input -> setFont(QFont("Courier New", 18));
    Secret_menu_input -> show();
    cancel_input_code = new QPushButton("CANCEL", this);
    cancel_input_code -> show();
    cancel_input_code->setStyleSheet(   "color: rgba(27, 108, 208, 1);"
                                "background-color: rgba(113, 247, 80, 0.9);"
                                "border-style: outset;"
                                "border-color: green;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: beige;"
                                "padding: 6px;");
    cancel_input_code -> setGeometry(200, 400, 100, 50);
    connect(cancel_input_code, SIGNAL(clicked()),this,SLOT(hide_secret_menu()));
    hide_menu();
}

void MainWindow::hide_secret_menu() {
    delete Secret_menu_rule;
    delete Secret_menu_input;
    delete cancel_input_code;
    inputing_code = 0;
    show_menu();
}
void MainWindow::update_secret_input() {
    QString secret_text = Secret_menu_input->text();
    secret_text.append(QVariant("*").toString());
    Secret_menu_input -> setText(secret_text);
}

bool MainWindow::check_code() {
    if(code_input == code_answer)
        return true;
    else
        return false;
}

void MainWindow::correct_input() {
    Secret_menu_input->setText("");
    code_input = "";
    QMessageBox right_input_msgbox;
    right_input_msgbox.setStyleSheet("QLabel{min-width: 250px;}");
    right_input_msgbox.setText("Achievement Unlocked!\nYou have unlocked\nNOTHING.\n");
    right_input_msgbox.exec();
    right_input_msgbox.close();
    quit();
}

void MainWindow::wrong_input() {
    Secret_menu_input->setText("");
    code_input = "";
    QMessageBox wrong_input_msgbox;
    wrong_input_msgbox.setStyleSheet("QLabel{min-width: 250px;}");
    wrong_input_msgbox.setText("Wrong code input.\nPlease try again.\n");
    wrong_input_msgbox.exec();
    wrong_input_msgbox.close();
}

void MainWindow::load_saved_game(){
    in_saved_game_menu = 1;
    hide_menu();

    QFile save_loader("../2020-pd2-sokoban/SavedGame/SavedGame.txt");
    if(!save_loader.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, tr("Unable to open file"), save_loader.errorString());
    }
    QTextStream in(&save_loader);
    in.setIntegerBase(10);
    /*int i = 0;
    while((!save_loader.atEnd()) && i < 10){
        for(int j = 0 ; j < 2 ; j++)
            in >> saved_game_record[i][j];
        qDebug() << saved_game_record[i][0] << " " << saved_game_record[i][1];
        i++;
    }*/
    QString data;
    int *read_ptr = &saved_game_record[0][0];
    int read_count = 0;
    do{
        data = in.readLine();
        bool read_test;
        *(read_ptr + read_count) = data.toInt(&read_test);
        if(read_test){
            read_count++;
        }
    }while(!data.isNull());
    save_loader.close();
    Saved_game_menu();
}

void MainWindow::Saved_game_menu(){
    Saved_game_labels[0] = new QLabel(this);
    Saved_game_labels[0] -> setText("\t\tTime used\tSteps used");
    Saved_game_labels[0] -> setFont(QFont("Courier New" , 14 , QFont::Bold));
    Saved_game_labels[0] -> setGeometry(20 , 20 , 500 , 50);
    Saved_game_labels[0] -> show();
    for(int i = 1 ; i < 11 ; i++){
        Saved_game_labels[i] = new QLabel(this);
        QString temp_save_str = "Level " + QVariant(i).toString() + "  \t" + QVariant(saved_game_record[i-1][0]).toString() + "\t\t" + QVariant(saved_game_record[i-1][1]).toString();
        Saved_game_labels[i] -> setText(temp_save_str);
        Saved_game_labels[i] -> setFont(QFont("Courier New" , 14 , QFont::Bold));
        Saved_game_labels[i] -> setGeometry(20 , 20+40*i , 500 , 40);
        Saved_game_labels[i] -> show();
    }
    back_to_menu = new QPushButton(this);
    back_to_menu -> setText("BACK\nTO MENU");
    back_to_menu -> setFont(QFont("Courier New" , 14 , QFont::Bold));
    back_to_menu -> setGeometry(200 , 470 , 100 , 70);
    back_to_menu -> show();
    back_to_menu->setStyleSheet(   "color: rgba(27, 108, 208, 1);"
                                "background-color: rgba(113, 247, 80, 0.9);"
                                "border-style: outset;"
                                "border-color: green;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: beige;"
                                "padding: 6px;");
    connect(back_to_menu , SIGNAL(clicked()) , this , SLOT(hide_saved_game_menu()));
}

void MainWindow::hide_saved_game_menu(){
    for (int i = 0 ; i < 11 ; i++)
        delete Saved_game_labels[i];
    delete back_to_menu;
    in_saved_game_menu = 0;
    show_menu();
}
void MainWindow::input_map_name() {
    input_level = new QLineEdit(this);
    input_level -> setGeometry(10, 10, 300, 30);
    input_level -> setFont(QFont("Courier New", 14 , QFont::Bold));
    input_level -> setInputMask("00");
    input_level -> show();
    input_level->setStyleSheet(  "border-style: outset;"
                                 "border-width: 2px;"
                                 "border-radius: 10px;"
                                 "border-color: beige;"
                                 "min-width: 8em;"
                                 "padding: 6px;");
    Input_Rule = new QLabel(this);
    Input_Rule -> setGeometry(10, 50, 400, 120);
    Input_Rule -> setFont(QFont("Courier New", 14 , QFont::Bold));
    Input_Rule -> setText("Input any positive integer(1~99),\nwhich indicates the level\nto be loaded.\nLeave blank if you want to\nload the first level.");
    Input_Rule -> show();
    Input_btn = new QPushButton(this);
    Input_btn -> setText("Confirm");
    Input_btn -> setFont(QFont("Courier New", 14, QFont::Bold));
    Input_btn -> setGeometry(350, 10, 80, 30);
    Input_btn -> show();
    Input_btn->setStyleSheet(   "color: rgba(27, 108, 208, 1);"
                                "background-color: rgba(113, 247, 80, 0.9);"
                                "border-style: outset;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: beige;"
                                "min-width: 8em;"
                                "padding: 6px;");
    connect(Input_btn, SIGNAL(clicked()), this, SLOT(map_preprocessor()));
}

void MainWindow::hide_menu() {
    mainmenu_BG -> hide();
    Start_btn -> hide();
    Exit_btn -> hide();
    Saved_game_btn -> hide();
    if(inputing_code == 0 && in_saved_game_menu == 0)
        input_map_name();
}

void MainWindow::show_menu() {
    mainmenu_BG->show();
    Start_btn->show();
    Exit_btn->show();
    Saved_game_btn -> show();
}
void MainWindow::hide_map() {
    timer->stop();
    Walked -> hide();
    player_facing -> hide();
    for(int i = 0; i<idx_box; i++) {
        Box[i] -> hide();
    }
    for(int i = 0; i<idx_ground; i++) {
        Ground[i] -> hide();
    }
    for(int i = 0; i<idx_target; i++) {
        Target[i] -> hide();
    }
    for(int i = 0; i<idx_wall; i++) {
        Wall[i] -> hide();
    }
    if(reset_mode == 1)
        reset_menu();
    if(quit_mode == 1)
        quit_menu();
}

void MainWindow::show_map() {
    if(reset_mode == 1) {
        reset_mode = 0;
        delete Reset_btn;
        delete Reset_Rule;
        delete second_Reset_Rule;
        delete Cancel_reset_btn;
    }
    if(quit_mode == 1) {
        quit_mode = 0;
        delete Quit_btn;
        delete Quit_Rule;
        delete second_Quit_Rule;
        delete Cancel_quit_btn;
    }
    Walked -> show();
    player_facing -> show();
    for(int i = 0; i<idx_box; i++) {
        Box[i] -> show();
    }
    for(int i = 0; i<idx_ground; i++) {
        Ground[i] -> show();
    }
    for(int i = 0; i<idx_target; i++) {
        Target[i] -> show();
    }
    for(int i = 0; i<idx_wall; i++) {
        Wall[i] -> show();
    }
    playing = 1;
    timer->start();
}

void MainWindow::reset_menu() {
    playing = 0;
    Reset_btn = new QPushButton(this);
    Reset_btn -> setText("CONFIRM");
    Reset_btn -> setFont(QFont("Courier New", 14, QFont::Bold));
    Reset_btn -> setGeometry(100, 250, 150, 100);
    Reset_btn -> show();
    Reset_btn->setStyleSheet(    "color: rgba(221, 49, 49, 1);"
                                "background-color: rgba(25, 188, 225, 0.85);"
                                "border-style: outset;"
                                "border-color: green;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: beige;"
                                "padding: 6px;");
    Cancel_reset_btn = new QPushButton(this);
    Cancel_reset_btn -> setText("CANCEL");
    Cancel_reset_btn -> setFont(QFont("Courier New", 14, QFont::Bold));
    Cancel_reset_btn -> setGeometry(300, 250, 150, 100);
    Cancel_reset_btn -> show();
    Cancel_reset_btn->setStyleSheet(   "color: rgba(27, 108, 208, 1);"
                                "background-color: rgba(113, 247, 80, 0.9);"
                                "border-style: outset;"
                                "border-color: green;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: beige;"
                                "padding: 6px;");
    Reset_Rule = new QLabel(this);
    Reset_Rule -> setFont(QFont("Courier New", 18 , QFont::Bold));
    Reset_Rule -> setText("If you wish to <span style=\"background-color:yellow;\">RESET</span> the level.");
    Reset_Rule -> setGeometry(60, 100, 500, 35);
    Reset_Rule -> show();
    second_Reset_Rule = new QLabel(this);
    second_Reset_Rule -> setFont(QFont("Courier New" , 18 , QFont::Bold));
    second_Reset_Rule -> setText("Click the CONFIRM button below.");
    second_Reset_Rule -> setGeometry(60, 135, 500, 35);
    second_Reset_Rule -> show();
    connect(Reset_btn, SIGNAL(clicked()), this, SLOT(reset_preprocessor()));
    connect(Cancel_reset_btn, SIGNAL(clicked()), this, SLOT(show_map()));
}

void MainWindow::quit_menu() {
    playing = 0;
    Quit_btn = new QPushButton(this);
    Quit_btn -> setText("CONFIRM");
    Quit_btn -> setFont(QFont("Courier New", 14, QFont::Bold));
    Quit_btn -> setGeometry(100, 250, 150, 100);
    Quit_btn -> show();
    Quit_btn->setStyleSheet(    "color: rgba(221, 49, 49, 1);"
                                "background-color: rgba(25, 188, 225, 0.85);"
                                "border-style: outset;"
                                "border-color: green;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: beige;"
                                "padding: 6px;");
    Cancel_quit_btn = new QPushButton(this);
    Cancel_quit_btn -> setText("CANCEL");
    Cancel_quit_btn -> setFont(QFont("Courier New", 14, QFont::Bold));
    Cancel_quit_btn -> setGeometry(300, 250, 150, 100);
    Cancel_quit_btn -> show();
    Cancel_quit_btn->setStyleSheet(   "color: rgba(27, 108, 208, 1);"
                                "background-color: rgba(113, 247, 80, 0.9);"
                                "border-style: outset;"
                                "border-color: green;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: beige;"
                                "padding: 6px;");
    Quit_Rule = new QLabel(this);
    Quit_Rule -> setFont(QFont("Courier New", 18 , QFont::Bold));
    Quit_Rule -> setText("If you wish to <span style=\"background-color:yellow;\">QUIT</span> the game.");
    Quit_Rule -> setGeometry(60, 100, 500, 35);
    Quit_Rule -> show();
    second_Quit_Rule = new QLabel(this);
    second_Quit_Rule -> setFont(QFont("Courier New" , 18 , QFont::Bold));
    second_Quit_Rule -> setText("Click the CONFIRM button below.");
    second_Quit_Rule -> setGeometry(60, 135, 500, 35);
    second_Quit_Rule -> show();
    connect(Quit_btn, SIGNAL(clicked()), this, SLOT(quit()));
    connect(Cancel_quit_btn, SIGNAL(clicked()), this, SLOT(show_map()));
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
    if(inputing_code == 1) {
        if(key->key() == Qt::Key_Up)
            code_input.append("U");
        else if(key->key() == Qt::Key_Down)
            code_input.append("D");
        else if(key->key() == Qt::Key_Left)
            code_input.append("L");
        else if(key->key() == Qt::Key_Right)
            code_input.append("R");
        else code_input.append(key->text().toLower());
        update_secret_input();
        //qDebug() << code_input;
        if(code_input.size() == 10) {
            if(check_code())
                correct_input();
            else
                wrong_input();
        }
        return;
    }
    if(playing == 1) {
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
            if(!checkWin()) {
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
            if(!checkWin()) {
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
            if(!checkWin()) {
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
            if(!checkWin()) {
                if(player_facing->x()<=MainWindow::size().width()-100&&movable) {
                    player_facing->move(player_facing->x()+50,player_facing->y());
                    update_step_counter();
                }
            }
        }
    }
    if(key->key() == Qt::Key_R) {
        if(playing == 1) {
            reset_mode = 1;
            emit hide_map();
        }
    }
    if(key->key() == Qt::Key_Q) {
        if(playing == 1) {
            quit_mode = 1;
            emit hide_map();
        }
    }
}

void MainWindow::clear_map() {
    delete walked;
    delete Walked;
    delete player_facing;
    delete timer;
    delete real_time_timer;
    delete real_time_step_counter;
    for (int i = 0 ; i < 10 ; i++ ) {
        for (int j = 0 ; j < 10 ; j++ ) {
            level_data[i][j] = 0;
        }
    }
    for(int i = 0; i<idx_box; i++) {
        delete Box[i];
    }
    for(int i = 0; i<idx_ground; i++) {
        delete Ground[i];
    }
    for(int i = 0; i<idx_target; i++) {
        delete Target[i];
    }
    for(int i = 0; i<idx_wall; i++) {
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
        timer->stop();
        QMessageBox msg;
        QString steps_str = QString::fromStdString(std::to_string(steps));
        QString timer_str = QString::fromStdString(std::to_string(back_end_timer));
        msg.setStyleSheet("QLabel{min-width: 200px;}");
        msg.setText("you win!!!!!!\nUsed Time: "+timer_str+"\nUsed Steps: "+steps_str+"\n");
        msg.exec();
        msg.close();
        save_data();
        clear_map();
        level_count++;
        map_preprocessor();
        return true;
    }
    return false;
}

void MainWindow::save_data(){
    QFile save_writer("../2020-pd2-sokoban/SavedGame/SavedGame.txt");
    if(!save_writer.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::information(this, tr("Unable to open file"), save_writer.errorString());
    }
    QTextStream out(&save_writer);
    out << back_end_timer << endl << steps << endl;
    save_writer.close();
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


void MainWindow::reset_preprocessor() {
    delete Reset_btn;
    delete Reset_Rule;
    delete second_Reset_Rule;
    delete Cancel_reset_btn;
    reset_mode = 0;
    clear_map();
    map_preprocessor();
}

void MainWindow::map_preprocessor() {
    loaded_level = QVariant(":").toString() + QDir::separator() + QVariant("mapdata").toString() + QDir::separator() + QVariant("level_").toString();
    if(first_run == 0) {
        delete Input_Rule;
        input_level->hide();
        delete Input_btn;
    }
    if(input_level->text().isEmpty() || first_run != 0) {
        loaded_level = loaded_level + QVariant(level_count).toString() + QVariant(".txt").toString();
    } else {
        loaded_level = loaded_level + input_level->text() + QVariant(".txt").toString();
        level_count = input_level->text().toInt();

    }
    first_run = 1;
    load_map();
}

void MainWindow::load_map() {
    QFile level_loader(loaded_level);
    if(!level_loader.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, tr("Unable to open file"), level_loader.errorString());
    }
    QTextStream in(&level_loader);
    in.setIntegerBase(10);
    for (int i = 0 ; i < 10 ; i++ ) {
        for (int j = 0 ; j < 10 ; j++ ) {
            in >> level_data[i][j];
            //qDebug() << level_data[i][j];
        }
    }
    level_loader.close();
    init(level_data);
}
MainWindow::~MainWindow() {
    delete ui;
}
