#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
typedef long long ll;
using namespace std;

int n,m;
int a[100010];

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
	readx(n); readx(m);
	for (int i=1;i<=n;i++) readx(a[i]);
	
	
}

/* 
 * Solution Sketch
 * 首先考虑贪心
 * 第 w 位上是 1 的一定要搞在一起
 * 是 0 的无所谓
 * 
 */