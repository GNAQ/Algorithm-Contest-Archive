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

int n,ai[100010];


template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Clear()
{
	for (int i=1;i<=n;i++) ai[i]=0;
}

int main()
{
	int T; readx(T); 
	while (T--)
	{
		readx(n);
		for (int i=2;i<=n;i++) readx(ai[i]);
		
		for (int i=2;i<=n;i++) ai[i]+=ai[i-1];
		
		int l=0,r=n;
		ll ans=0,sum_len=0;
		printf("0 ");
		for (int k=2;k<=n;k++)
		{
			if (k%2)
			{
				r--;
				ans+=sum_len;
			}
			else
			{
				l++;
				ans+=sum_len;
				ans+=ai[r]-ai[l];
				sum_len+=ai[r]-ai[l];
			}
			printf("%lld%c",ans," \n"[k==n]);
		}
		
		Clear();
	}
	
	
}