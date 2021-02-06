#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QPainter>
#include <QPalette>
#include <QObject>
#include <QFrame>
#include<QPoint>
#include<QDesktopWidget>
#include<QString>
#include<QDebug>

static int x_t=0,y_t=0;
static int stepcount=0;
static QFont ft2("Times New Roman",13);
static QPalette pal1,pal2,pal3,pal4;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timeronWidget = new Timer(ui->lcdNumber);
    gamecore = new Sudoku;

    //gamecore->initblank();
    for(int i=0;i<10;i++)
        for(int j=0;j<4;j++)
            undoStack[i][j]=0;


    pal1.setColor(QPalette::ButtonText,QColor("#ff4500"));
    pal2.setColor(QPalette::ButtonText,QColor("#8fbc8f"));
    pal3.setColor(QPalette::ButtonText,QColor("#EE9572"));
    pal4.setColor(QPalette::ButtonText,QColor("#778899"));

   //little keyboard
    QGridLayout* gl2 = new QGridLayout;
    key=new QPushButton*[12];
    QString a;
    for(int i=0;i<9;++i)
    {
        key[i]=new QPushButton(a.setNum(i+1));
        //key[i]->setFont(ft3);
        gl2->addWidget(key[i],i/3,i%3);
        key[i]->setMinimumSize(40,40);
        connect(key[i],SIGNAL(clicked(bool)),this,SLOT(keyboardclicked()));
    }
    key[9]=new QPushButton(tr("C"));
    key[10]= new QPushButton (tr("M"));
    key[11]=new QPushButton(tr("H"));
    key[9]->setPalette(pal1);
    key[10]->setPalette(pal2);
    key[11]->setPalette(pal3);
    gl2->addWidget(key[9],3,1);
    gl2->addWidget(key[10],3,2);
    gl2->addWidget(key[11],3,0);
    key[9]->setMinimumSize(40,40);
    key[10]->setMinimumSize(40,40);
    key[11]->setMinimumSize(40,40);
    //key[9]->setFont(ft3);
    for( int i=0 ; i<3; ++i)
    {
        gl2->setRowStretch(i,1);
        gl2->setColumnStretch(i,1);
    }
     gl2->setRowStretch(3,1);
    connect(key[9],SIGNAL(clicked(bool)),this,SLOT(keyboardclicked()));
    connect(key[10],SIGNAL(clicked(bool)),this,SLOT(keyboardclicked()));
    connect(key[11],SIGNAL(clicked(bool)),this,SLOT(keyboardclicked()));

