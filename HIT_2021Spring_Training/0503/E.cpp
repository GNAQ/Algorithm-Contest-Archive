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

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int n, a[10], b[10];
int ord[10], tar[10];
double ans[10];

int hp[10];
void DFS(int d, int prob)
{
	if (d==n+1)
	{
		for (int i=1;i<=n;i++) if (hp[i]>0)
			ans[i]+=1.0/(double)prob;
		return;
	}
	
	if (hp[ord[d]]<=0) 
	{
		DFS(d+1, prob);
		return;
	}
	
	int ret=0;
	for (int i=1;i<=n;i++) if (i!=ord[d])
		if (hp[i]>0) ret++;
	
	if (!ret) 
	{
		DFS(d+1, prob);
		return;
	}
	
	for (int i=1;i<=n;i++) if (i!=ord[d] && hp[i]>0)
	{
		hp[ord[d]]-=a[i];
		hp[i]-=a[ord[d]];
		DFS(d+1, prob*ret);
		hp[ord[d]]+=a[i];
		hp[i]+=a[ord[d]];
	}	
}

int main()
{
	readx(n); int lim = 1;
	for (int i=1;i<=n;i++)
	{
		readx(a[i]); readx(b[i]);
		ord[i]=i; 
		lim *= i;
	}
	
	for (int i=1;i<=lim;i++)
	{
		memcpy(hp, b, sizeof(b));
		DFS(1, lim);
		next_permutation(ord+1, ord+n+1);
	}
	
	for (int i=1;i<=n;i++) printf("%.12lf\n", ans[i]);
	
}