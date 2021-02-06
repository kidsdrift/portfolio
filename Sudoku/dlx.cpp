#include <cstdio>
#include <cstring>

struct wulala{int x,y,z;};
struct node{
    node *d,*u,*l,*r;
    int line,col;
    wulala x;//这个x结构体是用来标记这个位置所在的行所表示的在数独中的操作
    //x.x,x.y,x.z表示在数独中的[x.x,x.y]位置放一个x.z
    node():d(NULL),u(NULL),l(NULL),r(NULL),line(0),col(0){}
};
node *matrix[750][350];
wulala a[750];
int shudu[10][10];
int map[750][350];
int n,m=324;
bool v[350];//v数组用来记录哪些列已经有1了（这里的列是指矩阵中的）
int gong(int x,int y){return (x-1)/3*3+(y-1)/3+1;}
void input()
{
    for(int i=1;i<=9;i++)
    for(int j=1;j<=9;j++)
    {
        scanf("%d",&shudu[i][j]);
        if(shudu[i][j]!=0)
        {
            v[(i-1)*9+j]=true;//标记这些列已经有1了
            v[81+(i-1)*9+shudu[i][j]]=true;
            v[81*2+(j-1)*9+shudu[i][j]]=true;
            v[81*3+(gong(i,j)-1)*9+shudu[i][j]]=true;
        }
    }
    for(int i=1;i<=9;i++)//构建矩阵
    for(int j=1;j<=9;j++)
    if(shudu[i][j]==0)
    for(int k=1;k<=9;k++)
    if(!v[81+(i-1)*9+k]&&!v[81*2+(j-1)*9+k]&&!v[81*3+(gong(i,j)-1)*9+k])
    //如果这种方案中有某一列是被标记过的，这种方案就是不能选的
    {
        n++;
        map[n][(i-1)*9+j]=1;
        map[n][81+(i-1)*9+k]=1;
        map[n][81*2+(j-1)*9+k]=1;
        map[n][81*3+(gong(i,j)-1)*9+k]=1;
        a[n]=(wulala){i,j,k};
    }
}
//=====================================================================
//以下为DLX算法模板，如果看不懂可以去文章开头的那个超链接里面看看
node *head,*c[350];
int tot[350];
void work()
{
    node *p;
    for(int i=1;i<=n;i++)
    {
        p=NULL;
        for(int j=1;j<=m;j++)
        if(map[i][j]==1)
        {
            matrix[i][j]=new node;
            matrix[i][j]->line=i;matrix[i][j]->col=j;
            matrix[i][j]->x=a[i];
            if(p==NULL)p=matrix[i][j],p->l=p->r=p;
            else
            {
                p->r->l=matrix[i][j];matrix[i][j]->r=p->r;
                p->r=matrix[i][j];matrix[i][j]->l=p;
                p=matrix[i][j];
            }
        }
        else matrix[i][j]=NULL;
    }
    p=head=new node;p->l=p->r=p;
    for(int i=1;i<=m;i++)
    if(v[i])c[i]=NULL;//假如这一列已经有1了，那么就不要这一列了2
    else
    {
        c[i]=new node();tot[i]=0;
        p->r->l=c[i];c[i]->r=p->r;
        p->r=c[i];c[i]->l=p;p=c[i];
        c[i]->col=i;
    }
    for(int j=1;j<=m;j++)
    {
        if(v[j])continue;//被标记过的列就没必要遍历了，毕竟这一列半个1都不可能有
        p=c[j];p->d=p->u=p;
        for(int i=1;i<=n;i++)
        if(map[i][j]==1)
        {
            tot[j]++;
            p->d->u=matrix[i][j];matrix[i][j]->d=p->d;
            p->d=matrix[i][j];matrix[i][j]->u=p;
            p=matrix[i][j];
        }
    }
}
void print()
{
    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=9;j++)
        printf("%d ",shudu[i][j]);
        printf("\n");
    }
}
bool anss;
node *zhan[750];
int tt;
inline void del1(node *x){x->l->r=x->r;x->r->l=x->l;}
inline void del2(node *x){x->d->u=x->u;x->u->d=x->d;}
inline void reset1(node *x){x->l->r=x;x->r->l=x;}
inline void reset2(node *x){x->u->d=x;x->d->u=x;}
void down(node *x)
{
    for(node *i=x->d;i!=x;i=i->d)
    {
        if(i->line==0)continue;
        zhan[++tt]=i;
        del2(i),tot[i->col]--;
        for(node *j=i->r;j!=i;j=j->r)
        del2(j),tot[j->col]--;
    }
}
void dfs()
{
    if(head->r==head)
    {
        anss=true;
        print();
        return;
    }
    node *p=head->r;
    for(node *i=p->r;i!=head;i=i->r)
    if(tot[i->col]<tot[p->col])p=i;
    for(node *i=p->d;i!=p;i=i->d)
    {
        int st=tt;
        down(i);del1(c[i->col]);
        for(node *j=i->r;j!=i;j=j->r)
        down(j),del1(c[j->col]);
        zhan[++tt]=i;
        del2(i),tot[i->col]--;
        for(node *j=i->r;j!=i;j=j->r)
        del2(j),tot[j->col]--;
        shudu[i->x.x][i->x.y]=i->x.z;//记得标记一下这一次的选择
        dfs();
        if(anss)return;
        for(node *j=zhan[tt]->l;j!=zhan[tt];j=j->l)
        reset1(c[j->col]);
        reset1(c[zhan[tt]->col]);
        while(tt>st)
        {
            reset2(zhan[tt]),tot[zhan[tt]->col]++;
            for(node *j=zhan[tt]->r;j!=zhan[tt];j=j->r)
            reset2(j),tot[j->col]++;
            tt--;
        }
    }
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        n=0;
        memset(v,false,sizeof(v));
        memset(map,0,sizeof(map));
        input();
        work();
        anss=false;tt=0;
        dfs();
    }
}

