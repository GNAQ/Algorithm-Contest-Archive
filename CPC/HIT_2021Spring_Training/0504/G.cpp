#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
typedef long long ll;
using namespace std;

ll n, ai[100010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Solve()
{
	readx(n); ll ans=0, maxv=-1;
	for (int i=1;i<=n;i++)
	{
		readx(ai[i]);
		maxv=max(maxv, ai[i]);
	}
	
	for (int i=1;i<=n;i++)
	{
		ans += maxv-ai[i];
	}
	
	// cout << ans  << " " << maxv << endl;
	
	if (ans<maxv)
	{
		printf("%lld\n", ans);
		return;
	}
	else
	{
		puts("-1");
		return;
	}
	
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
	
	
	
}