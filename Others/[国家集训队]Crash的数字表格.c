#include<stdio.h>
#include<string.h>
#include<math.h>
#define ll long long

int pnum[10000100],ptr=0; char nnum[10000100];
int S[10000100],theta[10000100],stheta[10000100];
const ll mod=20101009;

void readx(ll* x)
{
    (*x)=0; int k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { (*x)=(*x)*10+ch-'0'; ch=getchar(); }
    (*x)*=k;
}

void Theta_Shake(int upat)
{
    theta[1]=1;
    for (int i=2;i<=upat;i++)
    {
        if (!nnum[i]) { pnum[++ptr]=i; theta[i]=(mod+1-i)%mod; }
        for (int j=1;j<=ptr && i*pnum[j]<=upat;j++)
        {
            nnum[i*pnum[j]]=1;
            if (!(i%pnum[j])) { theta[i*pnum[j]]=theta[i]; break; }
            theta[i*pnum[j]]=(1LL*theta[i]*theta[pnum[j]])%mod;
        }
    }
    
    for (int i=1;i<=upat;i++) stheta[i]=(stheta[i-1]+(1LL*theta[i]*i)%mod)%mod;
    for (int i=1;i<=upat;i++) S[i]=(S[i-1]+i)%mod;
}

int min(int aa,int ab) { return aa<ab?aa:ab; }
int max(int aa,int ab) { return aa>ab?aa:ab; }

int main()
{
    
    ll ans=0,A,B,x;
    readx(&A); readx(&B); x=min(A,B);
    Theta_Shake(max(A,B));
    for (int l=1,r;l<=x;l=r+1)
    {
        r=min(A/(A/l),B/(B/l));
        ans=(ans+ 1LL*((1LL*S[A/l]*S[B/l])%mod *(stheta[r]-stheta[l-1]+mod) )%mod )%mod;
    }
    printf("%lld\n",ans);
}
