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

int n,ai[1010];

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
		readx(n); int ans = 2*1e9;
		for (int i=1;i<=n;i++) readx(ai[i]);
		
		bool flag=1;
		int l=1,r=n;
		while (!ai[l]) l++;
		while (!ai[r]) r--;
		
		for (int i=l;i<=r;i++) flag=flag&ai[i];
		
		if (flag) 
		{
			printf("0\n");
			continue;
		}
		for (int i=1;i<=n;i++) if (ai[i])
		{
			int tmp=0;
			for (int j=l;j<i;j++) 
				if (!ai[j]) tmp++;
			for (int j=r;j>i;j--)
				if (!ai[j]) tmp++;
			
			ans=min(ans,tmp);
		}
		printf("%d\n", ans);
		
		memset(ai,0,sizeof ai);
	}
	
	return 0;
}