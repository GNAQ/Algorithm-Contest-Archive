#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int a[100010], n, b[100010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int gcd(int a, int b)
{
	if(a<b) swap(a,b);
	if(!b) return a;
	else return gcd(b,a%b);
}

void Solve()
{
	readx(n);
	for (int i=1;i<=n;i++)
	{
		readx(a[i]);
		b[i] = abs(a[i] - a[i-1]);
	}
	if(n==1) 
	{
		if(a[1]==1) cout<<1<<'\n';
		else cout<<0<<'\n';
		return;
	}
	int g=b[2];
	for (int i=3;i<=n;i++)
		g=gcd(g,b[i]);
	if(g==0) 
	{
		if(a[1]==1) cout<<1<<'\n';
		else cout<<0<<'\n';
	}
	else if(g==1) cout<<-1<<'\n';
	else
	{
		int ans=(g-b[1]%g)%g;
		for(int i=2;i*i<=g;i++)
			if(g%i==0) 
			{
				ans=min(ans,(i-b[1]%i)%i);
				ans=min(ans,(g/i-b[1]%(g/i))%(g/i));
			}
		cout<<ans<<'\n';
	}
}

void Clear()
{
	
}

int main()
{
	int T; readx(T);
	for (int t = 1; t <= T; t++)
	{
		printf("Case %d: ", t);
		Solve();
		Clear();
	}
}