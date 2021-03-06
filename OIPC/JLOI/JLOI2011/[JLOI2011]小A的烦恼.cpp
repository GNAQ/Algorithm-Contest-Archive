#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

int n,maxr=0;
char chs[110][110][210]={0};
char name[110][210]={0};
int rlen[110]={0},r[110]={0},irlen[110][110]={0};

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline int cnt(char ch[])
{
	int len=strlen(ch+1),ret=1;
	for (int i=1;i<=len;i++) if (ch[i]==',') ret++;
	return ret;
}

int main()
{
	readx(n);
	for (int i=1;i<=n;i++)
	{
		readx(r[i]); r[i]++;
		for (int j=1;j<=r[i];j++) scanf("%s",chs[i][j]+1);
	}
	
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=r[i];j++) rlen[i]=max(rlen[i],irlen[i][j]=cnt(chs[i][j]));
		for (int j=1;j<=r[i];j++)
		{
			int len=strlen(chs[i][j]+1);
			if (irlen[i][j]<rlen[i]) for (int k=len+1;k<=len+rlen[i]-irlen[i][j];k++) chs[i][j][k]=',';
		}
	}
	for (int i=1;i<=n;i++) maxr=max(r[i],maxr);
	for (int j=1;j<=maxr;j++)
	{
		for (int i=1;i<=n;i++)
		{
			if (j<=r[i])
			{
				int len=strlen(chs[i][j]+1);
				for (int k=1;k<=len;k++) printf("%c",chs[i][j][k]);
			}
			else for (int k=1;k<rlen[i];k++) printf(",");
			if (i!=n) printf(",");
		}
		printf("\n");
	}
	return 0;
}