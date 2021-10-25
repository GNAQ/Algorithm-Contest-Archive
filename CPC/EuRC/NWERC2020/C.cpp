#include <bits/stdc++.h>
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
	ll n, k;
	ll d, s;
	readx(n); readx(k); readx(d); readx(s);
	double ans = (double)(n * d - k * s) / (n - k);
	
	if (ans>=0 && ans<=100)
		printf("%.10lf\n", ans);
	else
		puts("impossible");
}