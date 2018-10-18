#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll n,seq[100010];
ll ap[100010],ptr=0;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll gcd(ll a,ll b)
{
	if (!b) return a;
	return gcd(b,a%b);
}

bool Judge(int lx,int rx)
{
	ll cnt_gcd=seq[lx];
	for (int i=lx+1;i<=rx;i++) cnt_gcd=gcd(cnt_gcd,seq[i]);
	for (int i=lx;i<=rx;i++) if (seq[i]==cnt_gcd) return true;
	return false;
}

int main()
{
	freopen("data.in","r",stdin);
	freopen("b1.out","w",stdout);
	
	readx(n);
	for (int i=1;i<=n;i++) readx(seq[i]);
	
	for (int ans=n;ans>=1;ans--)
	{
		ptr=0;
		for (int i=1;i<=n-ans+1;i++)
		{
			if (Judge(i,i+ans-1))
			{
				ptr++; ap[ptr]=i;
			}
		}
		if (ptr)
		{
			printf("%lld %d\n",ptr,ans-1);
			for (int i=1;i<=ptr;i++) printf("%d ",ap[i]);
			printf("\n"); //system("pause");
			return 0;
		}
	}
}