// luogu-judger-enable-o2
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
using namespace std;

ll pnum[100010]={0},ptr;
char nnum[100010]={0};

ll S,anses[200010]={0},ctr=0;
ll seq[100010]={0};

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline void Prime_Shake(int upat)
{
    nnum[0]=nnum[1]=1;
    for (int i=2;i<=upat;i++)
    {
        if (!nnum[i]) pnum[++ptr]=i;
        for (int j=1;j<=ptr && pnum[j]*i<=upat;j++)
        {
            nnum[pnum[j]*i]=true;
            if (!(i%pnum[j])) break;
        }
    }
}

inline bool is_prime(int inx)
{
    if (inx<=1) return false;
    if (inx<=100000) return nnum[inx]^1;
    for (int i=1;pnum[i]*pnum[i]<=inx;i++)
        if (!(inx%pnum[i])) return false;
    return true;
}

inline void DFS(ll _x,ll _sum,int _inx)
{
    if (_x==1) { anses[++ctr]=_sum; return; }
    if (_x-1>=pnum[_inx] && is_prime(_x-1)) anses[++ctr]=_sum*(_x-1);
    
    ll tmp=0,rec;
    for (int i=_inx;pnum[i]*pnum[i]<=_x;i++)
    {
        tmp=pnum[i]; rec=pnum[i]+1;
        for (;rec<=_x;tmp*=pnum[i],rec+=tmp) if (!(_x%rec)) DFS(_x/rec,_sum*tmp,i+1);
    }
}

int main()
{
    Prime_Shake(100000);
    while (scanf("%lld",&S)!=EOF)
    {
        memset(anses,0,sizeof anses); ctr=0;
        DFS(S,1LL,1);
        sort(anses+1,anses+ctr+1);
        printf("%lld\n",ctr);
        for (int i=1;i<=ctr;i++) printf("%lld%c",anses[i]," \n"[i==ctr]);
    }
}