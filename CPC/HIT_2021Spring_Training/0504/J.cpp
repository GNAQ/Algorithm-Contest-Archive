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

int n, a[100010], id[100010];

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
	readx(n);
	for (int i=1;i<=n;i++)
	{
		readx(a[i]);
		id[a[i]]=i;
	}
	
	ll ans = 0;
	for (int i=1;i<=n;i++)
	{
		if (a[i]!=i)
		{
			ans++;
			int tmp = a[i], tmpid = id[i];
			swap(a[i], a[id[i]]);
			swap(id[i], id[tmp]);
		}
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
	
	
}