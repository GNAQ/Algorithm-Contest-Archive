#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

int n,m,mapx[310][310],q,opt;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace FWT
{
	int fwt[110][310][310];
	
	void Upd(int w,int x,int y,int val)
	{
		for (int i=x;i<=n;i+=(i&(-i)))
			for (int j=y;j<=m;j+=(j&(-j)))
				fwt[w][i][j]+=val;
	}
	
	int Qry(int w,int x,int y)
	{
		int ret=0;
		for (int i=x;i>0;i-=(i&(-i)))
			for (int j=y;j>0;j-=(j&(-j)))
				ret+=fwt[w][i][j];
		return ret;
	}
};

int main()
{
	readx(n); readx(m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) readx(mapx[i][j]);
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) FWT::Upd(mapx[i][j],i,j,1);

	readx(q); register int x_1,x_2,y_1,y_2,c;
	while (q--)
	{
		readx(opt);
		if (opt==1)
		{
			readx(x_1); readx(y_1); readx(c);
			FWT::Upd(mapx[x_1][y_1],x_1,y_1,-1);
			FWT::Upd(mapx[x_1][y_1]=c,x_1,y_1,1);
		}
		else
		{
			readx(x_1); readx(x_2); readx(y_1); readx(y_2); readx(c);
			printf("%d\n",FWT::Qry(c,x_2,y_2)-FWT::Qry(c,x_1-1,y_2)-FWT::Qry(c,x_2,y_1-1)+FWT::Qry(c,x_1-1,y_1-1));
		}
	}
}
