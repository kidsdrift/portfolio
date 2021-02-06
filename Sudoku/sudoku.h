#ifndef SUDOKU_H
#define SUDOKU_H
class Solver;

class Sudoku
{
public:
    int blank[9][9];
    int userAnswer[9][9];
    int fullAnswer[9][9]=
    {{1,2,3,4,5,6,7,8,9},
     {4,5,6,7,8,9,1,2,3},
     {7,8,9,1,2,3,4,5,6},
     {2,3,4,5,6,7,8,9,1},
     {5,6,7,8,9,1,2,3,4},
     {8,9,1,2,3,4,5,6,7},
     {3,4,5,6,7,8,9,1,2},
     {6,7,8,9,1,2,3,4,5},
     {9,1,2,3,4,5,6,7,8}};
    Solver* solver;


    /*int templa1[9][9]=
    {{0,1,1,1,0,0,1,0,1},
    {0,0,0,1,1,1,1,0,1},
    {0,1,1,1,0,0,0,1,1},
    {1,1,0,1,0,0,1,1,0},
    {0,0,0,1,1,0,1,0,0},
    {1,1,1,1,0,0,0,0,1},
    {1,0,0,1,0,1,1,1,0},
    {0,1,1,1,0,1,0,0,1},
    {1,0,1,1,1,0,0,0,1}};
    int templa2[9][9]=
    {{0,1,1,1,0,1,0,0,1},
    {1,0,0,1,1,1,1,0,1},
    {0,1,1,1,0,1,1,1,1},
    {1,1,0,1,0,0,1,1,0},
    {0,0,0,1,1,0,1,0,0},
    {0,1,1,1,0,0,1,0,1},
    {1,0,0,1,0,1,1,1,0},
    {1,0,1,1,1,0,0,1,1},
    {1,1,1,1,0,1,0,0,1}};
    int templa3[9][9]=
    {
    {1,1,1,1,0,1,1,1,1},
    {1,1,0,1,0,0,1,1,0},
     {0,1,1,1,1,1,0,0,1},
     {1,0,0,1,1,1,1,1,0},
    {0,1,1,1,0,0,1,0,1},
     {1,1,0,1,1,1,1,0,1},
    {1,0,1,1,1,0,0,1,1},
    {1,1,1,1,0,1,0,0,1},
    {1,0,0,1,1,0,1,0,0}};*/

    int hardLevel,count=0;
    int randomnum[1000];
    void initblank();
    void getOne();
    void getBlank();
    void exchangeCol();
    void exchangeRow();
    void exchangeNum();
    void colswap();
    void rowswap();
    bool checkWin();
    void simplec(int a,int b);
    void simpler(int a,int b);
    void hardc(int a,int b);
    void hardr(int a,int b);
    void getrandom();

};

#endif // SUDOKU_H
