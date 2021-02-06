#include "sudoku.h"
#include"solver.h"
#include <random>
#include<QDebug>

void Sudoku::getrandom()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
       std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
       std::uniform_int_distribution<> dis(0, 8);
    for(int i=0;i<1000;i++)
        randomnum[i]=dis(gen);
}

void Sudoku::simplec(int a, int b)
{
    for(int i=0;i<9;i++)
    {
       int c = fullAnswer[i][a];
       fullAnswer[i][a]=fullAnswer[i][b];
       fullAnswer[i][b]=c;
    }
}
void Sudoku::simpler(int a, int b)
{
    for(int i=0;i<9;i++)
    {
       int c = fullAnswer[a][i];
       fullAnswer[a][i]=fullAnswer[b][i];
       fullAnswer[b][i]=c;
    }
}

void Sudoku::exchangeCol()
{
    for(int big=0;big<7;big+=3)
    {int condi=(randomnum[count])%3;count++;
    switch(condi)
    {
        case 0: simplec(1+big,0+big);break;
        case 1: simplec(1+big,2+big);break;
        case 2: simplec(2+big,0+big);break;

    }
    }

}
void Sudoku::exchangeRow()
{
    for(int big=0;big<7;big+=3)
    {int condi=(randomnum[count])%3;count++;
    switch(condi)
    {
        case 0: simpler(1+big,0+big);break;
        case 1: simpler(1+big,2+big);break;
        case 2: simpler(2+big,0+big);break;

    }
    }

}
void Sudoku::exchangeNum()
{
    int num1=randomnum[count];count++;
    int num2=randomnum[count];count++;
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(fullAnswer[i][j]==num1) fullAnswer[i][j]=0;
            if(fullAnswer[i][j]==num2) fullAnswer[i][j]=num1;
            if(fullAnswer[i][j]==0) fullAnswer[i][j]=num2;

        }
}

void Sudoku::hardc(int a, int b)
{
    for(int i=0;i<3;i++)
        {
            simplec(i+a*3,i+b*3);
        }
}
void Sudoku::hardr(int a, int b)
{
    for(int i=0;i<3;i++)
        {
            simpler(i+a*3,i+b*3);
        }
}

void Sudoku::colswap()
{
    int condi=(randomnum[count])%3;count++;
    switch(condi)
    {
        case 0: hardc(0,1);break;
        case 1: hardc(0,2);break;
        case 2: hardc(2,1);break;

    }

}
void Sudoku::rowswap()
{
    int condi=(randomnum[count])%3;count++;
    switch(condi)
    {
        case 0: hardr(0,1);break;
        case 1: hardr(0,2);break;
        case 2: hardr(2,1);break;

    }
}
void Sudoku::initblank()
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            blank[i][j]=1;
        }
}

void Sudoku::getBlank()
{
    initblank();
    //qDebug()<<hardLevel;
    if(hardLevel==1)
    {   int cnt=45;
        while(cnt>0)
        {
      int rownum=randomnum[count];count++;
      //qDebug()<<rownum;
      int clonum=randomnum[count];count++;
            if(blank[rownum][clonum]) {blank[rownum][clonum]=0;cnt--;}
        }
        /*for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
            {
                blank[i][j]=templa1[i][j];
            }*/
    }
    if(hardLevel==2)
    {
        int cnt=41;
               while(cnt>0)
               {
             int rownum=randomnum[count];count++;
             //qDebug()<<rownum;
             int clonum=randomnum[count];count++;
                   if(blank[rownum][clonum]) {blank[rownum][clonum]=0;cnt--;}
               }
        /*for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
            {
                blank[j][i]=templa2[i][j];
            }*/

    }
    if(hardLevel==3) //(hardLevel==3)
    {

        int cnt=37;
               while(cnt>0)
               {
             int rownum=randomnum[count];count++;
             //qDebug()<<rownum;
             int clonum=randomnum[count];count++;
                   if(blank[rownum][clonum]) {blank[rownum][clonum]=0;cnt--;}
               }

         /*for(int i=0;i<22;i++)
         {
             int rownum=randomnum[count];count++;
             qDebug()<<rownum;
             int clonum=randomnum[count];count++;
             blank[rownum][clonum]=0;
         }

        /*for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
            {
                blank[i][j]=templa3[i][j];
            }*/

    }
    if(hardLevel==4) //(hardLevel==3)
    {

        int cnt=33;
               while(cnt>0)
               {
             int rownum=randomnum[count];count++;
             //qDebug()<<rownum;
             int clonum=randomnum[count];count++;
                   if(blank[rownum][clonum]) {blank[rownum][clonum]=0;cnt--;}
               }
     }
    if(hardLevel==5) //(hardLevel==3)
    {

        int cnt=29;
               while(cnt>0)
               {
             int rownum=randomnum[count];count++;
             //qDebug()<<rownum;
             int clonum=randomnum[count];count++;
                   if(blank[rownum][clonum]) {blank[rownum][clonum]=0;cnt--;}
               }
     }
    if(hardLevel==6) //(hardLevel==3)
    {

        int cnt=26;
               while(cnt>0)
               {
             int rownum=randomnum[count];count++;
             //qDebug()<<rownum;
             int clonum=randomnum[count];count++;
                   if(blank[rownum][clonum]) {blank[rownum][clonum]=0;cnt--;}
               }
     }
    if(hardLevel==7) //(hardLevel==3)
    {

        int cnt=24;
               while(cnt>0)
               {
             int rownum=randomnum[count];count++;
             //qDebug()<<rownum;
             int clonum=randomnum[count];count++;
                   if(blank[rownum][clonum]) {blank[rownum][clonum]=0;cnt--;}
               }
     }
    if(hardLevel==8) //(hardLevel==3)
    {

        int cnt=22;
               while(cnt>0)
               {
             int rownum=randomnum[count];count++;
             //qDebug()<<rownum;
             int clonum=randomnum[count];count++;
                   if(blank[rownum][clonum]) {blank[rownum][clonum]=0;cnt--;}
               }
     }
    if(hardLevel==9) //(hardLevel==3)
    {

        int cnt=20;
               while(cnt>0)
               {
             int rownum=randomnum[count];count++;
             //qDebug()<<rownum;
             int clonum=randomnum[count];count++;
                   if(blank[rownum][clonum]) {blank[rownum][clonum]=0;cnt--;}
               }
     }
    if(hardLevel==10) //(hardLevel==3)
    {

        int cnt=17;
               while(cnt>0)
               {
             int rownum=randomnum[count];count++;
             //qDebug()<<rownum;
             int clonum=randomnum[count];count++;
                   if(blank[rownum][clonum]) {blank[rownum][clonum]=0;cnt--;}
               }
     }

}
void Sudoku::getOne()
{
    getrandom();
    getBlank();
    solver = new Solver;
    solver->getProblem(fullAnswer,blank);
    solver->solving();

    int times =randomnum[count];count++;
    //qDebug()<<times;
    for(int i=0;i<times;i++)
    {
        exchangeCol();
        exchangeRow();
        exchangeNum();
        colswap();
        rowswap();
    }
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(!blank[i][j])
            userAnswer[i][j]=fullAnswer[i][j];
            else
            userAnswer[i][j]=0;
        }
}

bool Sudoku::checkWin()
{
    bool mark  = true;
    for(int i=0;i<9;i++)
    {    for(int j=0;j<9;j++)
        {

            if(blank[i][j]==1&&fullAnswer[i][j]!=userAnswer[i][j])
            {
                mark = false;
                break;
            }
        }
          if(mark == false) break;
    }
    return mark;

}
