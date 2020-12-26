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

int n,m,sum=0,minx=0;
int a[100010];


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
	scanf("%d%d", &n, &m);
	for (int i=1;i<=n;i++)
	{
		readx(a[i]); sum+=a[i];
	}
	sort(a+1,a+n+1);
	
	for (int i=1;i<=n-m;i++) minx+=a[i];
	
	printf("%.6lf\n", (double)sum/2.0+((double)minx/(double)n));
}