#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
typedef long long ll;
using namespace std;

ll n, m;
ll p4[18];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

// [1]: swap(x, y)
// [2]: y += 4
// [3]: x += 4  y += 4
// [4]: y = x,  x = 9-y

void Solve(ll k, ll &ax, ll &ay, ll v)
{
	if (k==1)
	{
		if (v==1) { ax = ay = 1; }
		if (v==2) { ax = 1; ay = 2; }
		if (v==3) { ax = ay = 2; }
		if (v==4) { ax = 2; ay = 1; }
		return;
	}
	if (v <= p4[k-1]) // 1
	{
		Solve(k-1, ay, ax, v);
		return;
	}
	v -= p4[k-1];
	if (v <= p4[k-1]) // 2
	{
		Solve(k-1, ax, ay, v);
		ay += (1<<(k-1));
		return;
	}
	v -= p4[k-1];
	if (v <= p4[k-1])
	{
		Solve(k-1, ax, ay, v);
		ax += (1<<(k-1)); ay += (1<<(k-1));
		return;
	}
	v -= p4[k-1];
	{
		Solve(k-1, ax, ay, v);
		ll tx = ax, ty = ay;
		ax = (1<<k) + 1 - ty;
		ay = (1<<(k-1)) + 1 - tx;
	}
}

int main()
{
	p4[0]=1;
	for (int i=1;i<=17;i++) p4[i]=p4[i-1]*4;
	
	readx(n); readx(m);
	ll ax=0, ay=0;
	for (int i=1;i<=15;i++) if ((1<<i)==n)
	{
		Solve(i, ax, ay, m);
		break;
	}
	cout << ax << " " << ay << endl;
	return 0;
}