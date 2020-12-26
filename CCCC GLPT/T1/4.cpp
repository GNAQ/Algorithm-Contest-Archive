#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
using namespace std;

char msg[510][510];
char model[15]="chi1 huo3 guo1";

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void gnaqread(char *p)
{
	char ch=0;
	while ((ch=getchar())!='\n')
	{
		*p=ch;
		p++;
	}
}

bool match(char *p)
{
	for (int i=0;i<=13;i++)
	{
		if ( (*(p+i)) != model[i]) 
			return false;
	}
	return true;
}

int main()
{
	int n=0;
	while (1)
	{
		n++;
		gnaqread(msg[n]+1);
		
		if (strlen(msg[n]+1)==1 && msg[n][1]=='.') break;
	}
	
	n--;
	printf("%d\n", n);
	
	int cnt=0,fst=-1;
	for (int i=1;i<=n;i++)
	{
		int len=strlen(msg[i]+1);
		for (int j=1;j<=len-13;j++)
		{
			if (match(msg[i]+j))
			{
				cnt++;
				if (fst==-1) fst=i;
				break;
			}
		}
	}
	if (cnt==0) printf("-_-#\n");
	else printf("%d %d\n", fst, cnt);
	return 0;
}	
