#pragma G++ optimize("O3")
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

ll n, phi[1000010];
ll ans[1000010];
bool vis[1000010];
int pcnt=0, pnum[1000010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void PhiShake(int rng)
{
	phi[1]=1;
	for (int i=2;i<=rng;i++) phi[i]=i-1;
	
	for (int i=2;i<=rng;i++)
	{
		if (!vis[i]) pnum[++pcnt]=i;
		for (int j=1;j<=pcnt && i*pnum[j]<=rng;j++)
		{
			vis[i*pnum[j]]=1;
			if (!(i%pnum[j]))
			{
				phi[i*pnum[j]]=phi[i]*pnum[j];
				break;
			}
			else phi[i*pnum[j]]=phi[i]*(pnum[j]-1);
		}
	}
	for (int i=2;i<=rng;i++) phi[i]=phi[i]*i/2LL;
}

int main()
{
	PhiShake(1000000);
	
	for (int i=1;i<=1000000;i++)
		for (int j=i;j<=1000000;j+=i)
			ans[j]+=phi[i];
	
	int T; readx(T);
	while (T--)
	{
		readx(n);
		printf("%lld\n", n*ans[n]);
	}
	
	return 0;
}