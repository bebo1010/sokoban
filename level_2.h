#ifndef LEVEL_2_H
#define LEVEL_2_H

#include <QObject>

class level_2 : public QObject
{
    Q_OBJECT
public:
    explicit level_2(QObject *parent = nullptr);
    struct array {short int map[9][9];};
    array arr;
    static array const arrdata;
signals:

public slots:
};

#endif // LEVEL_2_H