//sudoku struct
    plate = new QPushButton**[9];
    for(int i=0 ;i<9 ;++i)
    {
        plate[i]=new QPushButton*[9];
        for( int j=0;j<9;++j)
        {
            plate[i][j]=new QPushButton;
            plate[i][j]->setMinimumSize(80,80);
            plate[i][j]->setMaximumSize(80,80);

            ui->gridLayout_2->addWidget(plate[i][j],i,j);
            plate[i][j]->setAccessibleName(QString::number(i*10+j));
            plate[i][j]->setFont(ft2);

            connect(plate[i][j],SIGNAL(clicked()),this,SLOT(tablebuttonClicked()));
            //connect(plate[i][j],SIGNAL(windowIconTextChanged(QString),this,)
            //plate[i][j]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        }
    }

//
    widget2 = new QFrame(this);
    gl2->setSpacing(0);
    widget2->setMinimumSize(120,160);
    widget2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    widget2->setLayout(gl2);
    widget2->close();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::highLight(int rnum,int cnum)
{
    for(int i=0;i<9;i++)
    {
        plate[rnum][i]->setStyleSheet("background-color:#E5E5E5;");
        plate[i][cnum]->setStyleSheet("background-color:#E5E5E5;");

    }
    if(rnum<3&&cnum<3)
    {
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#E5E5E5;");
            }
    }
    if(rnum<3&&cnum<6&&cnum>2)
    {
        for(int i=0;i<3;i++)
            for(int j=3;j<6;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#E5E5E5;");
            }
    }
    if(rnum<3&&cnum>5)
    {
        for(int i=0;i<3;i++)
            for(int j=6;j<9;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#E5E5E5;");

            }
    }
    if(rnum>2&&rnum<6&&cnum<3)
    {
        for(int i=3;i<6;i++)
            for(int j=0;j<3;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#E5E5E5;");

            }
    }
    if(rnum>2&&rnum<6&&cnum>5)
    {
        for(int i=3;i<6;i++)
            for(int j=6;j<9;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#E5E5E5;");

            }
    }
    if(rnum>2&&rnum<6&&cnum<6&&cnum>2)
    {
        for(int i=3;i<6;i++)
            for(int j=3;j<6;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#E5E5E5;");

            }
    }
    if(rnum>5&&cnum<6&&cnum>2)
    {
        for(int i=6;i<9;i++)
            for(int j=3;j<6;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#E5E5E5;");
            }
    }
    if(rnum>5&&cnum<3)
    {
        for(int i=6;i<9;i++)
            for(int j=0;j<3;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#E5E5E5;");

            }
    }
    if(rnum>5&&cnum>5)
    {
        for(int i=6;i<9;i++)
            for(int j=6;j<9;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#E5E5E5;");
            }
    }

}
void MainWindow::lowLight(int rnum,int cnum)
{
    for(int i=0;i<9;i++)
    {
        plate[rnum][i]->setStyleSheet("background-color:#D4D4D4;");
        plate[i][cnum]->setStyleSheet("background-color:#D4D4D4;");

    }
    if(rnum<3&&cnum<3)
    {
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#D4D4D4;");
            }
    }
    if(rnum<3&&cnum<6&&cnum>2)
    {
        for(int i=0;i<3;i++)
            for(int j=3;j<6;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#D4D4D4;");
            }
    }
    if(rnum<3&&cnum>5)
    {
        for(int i=0;i<3;i++)
            for(int j=6;j<9;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#D4D4D4;");

            }
    }
    if(rnum>2&&rnum<6&&cnum<3)
    {
        for(int i=3;i<6;i++)
            for(int j=0;j<3;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#D4D4D4;");

            }
    }
    if(rnum>2&&rnum<6&&cnum>5)
    {
        for(int i=3;i<6;i++)
            for(int j=6;j<9;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#D4D4D4;");

            }
    }
    if(rnum>2&&rnum<6&&cnum<6&&cnum>2)
    {
        for(int i=3;i<6;i++)
            for(int j=3;j<6;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#D4D4D4;");

            }
    }
    if(rnum>5&&cnum<6&&cnum>2)
    {
        for(int i=6;i<9;i++)
            for(int j=3;j<6;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#D4D4D4;");
            }
    }
    if(rnum>5&&cnum<3)
    {
        for(int i=6;i<9;i++)
            for(int j=0;j<3;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#D4D4D4;");

            }
    }
    if(rnum>5&&cnum>5)
    {
        for(int i=6;i<9;i++)
            for(int j=6;j<9;j++)
            {
                plate[i][j]->setStyleSheet("background-color:#D4D4D4;");
            }
    }


}



