#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

char ch1[1000010],ch2[1000010];
int fil[1000010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void KMP_Init(char* chs)
{
	int shs=0,len=strlen(chs+1);
	for (int i=2;i<=len;i++)
	{
		while (shs && chs[shs+1]!=chs[i]) shs=fil[shs];
		if (chs[shs+1]==chs[i]) shs++;
		fil[i]=shs;
	}
}

void KMP(char* chs,char* cht)
{
	int shs=0,lens=strlen(chs+1),lent=strlen(cht+1);
	for (int i=1;i<=lens;i++)
	{
		while (shs && cht[shs+1]!=chs[i]) shs=fil[shs];
		if (cht[shs+1]==chs[i]) shs++;
		if (shs==lent)
		{
			printf("%d\n",i-lent+1);
			shs=fil[shs];
		}
	}
}

int main()
{
	scanf("%s%s",ch1+1,ch2+1);
	KMP_Init(ch2);
	KMP(ch1,ch2);
	int tmp=strlen(ch2+1);
	for (int i=1;i<=tmp;i++) printf("%d%c",fil[i]," \n"[i==tmp]);
}
