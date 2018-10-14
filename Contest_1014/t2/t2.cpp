#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<vector>
#define ll long long
using namespace std;

vector<int> edge[300010];
int n,k;
ll ans;
bool Sub_4=1;
int seq[300010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx)
{
	edge[fx].push_back(tx);
	edge[tx].push_back(fx);
}

bool Judge(int dep)
{
	for (int i=1;i<=dep;i++)
		for (int j=i+1;j<=dep;j++) 
			if (abs(seq[i]-seq[j])<=k) return false;
	return true;
}

void Get(int now,int fa,int dep)
{
	seq[dep]=now;
	if (!Judge(dep)) return;
	else ans++;
	
	for (auto v:edge[now]) if (v!=fa) Get(v,now,dep+1);
}

void DFS(int now,int fa)
{
	Get(now,fa,1);
	for (auto v:edge[now]) if (v!=fa) DFS(v,now);
}

int main()
{
	readx(n); readx(k); int fx,tx;
	for (int i=1;i<n;i++)
	{
		readx(fx); readx(tx);
		if (abs(fx-tx)>1) Sub_4=false;
		Is(fx,tx);
	}
	if (k==0) 
	{
		printf("%lld\n",1LL*(n*(n+1))/2);
		return 0;
	}
	else if (Sub_4) 
	{
		printf("%d\n",n);
		return 0;
	}
	else
	{
		DFS(1,0);
		printf("%lld\n",ans);
		return 0;
	}
}