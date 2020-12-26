#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
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
	int n;
	double val,avg;
	
	readx(n); avg=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%lf", &val);
		avg+=1.0/val;
	}
	avg/=(double)n;
	avg=1.0/avg;
	printf("%.2lf\n", avg);
	return 0;
}	
