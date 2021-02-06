#include "solver.h"
void Solver::getProblem(int answer[9][9],int blank[9][9])
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(!blank[i][j]) solvemap[i][j]=answer[i][j];
            else solvemap[i][j]=0;
        }
}
bool Solver::checkok(int n,int m)
{
    int r=n/9;
    int c=n%9;
       for(int j=0; j<9; j++)
           if (solvemap[r][j]==m)
               return false;
       for(int i=0; i<9; i++)
           if (solvemap[i][c]==m)
               return false;
       int x = r/3*3;
       int y = c/3*3;
       for(int i = x; i < x + 3; i++)
           for(int j = y; j < y + 3; j++)
               if (solvemap[i][j] == m)
                   return false;
       return true;
}
void Solver::dfs(int n)
{
    if(n > 80 || flag)
       {
           flag = true;
           return;
       }
       if(solvemap[n / 9][n % 9])
       {
           dfs(n + 1);
           if(flag)
               return;
       }
       else
       {
           for(int cur = 1; cur <= 9; cur++)
           {
               if(checkok(n,cur))
               {
                   solvemap[n / 9][n % 9] = cur;
                   dfs(n + 1);
                   if(flag)
                       return;
                   solvemap[n / 9][n % 9] = 0;
               }
           }
       }
}
void Solver::solving()
{
    flag=false;
    dfs(0);
}
