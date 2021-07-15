#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<string>
typedef long long ll;
using namespace std;

int a[200];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int vis[100];

int main()
{
	for (int i=1;i<=14;i++)
	{
		readx(a[i]);
	}
	
	int ans = 10000;
	for (int i=1;i<=13;i++)
	{
		int ans1 = 0;
		memset(vis,0,sizeof(vis));
		for (int j=1;j<=14;j++)
		{
			if (a[j]>13) ans1++;
			else
			{
				if (!vis[a[j]])
				{
					vis[a[j]]=1;
				}
				else
				{
					if (vis[a[j]]==1 && a[j]==i)
					{
						vis[a[j]]++;
					}
					else ans1++;
				}
			}
			
		}
		ans=min(ans, ans1);
	}
	cout << ans << endl;
	return 0;
}