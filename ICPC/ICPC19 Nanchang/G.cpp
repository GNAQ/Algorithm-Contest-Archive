#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<vector>
#include<set>
typedef long long ll;
using namespace std;

const ll mod = 998857459LL; //  = 2803*461*773
int n,m,ai[3010],pos[3010];
ll fac[3010];

vector< pair<ll,int> > sums;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Init_Fac()
{
	fac[0]=1;
	for (int i=1;i<=3000;i++) fac[i]=fac[i-1]*i%mod;
}

bool cmp(pair<int,int> a, pair<int,int> b)
{
	if (a.first==b.first) return a.second<b.second;
	return a.first<b.first;
}

int main()
{
	Init_Fac(); int lim=0;
	readx(n); readx(m); int tmp;
	for (int i=1;i<=n;i++)
	{
		readx(tmp);
		if (tmp>=2803) continue;
		lim++; pos[lim]=i; ai[lim]=fac[tmp];
	}
	
	for (int i=1;i<=lim;i++) // r
	{
		ll sum=0;
		for (int j=i;j<=lim;j++)
		{
			sum=(sum+ai[j])%mod;
			sums.push_back(make_pair(sum,pos[j]-pos[i]+1));
		}
	}
	
	sort(sums.begin(),sums.end(),cmp);
	int loc_min=sums[sums.size()-1].second,size=sums.size();
	for (int i=size-1;i;i--)
	{
		if (sums[i].second<loc_min)
			loc_min=sums[i].second;
		else sums[i].second=loc_min;
	}
	
	while (m--)
	{
		ll ki; readx(ki);
		auto lower = lower_bound(sums.begin(),sums.end(),make_pair(ki,0));
		if (lower==sums.end()) printf("-1\n");
		else printf("%d\n",(*lower).second);
	}
	
}