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


long double C, ans, fr, wi[100010];
long double ans2;
int n;

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
	scanf("%d%Lf", &n, &C);
	
	for (int i=1;i<=n;i++) 
	{
		scanf("%Lf", &wi[i]);
		ans2+=wi[i];
	}
	sort(wi+1, wi+n+1);
	
	ans+=C;
	
	long double frac = 0.5, z = 0.25;
	for (int i=n-1;i>=1;i--)
	{
		// cerr << "!!" << ans << endl;
		ans += frac * wi[i];
		frac += z;
		z/=2;
	}
	
	printf("%.12Lf\n", min(ans, ans2));
	
}