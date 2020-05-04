#include "level_1.h"
#include "mainwindow.h"

level_1::level_1(QObject *parent) : QObject(parent) {

}

void level_1::mapGen() {
    MainWindow MW(nullptr , 1);
    MW.hide_menu();
    MW.idx_ground = 0;
    MW.idx_wall = 0;
    MW.idx_target = 0;
    MW.idx_box = 0;

    for(int x = 0; x<10; x++) {
        for(int y =0; y<10; y++) {

            switch(arrdata[x][y]) {
            case 1:
                MW.ground[MW.idx_ground] = new QPixmap(":/res/stone_ground.jpg");
                MW.Ground[MW.idx_ground] = MW.setLabel(MW.Ground[MW.idx_ground]);
                MW.Ground[MW.idx_ground] -> setPixmap(*(MW.ground[MW.idx_ground]));
                MW.Ground[MW.idx_ground] -> setScaledContents(true);
                MW.Ground[MW.idx_ground] -> setGeometry(50*x,50*y,50,50);
                MW.idx_ground++;
                break;
            case 2:
                MW.wall[MW.idx_wall] = new QPixmap(":/res/brick.jpg");
                MW.Wall[MW.idx_wall] = MW.setLabel(MW.Wall[MW.idx_wall]);
                MW.Wall[MW.idx_wall] -> setPixmap(*(MW.wall[MW.idx_wall]));
                MW.Wall[MW.idx_wall] -> setScaledContents(true);
                MW.Wall[MW.idx_wall] -> setGeometry(50*x,50*y,50,50);
                MW.idx_wall++;
                break;
            case 3:
                MW.target[MW.idx_target] = new QPixmap(":/res/target_ground.jpg");
                MW.Target[MW.idx_target] = MW.setLabel(MW.Target[MW.idx_target]);
                MW.Target[MW.idx_target] -> setPixmap(*(MW.target[MW.idx_target]));
                MW.Target[MW.idx_target] -> setScaledContents(true);
                MW.Target[MW.idx_target] -> setGeometry(50*x,50*y,50,50);
                MW.idx_target++;
                break;
            case 4:
                MW.ground[MW.idx_ground] = new QPixmap(":/res/stone_ground.jpg");
                MW.Ground[MW.idx_ground] = MW.setLabel(MW.Ground[MW.idx_ground]);
                MW.Ground[MW.idx_ground] -> setPixmap(*(MW.ground[MW.idx_ground]));
                MW.Ground[MW.idx_ground] -> setScaledContents(true);
                MW.Ground[MW.idx_ground] -> setGeometry(50*x,50*y,50,50);
                MW.idx_ground++;
                MW.box[MW.idx_box] = new QPixmap(":/res/wooden_box.png");
                MW.Box[MW.idx_box] = MW.setLabel(MW.Box[MW.idx_box]);
                MW.Box[MW.idx_box] -> setPixmap(*(MW.box[MW.idx_box]));
                MW.Box[MW.idx_box] -> setScaledContents(true);
                MW.Box[MW.idx_box] -> setGeometry(50*x,50*y,50,50);
                MW.idx_box++;
                break;
            case 5:
                MW.px=x;
                MW.py=y;
                MW.walked = new QPixmap(":/res/stone_ground.jpg");
                MW.Walked = MW.setLabel(MW.Walked);
                MW.Walked -> setPixmap(*MW.walked);
                MW.Walked -> setScaledContents(true);
                MW.Walked -> setGeometry(50*MW.px,50*MW.py,50,50);
                //Character Object
                MW.player_facing = MW.setLabel(MW.player_facing);
                MW.player_facing->setGeometry(50*MW.px,50*MW.py,50,50);
                MW.player_facing->setPixmap(*MW.front);
                MW.player_facing->setScaledContents(true);
                break;
            default:
                break;
            }
        }
    }

}
/*
 * air : 0
 * ground : 1
 * wall : 2
 * target : 3
 * box : 4
 * player : 5
 */
