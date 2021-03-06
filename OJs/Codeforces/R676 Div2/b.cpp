#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<queue>
#include<map>
#include<set>
typedef long long ll;
using namespace std;

char g[210][210];
int n;

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
		for (int i=1;i<=n;i++)
			scanf(" %s", g[i]+1);
		
		int sim=0;
		if (g[2][1]==g[1][2]) sim++;
		if (g[n][n-1]==g[n-1][n]) sim++;
		// case 1
		if (sim==2)
		{
			if (g[2][1]==g[n-1][n])
			{
				printf("2\n2 1\n1 2\n");
				continue;
			}
			else 
			{
				cout<<0<<endl;
				continue;
			}
		}
		if (sim==1)
		{
			if (g[2][1]==g[1][2])
			{
				printf("1\n");
				if (g[n][n-1]==g[2][1])
					printf("%d %d\n", n, n-1);
				else
					printf("%d %d\n", n-1, n);
			}
			else
			{
				printf("1\n");
				if (g[2][1]==g[n][n-1])
					printf("2 1\n");
				else
					printf("1 2\n");
			}
			continue;
		}
		if (!sim)
		{
			printf("2\n");
			printf("1 2\n");
			if (g[n][n-1]==g[2][1])
				printf("%d %d\n", n, n-1);
			else
				printf("%d %d\n", n-1, n);
			continue;
		}
	}
	return 0;
}