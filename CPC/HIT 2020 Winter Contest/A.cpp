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


int main()
{
	int T; readx(T);
	while (T--)
	{
		int x,y;
		readx(x); readx(y);
		if (x==1 || x==2)
		{
			printf("winter\n");
		}
		else if (x==7 || x==8)
		{
			printf("summer\n");
		}
		else
		{
			printf("daily\n");
		}
	}
	
}
