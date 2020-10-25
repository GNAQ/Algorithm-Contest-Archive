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
using namespace std;
typedef long long ll;

const ll mod=998244353;
int n;
ll k,xi[2010],yi[2010];

ll fastpow(ll an,ll p)
{
	ll ret=1;
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

ll Lagrange_Itp(int len,ll* x,ll* y,ll v)
{
	ll ret=0;
	for (int i=1;i<=len;i++)
	{
		ll s1=1,s2=1;
		for (int j=1;j<=len;j++) if (j!=i)
		{
			s1=s1*((v-x[j])%mod+mod)%mod;
			s2=s2*((x[i]-x[j])%mod+mod)%mod;
		}
		ret=(ret+(s1*y[i])%mod*fastpow(s2,mod-2)%mod)%mod;
	}
	return (ret%mod+mod)%mod;
}

int main()
{
	scanf("%d%lld",&n,&k);
	for (int i=1;i<=n;i++) scanf("%lld%lld",&xi[i],&yi[i]);
	printf("%lld\n",Lagrange_Itp(n,xi,yi,k));
	
}
