#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, ai[1000010];
ll A[4000010], B[4000010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

const ll mod=998244353;
ll fastpow(ll an,ll p)
{
    ll ret=1;
    for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
    return ret;
}

namespace FFT
{
    const ll G=3;
    const ll iG=fastpow(3,mod-2);
    
    int rev[2000010],revf,revt;
    void BtFl(ll* y,int len)
    {
        if (len!=revf)
        {
            revt=-1; revf=len; ll tmp=1;
            while (tmp<len) { tmp<<=1; revt++; }
            for (int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|(i&1)<<revt;
        }
        for (int i=0;i<len;i++) if (i<rev[i]) swap(y[i],y[rev[i]]);
    }
    void NTT(ll* y,int len,int mode)
    {
        BtFl(y,len);
        for (int i=1;i<len;i<<=1)
        {
            const ll wn=fastpow((mode==1?G:iG),(mod-1)/(i<<1));
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
            const ll inv=fastpow(len,mod-2);
            for (int i=0;i<len;i++) y[i]=y[i]*inv%mod;
        }
    }
};

bool vis[2000100];

int main()
{
	readx(n);
	for (int i=1;i<=n;i++) readx(ai[i]);
	sort(ai+1, ai+n+1);
	int maxa = ai[n];
	
	for (int i=1;i<=n;i++) A[ai[i]]=1;
	for (int i=1;i<=n;i++) B[maxa-ai[i]]=1;
	int len = 1;
	while (len<=2*maxa) len<<=1;
	
	FFT::NTT(A, len, 1); FFT::NTT(B, len, 1);
	for (int i=0;i<len;i++) A[i]=A[i]*B[i]%mod;
	FFT::NTT(A, len, -1);
	
	for (int i=maxa;i<=maxa*2;i++) 
		if (A[i]) vis[i-maxa]=1;
	
	for (int i=n;i<=maxa+1;i++) if (!vis[i])
	{
		int flag = 0;
		for (int j=1;i*j<=maxa+1;j++)
			flag = flag | vis[i*j];
		if (!flag)
		{
			printf("%d\n", i);
			return 0;
		}
	}
	return 0;
}