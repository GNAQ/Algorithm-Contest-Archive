#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
typedef long long ll;
using namespace std;

int d[100010], dr[100010], n;
int pre[100010], ans[100010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

// -> 0
// ↑ 1
// <- 2
// ↓ 3
int lst[4];

void Go(int i)
{
	if (pre[i]==-1) return;
	ans[pre[i]]++;
	Go(pre[i]);
}

int main()
{
	readx(n); int tmp;
	for (int i=1;i<=n;i++)
	{
		readx(tmp); readx(d[i]);
		pre[i] = -1;
		ans[i]=1;
	}
	
	dr[1]=0; 
	for (int i=2;i<=n;i++)
	{
		dr[i]=dr[i-1]+d[i-1];
		dr[i]=(dr[i]+4)%4; 
	}
	
	lst[0]=lst[1]=lst[2]=lst[3]=-1;
	
	for (int i=1;i<=n;i++)
	{
		pre[i]=lst[ (dr[i]+2)%4 ];
		lst[ dr[i] ] = i;
	}
	
	for (int i=1;i<=n;i++)
		Go(i);
	
	for (int i=1;i<=n;i++)
		printf("%d%c", ans[i], " \n"[i==n]);
	
	return 0;
}