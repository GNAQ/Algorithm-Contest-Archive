#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

int n,ai[200010];

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
		ai[i]-=i;
	}
	
	sort(ai+1,ai+n+1);
	
	long long ans=0;
	for (int i=1;i<=n;i++) ans+=abs(ai[i]-ai[n/2+1]);
	printf("%lld\n",ans);
	return 0;
}