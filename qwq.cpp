#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
typedef long long ll;
using namespace std;

struct node
{
	int val,chr,to[26];
} t[1000003];
int at=0;

int n,ans;
char ch[1000003];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Ins(int u, int pos, int l)
{
	if (pos==l) 
	{
		t[u].val++;
		return;
	}
	int d = ch[pos+1] - 'a' + 1;
	if (!t[u].to[d])
	{
		t[u].to[d]=++at;
		t[at].chr=ch[pos+1];
	}
}

int main()
{
	readx(n);
	while (n--)
	{
		scanf("%s",ch+1);
		int l=strlen(ch+1);
		l++; ch[l+1]='{';
		
		// match
		
		// insert
		Ins(0, 0, l);
	}
	
	
}