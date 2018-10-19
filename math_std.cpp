#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#define mod 998244353
#define ll long long
using namespace std;
 
int pnum[5000010],nnum[5000010],ptr=0;
int M,K;
 
ll mmul[5000010][24],F[5000010];
 
ll fastpow(ll an,ll p)
{
    ll ret=1;
    for (;p;p>>=1,an=(an*an)%mod) if (p&1) ret=(ret*an)%mod;
    return ret;
}
 
void Prime_Shake(int upat)
{
    nnum[0]=nnum[1]=1;
    for (int i=2;i<=upat;i++)
    {
        if (!nnum[i]) pnum[++ptr]=i;
        for (int j=1;j<=ptr && i*pnum[j]<=upat;j++)
        {
            nnum[i*pnum[j]]=1;
            if (!(i%pnum[j])) break;
        }
    }
}
 
void F_Shake(int upat)
{
    nnum[0]=nnum[1]=1; F[1]=1;
    for (int i=2;i<=upat;i++)
    {
        if (!nnum[i]) { pnum[++ptr]=i; F[i]=mmul[ptr][1]; }
        for (int j=1;j<=ptr && pnum[j]*i<=upat;j++)
        {
            nnum[i*pnum[j]]=1;
            if (!(i%pnum[j]))
            {
                int tmp=0,tmp2=i;
                while (!(tmp2%pnum[j])) { tmp++; tmp2/=pnum[j]; }
                F[i*pnum[j]]=(mmul[j][tmp+1]*F[tmp2])%mod;
                break;
            }
            else F[i*pnum[j]]=(F[i]*F[pnum[j]])%mod;
        }
    }
}
 
int main()
{
    scanf("%d%d",&M,&K);
    Prime_Shake(5000000);
    for (int i=1;i<=ptr;i++)
        for (int j=1;j<=23;j++)
            mmul[i][j]=((fastpow(pnum[i],j*K)-fastpow(pnum[i],(j-1)*K))%mod+mod)%mod;
     
    memset(nnum,0,sizeof nnum);
    ptr=0; memset(pnum,0,sizeof pnum);
    F_Shake(5000000);
     
    int tmp;
    for (int i=1;i<=M;i++)
    {
        scanf("%d",&tmp);
        printf("%lld\n",F[tmp]);
    }
}