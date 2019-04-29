#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<vector>
#include<queue>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

int n,lk[1000010],h,t;
char chr[1000010];

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int main()
{
	readx(n); scanf("%s",chr+1);
	h=t=n;
	for (int i=n;i;i--)
	{
		if (chr[i]>chr[i+1]) { lk[i]=h; h=i; }
		if (chr[i]<chr[i+1]) { lk[t]=i; t=i; }
	}
	
	for (int i=h;i;i=lk[i])
	{
		int j=i;
		while (chr[j-1]==chr[j]) j--;
		for (;j<=i;j++) printf("%d ",j);
	}
	
}