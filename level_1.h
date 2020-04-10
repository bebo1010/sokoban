#ifndef LEVEL_1_H
#define LEVEL_1_H

#include <QObject>
using namespace std;
class level_1 : public QObject
{
    Q_OBJECT
public:
    explicit level_1(QObject *parent = nullptr);
    struct array {short int map[9][9];};
    array arr;
    static array const arrdata;
signals:

public slots:

private:

};

#endif // LEVEL_1_H
