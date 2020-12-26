#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
using namespace std;

int s1[1010];
char s2[2010];
int n;

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

char G(int id)
{
	return s2[(id-1)*2+1];
}

int main()
{
	readx(n);
	for (int i=1;i<=n;i++) readx(s1[i]);
	gnaqread(s2+1);
	
	int a,b,h1=n,h2=n-1;
	char op;
	for (int i=1;i<n;i++)
	{
		a=s1[h1--];
		b=s1[h1--];
		op=G(h2); h2--;
		if (op=='+') a=b+a;
		if (op=='-') a=b-a;
		if (op=='*') a=b*a;
		if (op=='/')
		{
			if (!a) 
			{
				printf("ERROR: %d/0\n", b);
				return 0;
			}
			a=b/a;
		}
		s1[++h1]=a;
	}
	printf("%d\n",s1[h1]);
}
