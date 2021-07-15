#include<bits/stdc++.h>
#define ll long long
using namespace std;

typedef unsigned long long ull;

const ull bas=233;
const ll mod=1e9+7;

ull qpow(ull a,ull b)
{
	ull res=1;
	for(;b;b>>=1)
	{
		if(b&1) res*=a;
		a*=a;
	}
	return res;
}
ull has[1000010],sec[1000010];
long long Has[1000010];

int n;

bool check(int l,int p)
{
	ull now=has[p+l-1]-has[l-1];
	int i=l+p;
	for(;i+p-1<=n;i+=p)
	{
		if(has[i+p-1]-has[i-1]!=now*qpow(bas,p)) return 0;
		now=has[i+p-1]-has[i-1];
	}
	ull last=has[n]-has[i-1];
	ull beg=(has[l+n-i]-has[l-1])*qpow(bas,i-l);
	return last==beg;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>sec[i];
	}
	ull bass=1;
	for(int i=1;i<=n;i++)
	{
		has[i]=has[i-1]+sec[i]*bass;
		bass*=bas;
	}
	int p=1,ans=n,ansp=1,ansk=n-1;
	for(int k=n-2;k>=0;k--)
	{
		int now=k+1;
		if(sec[now]==sec[now+p]) 
		{
			if(ans>k+p) ans=k+p,ansp=p,ansk=k;
			continue;
		}
		
		while(!check(k+1,p)) p++;
		if(ans>k+p) ans=k+p,ansp=p,ansk=k;
	}
	cout<<ansk<<' '<<ansp<<'\n';
}