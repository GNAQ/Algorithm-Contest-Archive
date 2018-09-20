#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<queue>
#include<vector>
using namespace std;

int seq[110]={0},n,m;
double dp[60][60];

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

int main()
{
    readx(n); readx(m); 
    for (int i=1;i<=m;i++) readx(seq[i]);

    dp[1][1]=100.00000;
    for (int i=2;i<=n;i++)
        for (int j=1;j<=i;j++)
            for (int k=1;k<=m;k++)
            {
                int placex=(seq[k]-1)%i+1;
                if (placex!=j) dp[i][j]+=dp[i-1][(j-placex+i-1)%i+1]/(double)m;
            }
    for (int i=1;i<=n;i++) printf("%.2lf%c ",dp[n][i],"%%\n"[i==n]);
    return 0;
}