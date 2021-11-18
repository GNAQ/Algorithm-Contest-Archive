#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MAXN=1e6+100;


template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

vector<int>fac[MAXN];
vector<int>pos[MAXN];
int prime[MAXN],tot;
int main()
{
	int n,max_dig=1e6;cin>>n;
	for(int i=2;i<=1e6;i++)
	{
		if(fac[i].size()!=0)
			continue;
		prime[++tot]=i;
		for(int j=1;j*i<=1e6;j++)
			fac[i*j].push_back(i);
	}
	for(int i=1;i<=n;i++)
	{
		int tmp;
		scanf("%d",&tmp);
		for(int j=0;j<(int)fac[tmp].size();j++)
			pos[fac[i][j]].push_back(i);
	}
	long long ans=0;
	for(int i=1;i<=tot;i++)
	{
		int x=prime[i],last=0;
		for(int j=0;j<(int)pos[x].size();j++)
		{ 
			long long dis=pos[x][j]-1-last;
			ans+=x*dis*(dis+1)/2;
			last=pos[x][j];
		}
		long long dis=n-last;
		ans+=x*dis*(dis+1)/2;
	}
	cout<<ans;
}