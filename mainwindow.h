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

#include <QString>
#include <QDir>
#include <QVariant>
#include <QLineEdit>
#include <QTextStream>

#include <QTimer>

#include <fstream>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    explicit MainWindow(QWidget *parent = nullptr);
    void mainmenu();

    void input_map_name();
    void load_map();
    void mapGen(short int arrdata[10][10]);
    void init(short int arr[10][10]);

    void character_turn_back();
    void character_turn_front();
    void character_turn_left();
    void character_turn_right();

    void drawBackground(QPainter *painter, const QRectF &rect);

    bool checkWin();
    void checkDead();
    void clear_map();
    void close();

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
    void secret_menu();
    void hide_secret_menu();
    void update_timer();
    void load_saved_game();
    void hide_saved_game_menu();
    void hide_map();
    void show_map();
    void reset_preprocessor();
    void map_preprocessor();
    void quit();
    void hide_menu();
  protected:
    //void paintEvent(QPaintEvent *event);
  private:
    Ui::MainWindow *ui;
    QLabel *mainmenu_BG;
    QPixmap *mainmenu_image;
    bool first_run = 0;
    int steps=0;

    QLineEdit *input_level;
    int level_count = 1;
    QPushButton *Input_btn;
    QLabel *Input_Rule;
    QString loaded_level;
    short int level_data[10][10];

    bool inputing_code = 0;
    bool playing = 0;

    QPushButton *Start_btn;
    QPushButton *Exit_btn;

    QPushButton *Saved_game_btn;
    int saved_game_record[10][2] = {0};
    bool in_saved_game_menu = 0;
    void Saved_game_menu();
    QLabel *Saved_game_labels[11];
    QPushButton *back_to_menu;
    void save_data();

    QPushButton *Secret_btn;
    QLabel *Secret_menu_rule;
    QLabel *Secret_menu_input;
    void update_secret_input();
    QPushButton *cancel_input_code;
    void show_menu();
    QString code_input = "";
    QString code_answer = "UUDDLRLRba";
    bool check_code();
    void correct_input();
    void wrong_input();

    QTimer *timer;
    QLabel *real_time_timer;
    QLabel *real_time_step_counter;
    long long int back_end_timer = 0;
    void update_step_counter();

    void reset_menu();
    QPushButton *Reset_btn;
    QPushButton *Cancel_reset_btn;
    QLabel *Reset_Rule;
    QLabel *second_Reset_Rule;
    bool reset_mode = 0;

    void quit_menu();
    QPushButton *Quit_btn;
    QPushButton *Cancel_quit_btn;
    QLabel *Quit_Rule;
    QLabel *second_Quit_Rule;
    bool quit_mode = 0;
    void keyPressEvent( QKeyEvent *event );
};

#endif // MAINWINDOW_H
