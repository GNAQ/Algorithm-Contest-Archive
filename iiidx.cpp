#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<string>
#include<queue>
#include<vector>
#include<map>
#include<set>
typedef long long ll;
using namespace std;



template<typename inp_typ>
void readx(inp_typ& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'0') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace SGT
{
	struct Seg_Tree
	{
		int l,r,mid,val;
	}tree[400010];
	
	
	void 
	
};


int main()
{
	
}