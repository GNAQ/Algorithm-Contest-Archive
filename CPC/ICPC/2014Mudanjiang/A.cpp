#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;

int n, m;
int ai[10010],bi[10010];
ll ansl, ansr;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Clear(void)
{
	ansl=0; ansr=100;
	for (int i=1; i<=100; i++) 
		ai[i]=bi[i]=0;
	n=m=0;
}

void Solve(void)
{
	readx(n); readx(m); ll sa=0, sb=0;
	for (int i=1;i<n;i++) 
	{
		readx(ai[i]);
		sa+=ai[i];
	}
	for (int i=1;i<=m;i++)
	{
		readx(bi[i]);
		sb+=bi[i];
	}
	ansl=sb/m+(sb%m!=0);
	if (sb%m==0) ansl++;
	ansr=sa/(n-1);
	if (sa%(n-1)==0) ansr--;
	printf("%lld %lld\n", ansl, ansr);
	return;
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Clear();
		Solve();
	}
	
	return 0;
}