#ifndef LEVEL_1_H
#define LEVEL_1_H

#include <QObject>
using namespace std;
class level_1 : public QObject {
    Q_OBJECT
  public:

    explicit level_1(QObject *parent = nullptr);
    short int const arrdata[10][10]= {
        {0, 2, 2, 2, 2, 0, 0, 0, 0, 0},
        {0, 2, 1, 1, 2, 2, 2, 2, 2, 0},
        {0, 2, 4, 1, 1, 1, 4, 1, 2, 0},
        {0, 2, 1, 3, 2, 3, 1, 1, 2, 0},
        {2, 2, 1, 2, 2, 2, 1, 2, 2, 0},
        {2, 1, 4, 3, 2, 3, 1, 2, 0, 0},
        {2, 1, 5, 1, 1, 1, 4, 2, 0, 0},
        {2, 2, 2, 2, 2, 1, 1, 2, 0, 0},
        {0, 0, 0, 0, 2, 2, 2, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

  signals:

  public slots:
    void mapGen();
  private:

};

#endif // LEVEL_1_H
