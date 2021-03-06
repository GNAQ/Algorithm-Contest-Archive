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
	bool ok[5]={0,0,0,0,0}; int cnt=0;
	int a[5]={0,0,0,0,0},warn,les;
	for (int i=1;i<=4;i++) readx(a[i]);
	readx(warn); readx(les);
	
	a[0]=a[1]; 
	for (int i=2;i<=4;i++) 
		a[0]=max(a[0],a[i]);
	
	for (int i=1;i<=4;i++)
		if (a[i]<warn || a[0]-a[i]>les) 
		{
			cnt++;
			ok[i]=1;
		}
	
	if (cnt==0)
	{
		printf("Normal\n");
	}
	else if (cnt==1)
	{
		int id=0;
		for (int i=1;i<=4;i++) if (ok[i]) id=i;
		printf("Warning: please check #%d!\n", id);
	}
	else
	{
		printf("Warning: please check all the tires!\n");
	}
	return 0;
}	
