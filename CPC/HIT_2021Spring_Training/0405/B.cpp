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

ll n, phi[1000010], sphi[1000010];
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
	
	sphi[1]=1;
	for (int i=2;i<=rng;i++) sphi[i]=sphi[i-1]+phi[i];
}

ll gcd(ll a, ll b)
{
	if (!b) return a;
	return gcd(b, a%b);
}

void Solve()
{	
	if (n==1)
	{
		printf("0/1\n");
		return;
	}
	else
	{
		n--;
		ll dd = lower_bound(sphi+1, sphi+200001, n) - sphi;
		ll uu = 1;
		ll cnt = 1+sphi[dd-1];
		while (n!=cnt)
		{
			uu++;
			while (gcd(uu, dd)!=1) uu++;
			cnt++;
		}
		
		printf("%lld/%lld\n", uu, dd);
	}
}

int main()
{
	PhiShake(200100);
	
	n = 1;
	while (1)
	{
		readx(n);
		if (!n) return 0;
		Solve();
	}
	
	return 0;
}