#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

int vis[1000];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Init()
{
	vis[3]=1; vis[6]=1; vis[9]=1;
	for (int i=10;i<=99;i++)
	{
		int a = i%10, b = i/10;
		if (a%3==0 || b%3==0) vis[i]=1;
		else if (i%3==0) vis[i]=1;
	}
	for (int i=100;i<=999;i++)
	{
		int a = i%10, b = i/10%10, c = i/100;
		if (a%3==0 || b%3==0 || c%3==0)
		{
			vis[i]=1;
		}
		else if ((a+b)%3==0 || (b+c)%3==0)
		{
			vis[i]=1;
		}
		else if ((a+b+c)%3==0)
		{
			vis[i]=1;
		}
	}
	
	for (int i=1;i<=999;i++) vis[i]+=vis[i-1];
	
}

int main()
{
	Init();
	int T; readx(T);
	while (T--)
	{
		ll l, r; 
		readx(l); readx(r); l--;
		
		ll ans1, ans2;
		if (l>=1000)
		{
			ans1 = l-999+vis[999];
		}
		else ans1 = vis[l];
		
		if (r>=1000)
		{
			ans2 = r-999+vis[999];
		}
		else ans2 = vis[r];
		
		printf("%lld\n", ans2-ans1);
	}
	
	
	
}