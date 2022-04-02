#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n;
ll ai[300030], pf[300030];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int main()
{
	readx(n);
	for (int i=1;i<=n;i++)
	{
		readx(ai[i]);
		pf[i] = pf[i-1] + ai[i];
	}
	ll ans = 0;
	priority_queue<ll, vector<ll>, less<ll>> que;
	que.push(0);
	for (int i=1;i<=n;i++)
	{
		que.push(-pf[i]);
		que.push(-pf[i]);
		ans += pf[i] + que.top();
		que.pop();
	}
	cout << ans << endl;
	return 0;
}

/*

Solution:

	
	

*/