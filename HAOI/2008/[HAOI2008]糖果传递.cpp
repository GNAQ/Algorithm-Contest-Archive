#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

ll n,seq[1000010],avg,sum[100010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int main()
{
	readx(n);
	for (int i=1;i<=n;i++) readx(seq[i]);
	for (int i=1;i<=n;i++) avg+=seq[i];
	avg/=n;
	
	for (int i=1;i<=n;i++) seq[i]-=avg;
	
	ll ans=0;
	for (int i=1;i<=n;i++) sum[i]=seq[i]+sum[i-1];
	sort(sum+1,sum+n+1);
	
	for (int i=1;i<=n;i++) printf("%lld%c",sum[i]," \n"[i==n]);
	
	for (int i=1;i<=n;i++) 
	{
		ans+=abs(sum[i]-sum[(n+1)>>1]);
		printf("%lld%c",ans," \n"[i==n]);
	}
	
	printf("%lld\n",ans);
	return 0;
}
