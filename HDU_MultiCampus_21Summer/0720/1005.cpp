#include<bits/stdc++.h>
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

ll S_fr2(ll x)
{
	return (x*(x+1))/2-1;
}

bool isp[10000010];
int pnum[8000010], ptr_p;
ll pcnt[10000010];

void Prime_Shake(ll lim)
{
	isp[0]=isp[1]=1;
	for (int i=2;i<=lim;i++)
	{
		if (!isp[i]) pnum[++ptr_p]=i;
		for (int j=1;j<=ptr_p && 1LL*pnum[j]*i<=lim;j++)
		{
			isp[pnum[j]*i]=1;
			if (!(i%pnum[j])) break;
		}
	}
}

int main()
{
	int T; readx(T); Prime_Shake(10000004);
	for (int i=3;i<=10000004;i++) pcnt[i]=pcnt[i-1]+i*(!isp[i]);
	
	while (T--)
	{
		ll n;
		readx(n); 
		ll ans = S_fr2(n) - 2 + pcnt[n];
		printf("%lld\n", ans);
	}
	
	
}