#ifndef WATCH_H
#define WATCH_H
#include <QWidget>
#include <QTimer>
#include <QString>
#include <QLCDNumber>
#include <QtCore>
#include <QTime>
class Timer : public QTimer
{
    Q_OBJECT

public:
    Timer(QLCDNumber *display);
        ~Timer();

    void start();
    void pause();
    void resume();
    void displayUpdate();

private:

    QLCDNumber *lcd;
    QTimer *timer;
    QTime time;


};

#endif // WATCH_H
