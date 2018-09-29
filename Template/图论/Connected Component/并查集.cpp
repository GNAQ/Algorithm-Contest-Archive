#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<string>
#include<queue>
using namespace std;

int fatherx[20010]={0};
int n,m,z,x,y;
int cache1,cache2,cache3;

void unionx(int e1,int e2)
{
	fatherx[e2]=e1;
	return;
}

int findx(int e1)
{
	if (fatherx[e1]!=e1) fatherx[e1]=findx(fatherx[e1]);
	return fatherx[e1];
}

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) fatherx[i]=i;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&z,&x,&y);
		if (z==1)
		{
			cache1=findx(x);
			cache2=findx(y);
			if (cache1!=cache2) unionx(cache1,cache2);
		}
		if (z==2)
		{
			if (findx(x)==findx(y)) printf("Y\n");
			else printf("N\n");
		}
	}
	return 0;
}
