#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
using namespace std;
typedef long long ll;

int n,li[100010],ri[100010],wi[100010];
int id[100010],rk[100010],rkli[100010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool cmp(int a,int b)
{
	if (ri[a]==ri[b]) return li[a]>li[b];
	return ri[a]>ri[b];
}

int main()
{
	readx(n);
	for (int i=1;i<=n;i++) 
	{
		readx(li[i]); readx(ri[i]);
	}
	
	for (int i=1;i<=n;i++) id[i]=i;
	sort(id+1,id+n+1, cmp);
	
	for (int i=1;i<=n;i++)
		if (ri[id[i]]==ri[id[i-1]])
			rk[id[i]]=rk[id[i-1]];
		else 
			rk[id[i]]=i;
	
	for (int i=1;i<=n;i++)
		rkli[rk[i]]=max(rkli[rk[i]], li[i]);
	
	// for (int i=1;i<=n;i++) printf("%d%c", rkli[i]," \n"[i==n]);
	
	wi[id[n]]=max(li[id[n]], rkli[rk[id[n]]]);
	for (int i=n-1;i>=1;i--)
		wi[id[i]]=max(max(wi[id[i+1]], li[id[i]]), rkli[rk[id[i]]]);
	
	// for (int i=1;i<=n;i++)
	// 	printf("%d%c", wi[i], " \n"[i==n]);
	
	ll ans=0;
	for (int i=1;i<=n;i++) ans+=wi[i];
	printf("%lld\n", ans);
	return 0;
}