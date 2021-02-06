#ifndef SOLVER_H
#define SOLVER_H

#include<cstdio>
class Solver
{
    int solvemap[9][9];
    bool flag;
public:
    void dfs(int n);
    bool checkok(int m,int n);
    void getProblem(int[9][9],int[9][9]);
    void solving();

};

#endif // SOLVER_H
