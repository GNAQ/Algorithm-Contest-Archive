#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<iterator>
typedef long long ll;
using namespace std;

const ll mod=998244353;
int n,m,k; char ch1[600010],ch2[600010];

int F[600010],G[600010],ans[600010],pre[600010],bac[600010];

template<typename inp_typ>
void readx(inp_typ& x)
{
    x=0; char ch=0;
    while (ch<'0' || ch>'9') ch=getchar();
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
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
    
    int revf,rev[600010],revt;
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

void Solve()
{
	readx(n); readx(m);
    scanf("%s%s",ch1,ch2);
	
	for (int i=0;i<n;i++)
	{
		// if(ch2[i]=='S') ch2[i]='R'; // R -> C
		if(ch1[i]=='S') ch1[i]='C'; 
		// else if(ch2[i]=='R') ch2[i]='P'; // P -> B
		else if(ch1[i]=='R') ch1[i]='B';
		// else if(ch2[i]=='P') ch2[i]='S'; // S -> A
		else if(ch1[i]=='P') ch1[i]='A';
		else cout<<"FUCK\n";
	}
	for (int i=0;i<m;i++)
	{
		if (ch2[i]=='S') ch2[i]='A';
		if (ch2[i]=='P') ch2[i]='B';
		if (ch2[i]=='R') ch2[i]='C';
	}
	for (int i=n;i<n+m;i++) ch1[i]='D';
	n+=m;
	
    std::reverse(ch2,ch2+m);
    
    for (int c='A';c<='D';c++)
    {
        ll len=1;
        while (len<=(n+m)) len<<=1;
        for (int i=0;i<=n+m+2;i++) { pre[i]=0; } ll fitem=0;
        for (int i=0;i<len;i++) F[i]=(ch1[i]==c);
        for (int i=0;i<len;i++) G[i]=(ch2[i]==c);
  
        pre[0]=F[0]*F[0];
        for (int i=1;i<n;i++) pre[i]=pre[i-1]+F[i]*F[i];
        for (int i=0;i<m;i++) fitem=fitem+G[i]*G[i];
        
        FFT::NTT(F,len,1); FFT::NTT(G,len,1);
        for (int i=0;i<len;i++) F[i]=1LL*F[i]*G[i]%mod;
        FFT::NTT(F,len,-1);
        
        for (int i=m-1;i<n;i++) 
            ans[i-(m-1)]+=fitem+pre[i]-2*F[i];
        for (int i=m;i<n;i++) ans[i-(m-1)]-=pre[i-m];
    }
    
    // for (int i=0;i<n-m+1;i++)
	// 	bac[ans[i]/2]++;
    // for (int i=0;i<=k;i++) printf("%d\n",bac[i]);
	
	int all_ans = 0;
	for (int i=0;i<n-m+1;i++)
		all_ans = max(all_ans, m - (ans[i]/2));
	printf("%d\n", all_ans);
}

int main()
{
	Solve();
}