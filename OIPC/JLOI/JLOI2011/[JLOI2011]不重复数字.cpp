#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<vector>
#include<queue>
#include<map>
#include<set>
#define ll long long
#define PAUSE system("pause")
using namespace std;

int seq[100010]={0},n,T;
map<int,int> mapx;

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

int main()
{
    readx(T);
    while (T--)
    {
        mapx.clear();
        readx(n); memset(seq,0,sizeof seq);
        for (int i=1;i<=n;i++) readx(seq[i]);
        for (int i=1;i<=n;i++) if (!mapx[seq[i]])
        {
            mapx[seq[i]]=1;
            printf("%d ",seq[i]);
        }
        putchar('\n');
    }
    return 0;
}