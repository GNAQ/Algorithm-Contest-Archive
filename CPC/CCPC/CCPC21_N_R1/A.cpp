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



template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}


int main()
{
	int T; readx(T);
	while (T--)
	{
		ll n;
		readx(n);
		ll ans = (n- (n/2));
		ll r = n, l = n/3;
		
		while (l*3+1<=n) l++;
		
		if (l%2 && r%2)
		{
			ans+=(r-l+1+1)/2;
		}
		else if (l%2 && (r%2==0))
		{
			ans+=(r-l+1)/2;
		}
		else if ((l%2==0) && r%2)
		{
			ans+=(r-l+1)/2;
		}
		else
		{
			ans+=(r-l)/2;
		}
		cout << ans << endl;
	}
	
	
}