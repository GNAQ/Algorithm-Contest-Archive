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
typedef long long ll;
using namespace std;

const ll mod=998244353;


template<typename inp_t>
void readx(inp_t& x)
{
    x=0; int k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

ll fastpow(ll an,ll p)
{
    ll ret=1;
    for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
    return ret;
}

namespace FFT
{
    const ll G=3;
    const ll iG=fastpow(G,mod-2);
    
    int revf,rev[600010];
    template<typename poly_t>
    void BtFl(poly_t* y,int len)
    {
        if (len!=revf)
        {
            revf=len; int tmp=1,revt=-1;
            while (tmp<len) { tmp<<=1; revt++; }
            for (int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<revt);
        }
        for (int i=0;i<len;i++) if (i<rev[i]) swap(y[i],y[rev[i]]);
    }
    
    void NTT(ll* y,int len,int mode)
    {
        BtFl(y,len);
        for (int i=1;i<len;i<<=1)
        {
            ll wn=fastpow((mode==1)?G:iG,(mod-1)/(i<<1));
            for (int j=0;j<len;j+=(i<<1))
            {
                ll w=1;
                for (int k=0;k<i;k++,w=w*wn%mod)
                {
                    ll t1=y[j+k],t2=y[i+j+k]*w%mod;
                    y[j+k]=(t1+t2)%mod;
                    y[i+j+k]=(t1-t2+mod)%mod;
                }
            }
        }
        if (mode==-1)
        {
            ll inv=fastpow(len,mod-2);
            for (int i=0;i<len;i++) y[i]=y[i]*inv%mod;
        }
    }
};

namespace PCAL
{
    using namespace FFT;
    
    ll tmp_poly[100010],Q[100010];
    ll tR[100010],tG[100010],Ginv[100010];
    
    void PolyInv(ll* A,ll* B,ll* C,int _n)
    {
        if (_n==1) { B[0]=fastpow(A[0],mod-2); return; }
        PolyInv(A,B,C,(_n+1)/2);
        
        ll len=1; while (len<(_n*2)) len<<=1;
        for (int i=0;i<len;i++) C[i]=A[i];
        for (int i=_n;i<len;i++) B[i]=C[i]=0;
        NTT(C,len,1); NTT(B,len,1);
        for (int i=0;i<len;i++) B[i]=(2-B[i]*C[i]%mod+mod)%mod*B[i]%mod;
        NTT(B,len,-1);
        for (int i=_n;i<len;i++) B[i]=0;
    }
    
    void PolyDiv(vector<ll>& F,vector<ll>& G,vector<ll>& R,int _n,int _m)
    {
        ll len=1; while(len<(_n-_m+1)) len<<=1;
        for (int i=0;i<=_m;i++) tG[i]=G[_m-i];
        for (int i=_m+1;i<len;i++) tG[i]=0;
        PolyInv(tG,Ginv,tmp_poly,_n-_m+1);
        
        len=1; while (len<(_n-_m+1)*2) len<<=1;
        for (int i=0;i<=_n;i++) Q[i]=F[_n-i];
        for (int i=_n-_m+1;i<len;i++) Q[i]=Ginv[i]=0;
        NTT(Q,len,1); NTT(Ginv,len,1);
        for (int i=0;i<len;i++) Q[i]=Q[i]*Ginv[i]%mod;
        NTT(Q,len,-1); reverse(Q,Q+(_n-_m+1));
        
        len=1; while (len<(_m + _n-_m+1)) len<<=1;
        for (int i=0;i<_n-_m+1;i++) tR[i]=Q[i];
        for (int i=_n-_m+1;i<len;i++) tR[i]=0;
        for (int i=0;i<=_m;i++) tG[i]=G[i];
        for (int i=_m+1;i<len;i++) tG[i]=0;
        NTT(tG,len,1); NTT(tR,len,1);
        for (int i=0;i<len;i++) tR[i]=tR[i]*tG[i]%mod;
        NTT(tR,len,-1);
        
        R.resize(_m+2); for (int i=0;i<_m;i++) R[i]=(F[i]-tR[i]+mod)%mod;
    }
    
    void Drivative(ll* A,ll* B,int len)
    {
        for (int i=0;i<len-1;i++) B[i]=(A[i+1]*(i+1))%mod;
        B[len-1]=0;
    }
    
    void Intergral(ll* A,ll* B,int len)
    {
        for (int i=0;i<len-1;i++) B[i+1]=(A[i]*fastpow(i+1,mod-2))%mod;
        B[0]=0;
    }
};

namespace FEV
{
    using namespace PCAL;
    
    vector<ll> P[600010],A[600010];
    ll tA[600010],tB[600010]; int deg[600010];
    ll ans[600010];
    
    void FEV_Init(int inx,int lx,int rx,vector<ll>& poly)
    {
        if (lx==rx)
        {
            P[inx].resize(2); deg[inx]=1;
            P[inx][0]=(mod-(poly[lx]%mod))%mod;
            P[inx][1]=1; return;
        }
        int mid=(lx+rx)>>1;
        FEV_Init(inx<<1,lx,mid,poly); FEV_Init(inx<<1|1,mid+1,rx,poly);
        
        deg[inx]=deg[inx<<1]+deg[inx<<1|1]; P[inx].resize(deg[inx]+1);
        ll len=1; while (len<=deg[inx]) len<<=1;
        for (int i=0;i<=deg[inx<<1];i++) tA[i]=P[inx<<1][i];
        for (int i=0;i<=deg[inx<<1|1];i++) tB[i]=P[inx<<1|1][i];
        for (int i=deg[inx<<1]+1;i<len;i++) tA[i]=0;
        for (int i=deg[inx<<1|1]+1;i<len;i++) tB[i]=0;
        
        NTT(tA,len,1); NTT(tB,len,1);
        for (int i=0;i<len;i++) tA[i]=tA[i]*tB[i]%mod;
        NTT(tA,len,-1);
        for (int i=0;i<=deg[inx];i++) P[inx][i]=tA[i];
    }
    
    void FastEva(int inx,int lx,int rx)
    {
        if (lx==rx) { ans[lx]=A[inx][0]; return; }
        int mid=(lx+rx)>>1;
        
        PolyDiv(A[inx],P[inx<<1],A[inx<<1],deg[inx]-1,deg[inx<<1]);
        FastEva(inx<<1,lx,mid);
        
        PolyDiv(A[inx],P[inx<<1|1],A[inx<<1|1],deg[inx]-1,deg[inx<<1|1]);
        FastEva(inx<<1|1,mid+1,rx);
    }
    
};

// DEBUG
/*
int n,m;
vector<ll> val,poly;

void Debug_FEV()
{
    readx(n); readx(m); val.resize(m+10); poly.resize(n+10);
    for (int i=0;i<=n;i++) readx(poly[i]);
    for (int i=1;i<=m;i++) readx(val[i]);
    
    FEV::FEV_Init(1,1,m,val);
    
    FEV::A[1].resize(m+2);
    if (n>=m) PCAL::PolyDiv(poly,FEV::P[1],FEV::A[1],n,m);
    else FEV::A[1]=poly;
    
    FEV::FastEva(1,1,m);
    for (int i=1;i<=m;i++) printf("%lld%c",FEV::ans[i]," \n"[i==m]);
}
*/

namespace FIP // fast interpolation
{
    
};

int main()
{
    
    
    
    
    
    
}