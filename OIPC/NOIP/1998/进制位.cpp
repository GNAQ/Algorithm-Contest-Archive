// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
#define ll long long
using namespace std;

char G[12][12][12];
int n;
char mapx[150],nums[150];

template<typename int_t>
void readx(int_t& x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

bool check()
{
    for (int i=2;i<=n;i++)
        for (int j=2;j<=n;j++)
        {
            int a=mapx[G[i][1][1]],b=mapx[G[1][j][1]];
            a+=b;
            if (a<n-1)
            {
                if (strlen(G[i][j]+1)!=1) return 0;
                if (G[i][j][1]!=nums[a]) return 0;
            }
            else
            {
                if (strlen(G[i][j]+1)!=2) return 0;
                if (G[i][j][1]!=nums[1]) return 0;
                if (G[i][j][2]!=nums[a-n+1]) return 0;
            }
        }
    return 1;
}

int main()
{
    readx(n);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            scanf("%s",G[i][j]+1);
    
    for (int i=2;i<=n;i++)
    {
        bool flag=1;
        for (int j=2;j<=n;j++) if (G[i][j][1]!=G[1][j][1]) flag=0;
        if (flag)
        {
            mapx[G[i][1][1]]=0;
            nums[0]=G[i][1][1];
            break;
        }
    }
    
    for (int i=2;i<=n;i++)
        for (int j=2;j<=n;j++) if (strlen(G[i][j]+1)==2)
        {
            nums[1]=G[i][j][1];
            mapx[G[i][j][1]]=1;
            goto step_3;
        }
    step_3:
    
    for (int w=2;w<=n;w++) if (G[w][1][1]==nums[1])
    {
        for (int i=2;i<n-2;i++)
            for (int j=2;j<=n;j++)
                if (G[1][j][1]==nums[i-1])
                {
                    nums[i]=G[w][j][1];
                    mapx[G[w][j][1]]=i;
                }
        for (int j=2;j<=n;j++) if (strlen(G[w][j]+1)==2)
        {
            nums[n-2]=G[1][j][1];
            mapx[G[1][j][1]]=n-2;
        }
        break;
    }
    
    if (check())
    {
        for (int i=0;i<n-1;i++) printf("%c=%d%c",G[1][i+2][1],mapx[G[1][i+2][1]]," \n"[i==n-2]);
        printf("%d\n",n-1);
    }
    else printf("ERROR!\n");
    return 0;
}