void MainWindow::showWrong(int rnum,int cnum)
{
    for(int i=0;i<9;i++)
      {  if(this->plate[rnum][i]->text() == this->plate[rnum][cnum]->text()&&i!=cnum)
        {
            plate[rnum][i]->setPalette(pal1);
            plate[rnum][cnum]->setPalette(pal1);
        }
         if(this->plate[i][cnum]->text() == this->plate[rnum][cnum]->text()&&i!=rnum)
        {
            plate[i][cnum]->setPalette(pal1);
            plate[rnum][cnum]->setPalette(pal1);
        }
      }
    if(rnum<3&&cnum<3)
    {
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text()&&i!=rnum&&j!=cnum)
                   { plate[i][j]->setPalette(pal1);
                    plate[rnum][cnum]->setPalette(pal1);}
            }
    }
    if(rnum<3&&cnum<6&&cnum>2)
    {
        for(int i=0;i<3;i++)
            for(int j=3;j<6;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text()&&i!=rnum&&j!=cnum)
                   { plate[i][j]->setPalette(pal1);
                    plate[rnum][cnum]->setPalette(pal1);}
            }
    }
    if(rnum<3&&cnum>5)
    {
        for(int i=0;i<3;i++)
            for(int j=6;j<9;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text()&&i!=rnum&&j!=cnum)
                   { plate[i][j]->setPalette(pal1);
                    plate[rnum][cnum]->setPalette(pal1);}

            }
    }
    if(rnum>2&&rnum<6&&cnum<3)
    {
        for(int i=3;i<6;i++)
            for(int j=0;j<3;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text()&&i!=rnum&&j!=cnum)
                   { plate[i][j]->setPalette(pal1);
                    plate[rnum][cnum]->setPalette(pal1);}

            }
    }
    if(rnum>2&&rnum<6&&cnum>5)
    {
        for(int i=3;i<6;i++)
            for(int j=6;j<9;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text()&&i!=rnum&&j!=cnum)
                   { plate[i][j]->setPalette(pal1);
                    plate[rnum][cnum]->setPalette(pal1);}

            }
    }
    if(rnum>2&&rnum<6&&cnum<6&&cnum>2)
    {
        for(int i=3;i<6;i++)
            for(int j=3;j<6;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text()&&i!=rnum&&j!=cnum)
                   { plate[i][j]->setPalette(pal1);
                    plate[rnum][cnum]->setPalette(pal1);}

            }
    }
    if(rnum>5&&cnum<6&&cnum>2)
    {
        for(int i=6;i<9;i++)
            for(int j=3;j<6;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text()&&i!=rnum&&j!=cnum)
                   { plate[i][j]->setPalette(pal1);
                    plate[rnum][cnum]->setPalette(pal1);}

            }
    }
    if(rnum>5&&cnum<3)
    {
        for(int i=6;i<9;i++)
            for(int j=0;j<3;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text()&&i!=rnum&&j!=cnum)
                   { plate[i][j]->setPalette(pal1);
                    plate[rnum][cnum]->setPalette(pal1);}

            }
    }
    if(rnum>5&&cnum>5)
    {
        for(int i=6;i<9;i++)
            for(int j=6;j<9;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text()&&i!=rnum&&j!=cnum)
                   { plate[i][j]->setPalette(pal1);
                    plate[rnum][cnum]->setPalette(pal1);}

            }
    }


}
//void MainWindow::checkRight(int rnum,int cnum)
//{
   /* if(rnum<3&&cnum<6&&cnum>2)
    {
        for(int i=0;i<3;i++)
            for(int j=3;j<6;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text())
                    plate[i][j]->setPalette(pal1);
                else
                    plate[i][j]->setPalette(pal4);
            }
    }
    if(rnum<3&&cnum>5)
    {
        for(int i=0;i<3;i++)
            for(int j=6;j<9;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text())
                    plate[i][j]->setPalette(pal1);
                else
                    plate[i][j]->setPalette(pal4);

            }
    }
    if(rnum>2&&rnum<6&&cnum<3)
    {
        for(int i=3;i<6;i++)
            for(int j=0;j<3;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text())
                    plate[i][j]->setPalette(pal1);
                else
                    plate[i][j]->setPalette(pal4);

            }
    }
    if(rnum>2&&rnum<6&&cnum>5)
    {
        for(int i=3;i<6;i++)
            for(int j=6;j<9;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text())
                    plate[i][j]->setPalette(pal1);
                else
                    plate[i][j]->setPalette(pal4);

            }
    }
    if(rnum>2&&rnum<6&&cnum<6&&cnum>2)
    {
        for(int i=3;i<6;i++)
            for(int j=3;j<6;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text())
                    plate[i][j]->setPalette(pal1);
                else
                    plate[i][j]->setPalette(pal4);

            }
    }
    if(rnum>5&&cnum<6&&cnum>2)
    {
        for(int i=6;i<9;i++)
            for(int j=3;j<6;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text())
                    plate[i][j]->setPalette(pal1);
                else
                    plate[i][j]->setPalette(pal4);
            }
    }
    if(rnum>5&&cnum<3)
    {
        for(int i=6;i<9;i++)
            for(int j=0;j<3;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text())
                    plate[i][j]->setPalette(pal1);
                else
                    plate[i][j]->setPalette(pal4);

            }
    }
    if(rnum>5&&cnum>5)
    {
        for(int i=6;i<9;i++)
            for(int j=6;j<9;j++)
            {
                if(this->plate[i][j]->text()==this->plate[rnum][cnum]->text())
                    plate[i][j]->setPalette(pal1);
                else
                    plate[i][j]->setPalette(pal4);

            }
    }*/

