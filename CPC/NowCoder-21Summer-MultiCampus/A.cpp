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
		ll n, k;
		readx(n); readx(k);
		if (n > k+1)
		{
			printf("No\n");
		}
		else
		{
			printf("Yes\n");
		}
	}
	
	
}