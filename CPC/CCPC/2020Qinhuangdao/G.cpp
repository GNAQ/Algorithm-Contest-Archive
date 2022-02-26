#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
ll n,k;
ll qpow(ll a,ll b)
{
	ll res=1,atag=0,restag=0;
	for(;b;b>>=1)
	{
		if(b&1) 
		{
			res*=a;
			if(res>n)
			{
				res%=n;
				restag=1;
			}
			if(atag)
				restag=1;
		}
		a*=a;
		if(a>n)
		{
			a%=n;
			atag=1;
		}
	}
	if(restag) res+=n+2;
	return res;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	for(int o=1;o<=T;o++)
	{	
		cin>>n>>k;
		if(k==1)
		{
			cout<<"Case #"<<o<<": "<<n<<'\n';
			continue;
		}
		ll i,ans=0;
		for(i=2;qpow(i,k)-1<=n;i++)
		{
			ll pre=qpow(i-1,k),now=qpow(i,k)-1;
			now=now/(i-1)*(i-1);
			ans+=(now-pre)/(i-1)+1;
		}
		n=n/(i-1)*(i-1);
		ans+=(n-qpow(i-1,k))/(i-1)+1;
		cout<<"Case #"<<o<<": "<<ans<<'\n';
	}
}