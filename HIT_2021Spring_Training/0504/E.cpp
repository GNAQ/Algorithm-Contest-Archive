#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
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

void Solve()
{
	int n, m;
	readx(n); readx(m);
	if (n<m)
	{
		printf("1\n");
		return;
	}
	else
	{
		if (n%m==0)
		{
			printf("0\n");
			return;
		}
		else
		{
			printf("1\n");
			return;
		}
		
	}
	
}

void Clear()
{
	
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
	
	
}