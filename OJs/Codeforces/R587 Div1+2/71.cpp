#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, q;
int a[200010];
int dsu[200010];
int w[200010], l[200010], r[200010];
int ans[200010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int findfa(int e)
{
	if (dsu[e] != e) dsu[e] = findfa(dsu[e]);
	return dsu[e];
}

void merge(int a, int b)
{
	dsu[findfa(b)] = findfa(a);
}

int main()
{
	readx(n); readx(q);
	for (int i=1;i<=200000;i++)
	{ 
		l[i] = 1e9, r[i] = 0; 
		dsu[i] = i;
	}
	for (int i=1;i<=n;i++)
	{
		readx(a[i]);
		l[a[i]] = min(l[a[i]], i);
		r[a[i]] = max(r[a[i]], i);
		w[a[i]]++;
	}
	
	stack<int> stk;
	for (int i=1;i<=n;i++)
	{
		if (!stk.empty())
			merge(a[i], stk.top());
		if (l[a[i]] == i)
		{
			stk.push(a[i]);
		}
		if (r[a[i]] == i)
		{
			stk.pop();
		}
	}
	
	for (int i=1;i<=n;i++)
		ans[findfa(a[i])] = max(ans[findfa(a[i])], w[a[i]]);
	
	int totans = n;
	for (int i=1;i<=200000;i++) 
		totans -= ans[i];
	printf("%d\n", totans);
}