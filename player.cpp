#include "player.h"
#include "mainwindow.h"

player::player(int x1, int y1, int x2, int y2)
{
    player_facing = new QLabel;
    player_facing->setGeometry(x1,y1,x2,y2);
    front = new QPixmap(":/res/main_character(front).png");
    back = new QPixmap(":/res/main_character(back).png");
    left = new QPixmap(":/res/main_character(left).png");
    right = new QPixmap(":/res/main_character(right).png");

    player_facing->setPixmap(*front);
    player_facing->setScaledContents(true);
    player_facing->show();
}


void player::character_turn_back(){
    player_facing->setPixmap(*back);
}
void player::character_turn_front(){
    player_facing->setPixmap(*front);
}
void player::character_turn_left(){
    player_facing->setPixmap(*left);
}
void player::character_turn_right(){
    player_facing->setPixmap(*right);
}

