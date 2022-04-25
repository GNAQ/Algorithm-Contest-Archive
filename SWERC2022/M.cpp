#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, m, r[100010], w[100010];

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
	scanf("%d%d", &n, &m);
	int mr = 0, mw = 0;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d", &r[i], &w[i]);
		mr = max(mr, r[i]);
		mw = max(mw, w[i]);
	}
	
	if (mw + mr > n)
	{
		puts("IMPOSSIBLE");
		return;
	}
	
	for (int i=1;i<=mr;i++)
	{
		putchar('R');
	}
	for (int i=1;i<=mw;i++)
	{
		putchar('W');
	}
	for (int i=1;i<=n-mw-mr;i++)
	{
		putchar('W');
	}
	putchar('\n');
}

void Clear()
{
	
}

int main()
{
	int t; scanf("%d", &t);
	for (int i=1;i<=t;i++)
	{
		Solve();
		Clear();
	}
	
}