//}
void MainWindow::highlighing()
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(!clickable[i][j])
            {
                plate[i][j]->setStyleSheet("background-color:#C1CDCD;");
            }
        }
}
void MainWindow::highlightnum(int num)
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(gamecore->userAnswer[i][j]==num)
            {
                plate[i][j]->setPalette(pal3);
            }
        }
}

void MainWindow::tablebuttonClicked()
{
    lowLight(x_t,y_t);
    highlighing();
    //showWrong(x_t,y_t);
    widget2->close();
    QPushButton*btn = qobject_cast<QPushButton*>(sender());
    int n=btn->accessibleName().toInt();
    int i=n/10,j=n%10;
    x_t=i;
    y_t=j;
    int num=btn->text().toInt();
    highlightnum(num);

    if(!clickable[x_t][y_t])  return;

    undoStack[stepcount][0]=x_t;
    undoStack[stepcount][1]=y_t;
    undoStack[stepcount][2]=num;

    widget2->show();
    highLight(x_t,y_t);
    //highlighing();
    //showWrong(x_t,y_t);
}

void MainWindow::keyboardclicked()
{
    widget2->close();
    lowLight(x_t,y_t);
    highlighing();
    //showWrong(x_t,y_t);

    if(plate[x_t][y_t]->text()==("×"))  return;

    QPushButton*btn = qobject_cast<QPushButton*>(sender());

    int num=btn->text().toInt();    
    if(num)
    {
        plate[x_t][y_t]->setText(QString::number(num));
        this->gamecore->userAnswer[x_t][y_t]=num;
        this->showWrong(x_t,y_t);
        undoStack[stepcount][3]=num;
    }
    else if(btn->text()=="C")
    {
        plate[x_t][y_t]->setText("");
       this->gamecore->userAnswer[x_t][y_t]=0;
        //checkRight(x_t,y_t);
        undoStack[stepcount][3]=0;
    }
    else if(btn->text()=="M")
    {
        plate[x_t][y_t]->setText("M");
        undoStack[stepcount][3]=10;
    }
    else
    {
        plate[x_t][y_t]->setText(QString::number(gamecore->fullAnswer[x_t][y_t]));
        undoStack[stepcount][3]=gamecore->fullAnswer[x_t][y_t];
    }
    stepcount++;
    stepcount%=10;
    qDebug()<<gamecore->checkWin();
    if(gamecore->checkWin())  {ui->stackedWidget->setCurrentIndex(2);}

}

/*void MainWindow::paintEvent(QPaintEvent *)
{
        QPainter p(this);
        QPen ss;
        ss.setWidth(5);
        ss.setColor(Qt::darkGray);
        p.setPen(ss);
        int bm=ui->menuBar->geometry().bottom();
        for( int i=3 ; i<8; i+=3)
        {
            int x1= (plate[0][i]->geometry().left()+plate[0][i-1]->geometry().right())/2;
            int y1= plate[0][i]->geometry().top();
            int y2=plate[8][i]->geometry().bottom();
            p.drawLine( x1+2 ,y1+2+bm,x1+1,y2+bm );
        }
        for( int i=3 ; i<8; i+=3)
        {
            int y1= (plate[i][0]->geometry().top()+plate[i-1][0]->geometry().bottom())/2;
            int x1= plate[i][0]->geometry().left();
            int x2=plate[i][8]->geometry().right();
            p.drawLine( x1+2 ,y1+1+bm,x2-2,y1+1+bm );
        }

}*/

void MainWindow::addNewGame()
{
    gamecore->getOne();
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
 {   if(this->gamecore->blank[i][j]==1)
    {
        plate[i][j]->setText("");
        clickable[i][j]=true;
        plate[i][j]->setStyleSheet("background-color:#D4D4D4;");
       // plate[i][j]->setPalette(pal4);
    }
    else
    {
        plate[i][j]->setText(QString::number(this->gamecore->fullAnswer[i][j]));
        clickable[i][j]=false;
        plate[i][j]->setStyleSheet("background-color:#C1CDCD;");
    }}
}

void MainWindow::on_delallbutton_2_clicked()
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(clickable[i][j]) {plate[i][j]->setText("");gamecore->userAnswer[i][j]=0;}

}



