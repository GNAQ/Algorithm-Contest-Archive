#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

int n,ai[300010],ans[300010];
pair<int,int> Sx[300010][2];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool cmp(pair<int,int> a, pair<int,int> b)
{
	return a.first>b.first;
}

void Upd(int u)
{
	pair<int,int> tmp[4];
	for (int i=0;i<n;i++) if (u&(1<<i))
	{
		int v=u-(1<<i);
		tmp[0]=Sx[u][0]; tmp[1]=Sx[u][1];
		tmp[2]=Sx[v][0]; tmp[3]=Sx[v][1];
		sort(tmp,tmp+4,cmp);
		
		Sx[u][0]=Sx[u][1]=make_pair(0,0);
		Sx[u][0]=tmp[0];
		int id=1; 
		while (id<=3 && tmp[id].second==Sx[u][0].second) id++;
		if (id<=3) Sx[u][1]=tmp[id];
	}
}

int main()
{
	readx(n);
	for (int i=0;i<(1<<n);i++)
	{
		readx(ai[i]);
		Sx[i][0]=make_pair(ai[i],i); 
		Sx[i][1]=make_pair(0,0);
	}
	
	for (int i=0;i<(1<<n);i++)
	{
		Upd(i);
		ans[i]=Sx[i][0].first+Sx[i][1].first;
	}
	
	for (int i=2;i<(1<<n);i++)
		ans[i]=max(ans[i],ans[i-1]);
	
	for (int i=1;i<(1<<n);i++)
		printf("%d\n",ans[i]);
	return 0;
}