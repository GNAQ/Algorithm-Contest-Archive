#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<queue>
typedef long long ll;
using namespace std;

int n,ai[3010];
int cnt[3010];

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
	for (int i=1;i<=n;i++) 
		cnt[i]=0;
}

ll fac4(int x)
{
	return 1LL*x*(x-1)*(x-2)*(x-3);
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		readx(n); ll ans=0;
		for (int i=1;i<=n;i++) readx(ai[i]);
		
		// Only a[i]==a[k] && a[j]==a[l] && **a[i]!=a[j]**
		cnt[ai[n]]++;
		for (int k=n-1;k>=2;k--)
		{
			int tmp=0;
			for (int i=k-1;i>=1;i--)
			{
				if (ai[i]!=ai[k])
					tmp+=cnt[ai[i]];
				else
				{
					if (i==k-1) continue;
					ans+=tmp;
				}
			}
			
			// Push k to left
			cnt[ai[k]]++;
		}
		Clear();
		
		// count a[i]==a[j]==a[k]==a[l]
		for (int i=1;i<=n;i++) cnt[ai[i]]++;
		for (int i=1;i<=n;i++) if (cnt[i]>=4)
			ans+=fac4(cnt[i])/24;
		
		printf("%lld\n",ans);
		Clear();
	}
	return 0;
}