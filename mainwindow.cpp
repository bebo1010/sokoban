#include "../headers/mainwindow.h"
#include "../headers/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    for(int i = 51 ; i < 507 ; i = i + 51){
        painter.drawLine(i , 0 , i , 507);
        painter.drawLine(0 , i , 507 , i);
    }
    return;
}
