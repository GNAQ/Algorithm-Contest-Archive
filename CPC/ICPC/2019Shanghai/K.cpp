#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
typedef long long ll;
using namespace std;

int ans;
int n,m;
vector< pair<int,int> > ev;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool vis[18];
void Solve()
{
	int lim = (1<<n)-1;
	for (int i=0;i<=lim;i++)
	{
		int tmp=0;
		for (int j=0;j<n;j++)
			vis[j+1] = (((1<<j)&i) != 0);
		
		for (int j=0;j<m;j++)
			if (vis[ev[j].first]==vis[ev[j].second])
				tmp++;
		
		ans=min(ans,tmp);
	}
	return;
}

int main()
{
	int T; readx(T);
	for (int tt=1;tt<=T;tt++)
	{
		printf("Case #%d: ", tt); 
		
		ans=2*1e9;
		ev.clear();
		readx(n); readx(m); int u,v;
		
		for (int i=1;i<=m;i++) 
		{
			readx(u); readx(v);
			ev.push_back(make_pair(u,v));
		}
		
		Solve();
		printf("%d\n", m-ans);
	}
	
}