#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<cmath>
#include<queue>
#include<vector>
#define eps 1e-8
using namespace std;

double vars[1010]={0},equ[1010][1010]={0},sol[1010]={0};
int cache1,n;


inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline int Gauss_Elimination()
{
	int greater; double baze;
	
	for (int i=1;i<=n;i++)
	{
		if (fabs(equ[i][i])<eps) return -1;
		
		greater=i;
		for (int j=i+1;j<=n;j++) if (fabs(equ[j][i])>fabs(equ[greater][i])) greater=j;
		for (int j=i;j<=n;j++) swap(equ[greater][j],equ[i][j]);
		swap(vars[greater],vars[i]);
		
		for (int j=i+1;j<=n;j++)
		{
			baze=equ[j][i]/equ[i][i];
			for (int k=i;k<=n;k++) equ[j][k]-=equ[i][k]*baze;
			vars[j]-=vars[i]*baze;
		}
	}
	
	double sum;
	sol[n]=vars[n]/equ[n][n];
	for (int i=n-1;i;i--)
	{
		sum=0;
		for (int j=i+1;j<=n;j++) sum+=equ[i][j]*sol[j];
		vars[i]-=sum;
		sol[i]=vars[i]/equ[i][i]; 
	}
	return 1;
}

int main()
{
	readx(n);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		{
			readx(cache1);
			equ[i][j]=((double)cache1)*1.0000;
		}
		readx(cache1); vars[i]=((double)cache1)*1.0000;
	}
	
	if (Gauss_Elimination()==-1)
	{
		printf("No Solution\n");
		return 0;
	}
	for (int i=1;i<=n;i++) printf("%.2lf\n",sol[i]);
	return 0;
}
