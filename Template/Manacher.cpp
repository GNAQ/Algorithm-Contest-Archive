#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<cmath>
#define ll long long
using namespace std;

char chs[22000050];
int mnc[22000050],ans=-1;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void manacher(int mnc[],char chs[],int len) // chs[0] should be '~'
{
	register int maxr=1,mid=1;
	for (int i=1;i<=len;i++)
	{
		if (i<maxr) mnc[i]=min(mnc[mid*2-i],maxr-i);
		else mnc[i]=1;
		while (chs[i+mnc[i]]==chs[i-mnc[i]]) mnc[i]++;
		if (maxr<i+mnc[i])
		{
			mid=i;
			maxr=i+mnc[i];
		}
	}
	for (int i=1;i<=len;i++) ans=max(ans,mnc[i]-1);
}

int main()
{
	chs[0]='~'; chs[1]='$'; char ch=0; int tmppos=2;
	while (ch<'a' || ch>'z') ch=getchar();
	while (ch>='a' && ch<='z')
	{
		chs[tmppos]=ch; 
		chs[tmppos+1]='$';
		tmppos+=2; ch=getchar();
	}
	
	manacher(mnc,chs,tmppos-1);
	
	printf("%d\n",ans);
}
