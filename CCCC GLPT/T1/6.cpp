#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
using namespace std;

int G[10][10];
bool vis[20];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int win[25]={0,0,0,0,0,0,10000,36,720,360,80,252,108,72,54,180,72,180,119,36,306,1080,144,1800,3600};
printf("%d\n", win[ans]);


int main()
{
	memset(vis,0,sizeof vis);
	
	for (int i=1;i<=3;i++)
		for (int j=1;j<=3;j++)
		{
			readx(G[i][j]);
			vis[G[i][j]]=1;
		}
	
	int val,posx,posy;
	for (int i=1;i<=9;i++) if (!vis[i]) val=i;
	for (int i=1;i<=3;i++)
		for (int j=1;j<=3;j++)
			if (!G[i][j]) 
			{
				posx=i;
				posy=j;
			}
	
	G[posx][posy]=val;
	
	for (int i=1;i<=3;i++)
	{
		readx(posx); readx(posy);
		printf("%d\n", G[posx][posy]);
	}
	
	int ans=0;
	readx(val);
	switch(val)
	{
		case 1:
			ans=G[1][1]+G[1][2]+G[1][3];
			break;
		case 2:
			ans=G[2][1]+G[2][2]+G[2][3];
			break;
		case 3:
			ans=G[3][1]+G[3][2]+G[3][3];
			break;
		case 4:
			ans=G[1][1]+G[2][1]+G[3][1];
			break;
		case 5:
			ans=G[1][2]+G[2][2]+G[3][2];
			break;
		case 6:
			ans=G[1][3]+G[2][3]+G[3][3];
			break;
		case 7:
			ans=G[1][1]+G[2][2]+G[3][3];
			break;
		case 8:
			ans=G[1][3]+G[2][2]+G[3][1];
			break;
	}
	
	printf("%d\n", win[ans]);
	return 0;
}


/*
好恶心的大模拟。。。
有意思吗。。。。
*/ 
