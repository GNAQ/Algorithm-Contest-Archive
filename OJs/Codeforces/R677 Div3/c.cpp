#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
typedef long long ll;
using namespace std;

ll n,a[300010];

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
	int T; readx(T);
	while (T--)
	{
		readx(n);
		for (int i=1;i<=n;i++) readx(a[i]);
		
		int aeq=a[1]; bool flag=1;
		for (int i=1;i<=n;i++)
			if (a[i]!=aeq) flag=0;
		if (flag)
		{
			printf("-1\n");
			continue;
		}
		
		ll val=a[1]; int ans=1;
		for (int i=1;i<=n;i++) 
			if (val<a[i])
			{
				val=a[i];
				ans=i;
			}
		
		if (a[n]==val)
		{
			for (int i=n;i>=1;i--)
				if (a[i]==val && a[i-1]!=val) 
				{
					ans=i;
					break;
				}
		}
		else 
		{
			for (int i=1;i<=n;i++)
				if (a[i]==val) ans=i;
		}
		printf("%d\n", ans);
	}
	
	return 0;
}