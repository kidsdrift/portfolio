#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"sudoku.h"
#include"timer.h"
class QPushButton;
class QStackedWidget;
class QFrame;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //void paintEvent(QPaintEvent * );


private:

    Ui::MainWindow *ui;
    QPushButton*** plate;
    QPushButton** key;
    Sudoku* gamecore;
    QFrame* widget2;
    Timer* timeronWidget;
    int undoStack[10][4];
    bool clickable[9][9];
    //QStackedWidget* startPage;
    //QStackedWidget* gamePage;
    //QStackedWidget* endPage;
    void highLight(int, int);
    void lowLight(int,int);
    //void recording();

    void showWrong(int,int);
    //void checkRight(int,int);
    void highlighing();
    void addNewGame();
    void initGame();
    void highlightnum(int);

private slots:
    void tablebuttonClicked();
    void keyboardclicked();
    void on_delallbutton_2_clicked();
    void on_answerbutton_2_clicked();
    void on_pulsebutton_2_clicked();
    void on_resume_clicked();
    void on_undobutton_2_clicked();
    void on_redobutton_2_clicked();
    void on_restart_clicked();
    void on_level2_clicked();
    void on_level1_clicked();
    void on_level3_clicked();
    void on_level4_clicked();
    void on_level5_clicked();
    void on_level6_clicked();
    void on_level7_clicked();
    void on_level8_clicked();
    void on_level9_clicked();
    void on_level10_clicked();
};

#endif // MAINWINDOW_H