void MainWindow::on_answerbutton_2_clicked()
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(clickable[i][j]) {plate[i][j]->setText(QString::number(gamecore->fullAnswer[i][j]));
                gamecore->userAnswer[i][j]=gamecore->fullAnswer[i][j];}

}

void MainWindow::on_pulsebutton_2_clicked()
{
    this->timeronWidget->pause();
}


void MainWindow::on_resume_clicked()
{
    this->timeronWidget->resume();

}

void MainWindow::on_undobutton_2_clicked()
{

       if(stepcount>0)
          { stepcount--;

             if(!undoStack[stepcount][2]) plate[undoStack[stepcount][0]][undoStack[stepcount][1]]->setText("");
             else  plate[undoStack[stepcount][0]][undoStack[stepcount][1]]->setText(QString::number(undoStack[stepcount][2]));

          }
       if(!stepcount)
       { stepcount=9;
           if(!undoStack[stepcount][2]) plate[undoStack[stepcount][0]][undoStack[stepcount][1]]->setText("");
           else  plate[undoStack[stepcount][0]][undoStack[stepcount][1]]->setText(QString::number(undoStack[stepcount][2]));

       }
}

void MainWindow::on_redobutton_2_clicked()
{
    if(stepcount<9)
       {

          if(!undoStack[stepcount][3]) plate[undoStack[stepcount][0]][undoStack[stepcount][1]]->setText("");
          else  if(undoStack[stepcount][3]==10) plate[undoStack[stepcount][0]][undoStack[stepcount][1]]->setText("M");
          else plate[undoStack[stepcount][0]][undoStack[stepcount][1]]->setText(QString::number(undoStack[stepcount][3]));
          stepcount++;

       }
    if(stepcount==9)
    {
        if(!undoStack[stepcount][3]) plate[undoStack[stepcount][0]][undoStack[stepcount][1]]->setText("");
        else  if(undoStack[stepcount][3]==10) plate[undoStack[stepcount][0]][undoStack[stepcount][1]]->setStyleSheet("background-color:#EEDC82;");
        else plate[undoStack[stepcount][0]][undoStack[stepcount][1]]->setText(QString::number(undoStack[stepcount][3]));
        stepcount=0;
    }
}

void MainWindow::on_restart_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    initGame();
}

void MainWindow::initGame()
{
    x_t=y_t=stepcount=0;
    gamecore->initblank();
    //gamecore->initblank();
    for(int i=0;i<10;i++)
        for(int j=0;j<4;j++)
            undoStack[i][j]=0;

}

void MainWindow::on_level2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->timeronWidget->start();
    gamecore->hardLevel=2;
   //qDebug()<<gamecore->hardLevel;
    addNewGame();
}



void MainWindow::on_level1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->timeronWidget->start();
    gamecore->hardLevel=1;
   //qDebug()<<gamecore->hardLevel;
    addNewGame();
}

void MainWindow::on_level3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->timeronWidget->start();
    gamecore->hardLevel=3;
   //qDebug()<<gamecore->hardLevel;
    addNewGame();
}

void MainWindow::on_level4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->timeronWidget->start();
    gamecore->hardLevel=4;
   //qDebug()<<gamecore->hardLevel;
    addNewGame();
}

void MainWindow::on_level5_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->timeronWidget->start();
    gamecore->hardLevel=5;
   //qDebug()<<gamecore->hardLevel;
    addNewGame();
}

void MainWindow::on_level6_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->timeronWidget->start();
    gamecore->hardLevel=6;
   //qDebug()<<gamecore->hardLevel;
    addNewGame();
}

void MainWindow::on_level7_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->timeronWidget->start();
    gamecore->hardLevel=7;
   //qDebug()<<gamecore->hardLevel;
    addNewGame();
}

void MainWindow::on_level8_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->timeronWidget->start();
    gamecore->hardLevel=8;
   //qDebug()<<gamecore->hardLevel;
    addNewGame();
}

void MainWindow::on_level9_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->timeronWidget->start();
    gamecore->hardLevel=9;
   //qDebug()<<gamecore->hardLevel;
    addNewGame();
}

void MainWindow::on_level10_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->timeronWidget->start();
    gamecore->hardLevel=10;
   //qDebug()<<gamecore->hardLevel;
    addNewGame();
}
