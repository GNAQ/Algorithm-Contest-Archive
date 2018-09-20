#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

struct BNUM
{
	short s[210],len;
	
	BNUM() { memset(s,0,sizeof s); len=0; }
	//IO
	void readnum(ll qwq)
	{
		len=1; if (qwq) len--;
		while (qwq) { len++; s[200-len+1]=qwq%10; qwq/=10; }
	}
	void output()
	{
		if (!len) putchar('0');
		for (int i=200-len+1;i<=200;i++) putchar(s[i]+'0');
		putchar('\n');
	}
	//opes
	BNUM operator + (const BNUM& b)
	{
		BNUM c; c.len=max(len,b.len);
		for (int i=200;i>200-c.len;i--)
		{
			c.s[i]+=(s[i]+b.s[i]);
			if (c.s[i]>9) { c.s[i-1]++; c.s[i]-=10; }
		}
		if (c.s[200-c.len]) c.len++;
		return c;
	}
};

int n,m;
char ca[2003]={0},cb[2003]={0},mac[200];
BNUM dp[2003];

inline bool match(int i,int j) { return (mac[ca[i]]==cb[j]); }
int main()
{
	scanf("%d%d%s%s",&n,&m,ca+1,cb+1);
	mac['A']='T'; mac['T']='A'; mac['G']='C'; mac['C']='G'; dp[0].readnum(1);
	
	for (int i=1;i<=n;i++)
		for (int j=m;j;j--) if (match(i,j)) dp[j]=dp[j]+dp[j-1];
	dp[m].output();
	return 0;
}