#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<string>
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

void Solve()
{
	int a,b,c;
	readx(a); readx(b); readx(c);
	if (a==0 || b==0 || c==0 || a==180 || b==180 || c==180) 
	{
		puts("NO");
		return;
	}
	if (a+b+c!=180)
	{
		puts("NO");
		return;
	}
	puts("YES");
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
	}
	
	
}