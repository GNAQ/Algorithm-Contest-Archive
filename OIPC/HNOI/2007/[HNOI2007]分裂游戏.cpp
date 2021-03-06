#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

int T,n,seq[10010],sg[30];

template<typename int_t>
void readx(int_t& x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

int CalcSG(int x)
{
    if (x==n) return 0;
    if (sg[x]!=-1) return sg[x];
    bool vis[10010]; memset(vis,0,sizeof vis);
    for (int j=x+1;j<=n;j++)
        for (int k=j;k<=n;k++)
            vis[CalcSG(j)^CalcSG(k)]=1;
    for (int i=0;;i++) if (!vis[i]) return sg[x]=i;
}

int main()
{
    readx(T);
    while (T--)
    {
        memset(sg,-1,sizeof sg); readx(n); int ans=0,cnt=0;
        for (int i=1;i<=n;i++) readx(seq[i]);
        for (int i=1;i<=n;i++) if (seq[i]&1) ans^=CalcSG(i);
        
        for (int i=1;i<=n;i++)
            for (int j=i+1;j<=n;j++)
                for (int k=j;k<=n;k++) if (!(ans^CalcSG(i)^CalcSG(j)^CalcSG(k)))
                {
                    if (!cnt) printf("%d %d %d\n",i-1,j-1,k-1);
                    cnt++;
                }

        if (!cnt) printf("-1 -1 -1\n");
        printf("%d\n",cnt);
    }
}
