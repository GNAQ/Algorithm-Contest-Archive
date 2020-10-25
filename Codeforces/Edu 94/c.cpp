#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<queue>
typedef long long ll;
using namespace std;

char ch[100010];
int w[100010];
int x,len;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Clear()
{
	for (int i=1;i<=len;i++)
		ch[i]=w[i]=0;
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		scanf(" %s", ch+1);
		len=strlen(ch+1);
		scanf("%d", &x);
		
		for (int i=1;i<=len;i++)
			w[i]=1;
		for (int i=1;i<=len;i++)
			if (ch[i]=='0')
			{
				if (i-x>0) w[i-x]=0;
				if (i+x<=len) w[i+x]=0;
			}
		
		// Only need to check 1 'cause 0 is already satisfied.
		bool flag=0;
		for (int i=1;i<=len;i++)
			if (ch[i]=='1')
			{
				int cnt=0;
				if (i-x>0) cnt+=w[i-x];
				if (i+x<=len) cnt+=w[i+x];
				if (!cnt) flag=1;
			}
		
		if (!flag)
		{
			for (int i=1;i<=len;i++)
				printf("%d", w[i]);
			putchar('\n');
		}
		else printf("-1\n");
		
		Clear();
	}
	
	return 0;
}