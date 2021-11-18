#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, k, a[200010], b[200010];

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
	readx(n); readx(k);
	for (int i=1;i<=n;i++)
		readx(a[i]);
	for (int i=1;i<=n;i++)
		readx(b[i]);
	
	sort(a+1, a+n+1);
	sort(b+1, b+n+1);
	
	ll ans = 0;
	int pos = n;
	for (int i=1;i<=n;i++)
	{
		if (pos > 0 && b[pos] + a[i] >= k)
		{
			ans++;
			pos--;
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