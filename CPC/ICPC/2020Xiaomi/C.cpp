#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

char ch[1000010];

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
	scanf("%s", ch+1);
	int len = strlen(ch+1);
	
	int cont=0,ans=0;
	int j;
	for (int i=1;i<=len;i=j+1)  
	{
		j=i;
		if (ch[j]!='w') continue;
		
		while (ch[j+1]=='w' && j<len) j++;
		ans+=(j-i+1)*2-1;
	}
	
	printf("%d\n",ans);
}