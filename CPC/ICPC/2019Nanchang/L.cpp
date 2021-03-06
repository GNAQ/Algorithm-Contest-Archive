#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

int n,a[1010][1010];
int winb[1010],loseb[1010],mark[1010];

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
	readx(n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) readx(a[i][j]);
	
	// calc marks
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++) // i vs j
		{
			if (a[i][j]>a[j][i])
				mark[i]+=3;
			else if (a[j][i]>a[i][j])
				mark[j]+=3;
			else 
			{
				mark[i]++; mark[j]++;
			}
		}
	
	//calc balls
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
		{
			winb[i]+=a[i][j];
			loseb[i]+=a[j][i];
			winb[j]+=a[j][i];
			loseb[j]+=a[i][j];
		}
	
	// calc winners
	int max_mark = -21398492, max_num=0;
	for (int i=1;i<=n;i++) 
		max_mark=max(max_mark, mark[i]);
	for (int i=1;i<=n;i++) 
		if (max_mark == mark[i]) max_num++;
	if (max_num==1)
	{
		for (int i=1;i<=n;i++) if (max_mark == mark[i])
		{
			printf("%d\n",i);
			return 0;
		}
	}
	else
	{
		int max_winb = -21398492;
		max_num = 0;
		for (int i=1;i<=n;i++) if (max_mark==mark[i])
		{
			winb[i]-=loseb[i];
			max_winb=max(max_winb, winb[i]);
		}
		for (int i=1;i<=n;i++) if (max_mark==mark[i])
			if (winb[i]==max_winb) max_num++;
		if (max_num==1)
		{
			for (int i=1;i<=n;i++) if (max_mark==mark[i])
				if (winb[i]==max_winb)
				{
					printf("%d\n",i);
					return 0;
				}
		}
		else
		{
			printf("play-offs\n");
			return 0;
		}
		
	}
	
}