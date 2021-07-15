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

char str[100010];
int n, m;
const ll mod = 1000000007LL;
vector<int> ss[100010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int id[100010];

int ds[100010];
int Find(int e_1)
{
	if (e_1!=ds[e_1]) ds[e_1]=Find(ds[e_1]);
	return ds[e_1];
}
void Merge(int e_1,int e_2)
{
	ds[Find(e_2)]=Find(e_1);
}


void Solve()
{
	readx(n); readx(m);
	scanf("%s", str+1);
	int u, v;
	for (int i=1;i<=n;i++) { ds[i]=i; id[i]=str[i]; }
	
	for (int i=1;i<=m;i++)
	{
		readx(u); readx(v);
		ss[u].push_back(v);
		ss[v].push_back(u);
	}
	for (int i=1;i<=n;i++)
	{
		ss[i].push_back(n+1-i);
	}
	
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<ss[i].size();j++) if (ss[i][j]!=i)
		{
			int i1=Find(i), i2=Find(ss[i][j]);
			if (id[i1]!='?' && id[i2]!='?' && id[i1]!=id[i2]) 
			{
				printf("0\n");
				return;
			}
			if (id[i2]!='?') id[i1]=id[i2];
			Merge(i, ss[i][j]);
		}
	}
	
	ll ans = 1;
	for (int i=1;i<=n;i++) 
	{
		if (id[Find(i)]=='?') 
		{
			ans=ans*26%mod;
			id[Find(i)]=0;
		}
	}
	cout<<ans<<endl;
	
}

void Clear()
{
	for (int i=1;i<=n;i++) ss[i].clear();
}


int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
	
}