#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<set>
typedef long long ll;
using namespace std;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

set<int> setx;
int n,m;
int arr[100010];

int main()
{
	int T; readx(T);
	while (T--)
	{
		readx(n); readx(m);
		for (int i=1;i<=n;i++) readx(arr[i]);
		
		for (int i=1;i<=n;i++)
		{
			setx.insert(arr[i]+m);
			setx.insert(arr[i]-m);
		}
		
		for (int i=1;i<=n;i++)
		{
			if (setx.find(arr[i]) != setx.end())
			{
				printf("Yes\n");
				goto round_end;
			}
		}
		
		printf("No\n");
		round_end:
		setx.clear();
	}
	
}
