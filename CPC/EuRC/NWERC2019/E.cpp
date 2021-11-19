#include <bits/stdc++.h>
typedef long long ll;
using namespace std;



template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); if (ch=='.') ch=getchar(); }
	x*=k;
}



int main()
{
	int t[5], ta;
	double tmp;
	for (int i=1;i<=4;i++)
	{
		readx(t[i]);
	}
	readx(ta);
	
	sort(t+1, t+5);
	// most
	if ((t[2]+t[3]+t[4])<=ta*3)
	{
		puts("infinite");
		return 0;
	}
	if ((t[2]+t[3]+t[4])>ta*3 && (t[1]+t[2]+t[3])<=ta*3)
	{
		for (int ans = t[4]; ans>=t[1]; ans--)
		{
			if (ans+t[2]+t[3]<=ta*3)
			{
				printf("%d.%d%d\n", ans/100, ans/10%10, ans%10);
				return 0;
			}
		}
	}
	if ((t[1]+t[2]+t[3])>ta*3)
	{
		puts("impossible");
		return 0;
	}
	
}