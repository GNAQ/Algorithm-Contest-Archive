#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;

struct Rob
{
	int l,r;
} rob[100010];
int ans,n;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool cmp(Rob a, Rob b)
{
	if (a.r == b.r) return a.l<b.l;
	return a.r<b.r; 
}

int main()
{
	readx(n); int xi,li;
	for (int i=1;i<=n;i++)
	{
		readx(xi); readx(li);
		rob[i].l=xi-li;
		rob[i].r=xi+li; 
	}
	sort(rob+1,rob+n+1,cmp);
	
	int nowr=-2*1e9; ans=0;
	for (int i=1;i<=n;i++)
	{
		if (rob[i].l>=nowr)
		{
			nowr=rob[i].r;
			ans++;
		}
	}
	
	printf("%d\n",ans);
	return 0;
}
