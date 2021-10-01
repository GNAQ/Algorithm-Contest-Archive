#pragma GCC optimize(3)
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;



const ll mod=998244353;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
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
    
    int revf,rev[300010],revt;
    template<typename inp_arr>
    void BtFl(inp_arr* y,int len)
    {
        if (len!=revf)
        {
            revf=len; revt=-1; int tmp=1;
            while (tmp<len) { tmp<<=1; revt++; }
            for (int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<revt);
        }
        for (int i=0;i<len;i++) if (i<rev[i]) swap(y[i],y[rev[i]]);
    }
    
    void NTT(int* y,int len,int mode)
    {
        BtFl(y,len);
        
        for (int i=1;i<len;i<<=1)
        {
            ll wn=fastpow((mode==1)?G:iG,(mod-1)/(i<<1));
            
            for (int j=0;j<len;j+=(i<<1))
            {
                ll w=1;
                for (int k=0;k<i;k++,w=wn*w%mod)
                {
                    ll t1=y[j+k],t2=1LL*y[i+j+k]*w%mod;
                    y[j+k]=(t1+t2)%mod;
                    y[i+j+k]=(t1-t2+mod)%mod;
                }
            }
        }
        if (mode==-1)
        {
            ll inv=fastpow(len,mod-2);
            for (int i=0;i<len;i++) y[i]=1LL*y[i]*inv%mod;
        }
    }
};

int F[300010], G[300010], lim;
string s;

void Solve()
{
	cin >> s; 
	lim = 0; 
	
	int cnt = 0; ll ans = 0;
	for (int i = 'a'; i <= 'z'; i++)
	{
		for (int j=0;j<s.size();j++)
		{
			if (s[j]!=i) cnt++;
			else
			{
				F[lim++] = cnt+1;
				cnt = 0;
			}
		}
		lim = 0; cnt = 0;
		for (int j=s.size()-1; j>=0; j--)
		{
			if (s[j]!=i) cnt++;
			else
			{
				G[lim++] = cnt+1;
				cnt = 0;
			}
		}
		lim--; cnt = 0;
		
		// for (int i=0;i<=lim;i++) 
		// 	cout << F[i] << " ";
		// puts("");
		// for (int i=0;i<=lim;i++) 
		// 	cout << G[i] << " ";
		// puts("");
		
		ll len = 1;
		while (len <= (lim*2+2)) len<<=1;
		FFT::NTT(F, len, 1); FFT::NTT(G, len, 1);
		for (int i=0;i<len;i++) F[i]=1LL*F[i]*G[i]%mod;
		FFT::NTT(F,len,-1);
		
		for (int i=0;i<=lim;i++)
		{
			ans += 1LL * (F[i]) * (lim-i+1) % mod * (lim-i+1) % mod;
			ans %= mod;
		}
		
		// for (int i=lim;i>=0;i--) cout << "Range " << (lim - i + 1) << " Count = " << F[i] << endl;
		
		for (int i=0;i<=len;i++) F[i]=G[i]=0;
		lim = 0;
	}
	
	cout << ans << endl;
}

void Clear()
{
	
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
	
	return 0;
}