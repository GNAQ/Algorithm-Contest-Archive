#pragma GCC optimize ("Ofast")
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<iterator>
#include<queue>
#include<cmath>
#include<vector>
#include<cstdlib>
#include<map>
#include<set>
#define PAUSE system("pause")
#define ll long long
using namespace std;

struct ed
{
    int pre,to;
}edge[1000010]={0,0};
int at=1,ptr[10010]={0},matchs[10010],vis[10010],ansf;

int n,m,mapsiz;
char mapx[2200][2200]={0};
bool av[2200][2200]={0},l[2200]={0},h[2200]={0};
int pau[2200][2]={0};

int wx[8]={0,-1,-1,-1,0,1,1,1},wy[8]={-1,-1,0,1,1,1,0,-1};
int KX[8]={-1,-2,-2,-1,1,2,2,1},KY[8]={-2,-1,1,2,2,1,-1,-2};

inline void Insert(int fx,int tx)
{
    at++;
    edge[at].pre=ptr[fx];
    edge[at].to=tx;
    ptr[fx]=at;
}

inline bool Find(int x,int src)
{
    for (int prex=ptr[x];prex;prex=edge[prex].pre) if (vis[edge[prex].to]!=src)
    {
        vis[edge[prex].to]=src;
        if (!matchs[edge[prex].to] || Find(matchs[edge[prex].to],src)) { matchs[edge[prex].to]=x; return true; }
    }
    return false;
}

inline void BuildG()
{
    int _x,_y;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++) if (!av[i][j])
        {
            _x=pau[i][0]+j-1; _y=pau[i][1]+j-1;
            if ((!h[_x]) && (!l[_y])) Insert(_x,_y+mapsiz);
        }
}

inline void GoB(int _x,int _y)
{
    av[_x][_y]=true;
    int i=pau[_x][0]+_y-1,j=pau[_x][1]+_y-1;
    h[i]=true; l[j]=true;
}
inline void GoK(int _x,int _y)
{
    GoB(_x,_y);
    for (int w=0;w<=7;w++) av[_x+wx[w]][_y+wy[w]]=true;
}
inline void GoQ(int _x,int _y)
{
    int wayx[4]={0,-1,0,1},wayy[4]={-1,0,1,0};
    GoB(_x,_y);
    for (int w=0;w<=3;w++) for (int i=1;;i++)
    {
        if (mapx[_x+wayx[w]*i][_y+wayy[w]*i]!='.') break;
        av[_x+wayx[w]*i][_y+wayy[w]*i]=true;
    }
}
inline void GoN(int _x,int _y)
{
    GoB(_x,_y);
    for (int w=0;w<=7;w++) if (_x+KX[w]>0 && _y+KY[w]>0) av[_x+KX[w]][_y+KY[w]]=true;
}

int main()
{
    scanf("%d%d",&n,&m);mapsiz=2*max(n,m)-1;
    for (int i=1;i<=n;i++) scanf("%s",mapx[i]+1);
    
    pau[1][0]=1; pau[1][1]=m;
    for (int i=2;i<=n;i++) { pau[i][0]=pau[i-1][0]+1; pau[i][1]=pau[i-1][1]-1; }
    
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
        {
            if (mapx[i][j]=='.') continue;
            switch (mapx[i][j])
            {
                case 'K':
                    GoK(i,j);
                    break;
                case 'Q':
                    GoQ(i,j);
                    break;
                case 'R':
                    GoQ(i,j);
                    break;
                case 'B':
                    GoB(i,j);
                    break;
                case 'P':
                    GoB(i,j);
                    break;
                case 'N':
                    GoN(i,j);
                    break;
            }
        }
    
    BuildG();
    for (int i=1;i<=mapsiz;i++) ansf+=Find(i,i);
    printf("%d\n",ansf);
    // PAUSE;
    return 0;
}