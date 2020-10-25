#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
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

int gcd(int a, int b)
{
	if (!b) return a;
	return gcd(b,a%b);
}


int main()
{
	int T; readx(T);
	int cnt=0;
	while (T--)
	{
		int a, b; cnt++;
		readx(a); readx(b);
		if (a==1)
		{
			printf("Case #%d: 0/1\n", cnt);
			continue;
		}
		if (!b)
		{
			printf("Case #%d: 1/1\n", cnt);
			continue;
		}
		int x=a*(a-1)/2,y=(a+b)*(a+b-1)/2;
		printf("Case #%d: %d/%d\n", cnt, x/gcd(x,y), y/gcd(x,y));
	}
	
}