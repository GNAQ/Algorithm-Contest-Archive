#include<cstring>
#include<string>
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#define ll long long
using namespace std;

char chs[1000010]={0},chr[1000010]={0};
int next[1000010]={0},lena,lenb;

inline void Calc_Next()
{
	int su=0;
	for (int i=2;i<=lenb;i++)
	{
		while (su && chr[su+1]!=chr[i]) su=next[su];
		if (chr[su+1]==chr[i]) su++;
		next[i]=su;
	}
}	

inline int KMP()
{
	int su=0;
	for (int i=1;i<=lena;i++)
	{
		while (su && chr[su+1]!=chs[i]) su=next[su];
		if (chr[su+1]==chs[i]) su++;
		if (su==lenb)
		{
			printf("%d\n",i-lenb+1);
			su=next[su];
		}
	}
}

int main()
{
	scanf("%s%s",chs+1,chr+1);
	lena=strlen(chs+1); lenb=strlen(chr+1);
	Calc_Next();
	KMP();
	for (int i=1;i<=lenb;i++) printf("%d ",next[i]); printf("\n");
	return 0;
}
