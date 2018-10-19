#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

int n,m,v,e;
int G[310][310];
int cl[2010][2],pr[2010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}
void Input()
{
	int fx,tx;
	readx(n); readx(m); readx(v); readx(e);
	for (int i=1;i<=n;i++) readx(cl[i][0]);
	for (int i=1;i<=n;i++) readx(cl[i][1]);
	for (int i=1;i<=n;i++) scanf("%lf",&pr[i]);
	for (int i=1;i<=)
}


void Folyd()
{
	
}

int main()
{
	
	
}