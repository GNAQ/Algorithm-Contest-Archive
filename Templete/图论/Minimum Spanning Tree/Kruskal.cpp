#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

struct e
{
	int from,to,w;
	e operator = (const e x)
	{
		from=x.from;
		to=x.to;
		w=x.w;
		return *this;
	}
};
e edge[1000010]={0};
int fatherx[7010]={0},edgenum,nodenum,fx,tx,wx;
int mst=0,counter1=0;

void QuickSort(int l,int r)
{
	int mid=edge[(l+r)/2].w,i=l,j=r;
	e x;
	while (i<=j)
	{
		while (edge[i].w<mid) i++;
		while (edge[j].w>mid) j--;
		if (i<=j)
		{
			x=edge[i]; edge[i]=edge[j]; edge[j]=x;
			i++; j--;
		}
	}
	if (l<j) QuickSort(l,j);
	if (i<r) QuickSort(i,r);
	return;
}

int findx(int e1)
{
	if (fatherx[e1]!=e1) fatherx[e1]=findx(fatherx[e1]);
	return fatherx[e1];
}

int main()
{
	scanf("%d%d",&nodenum,&edgenum);
	for (int i=1;i<=edgenum;i++) scanf("%d%d%d",&edge[i].from,&edge[i].to,&edge[i].w);
	
	QuickSort(1,edgenum);
	for (int i=1;i<=nodenum;i++) fatherx[i]=i;
	
	for (int i=1;i<=edgenum;i++)
	{
		if (findx(edge[i].from)!=findx(edge[i].to))
		{
			fatherx[findx(edge[i].to)]=findx(edge[i].from);
			mst+=edge[i].w;
			counter1++;
			if (counter1==nodenum-1) break;
		}
	}
	
	printf("%d\n",mst);
	return 0;
}
