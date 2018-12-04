#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<queue>
#define ll long long
#define LCH tree[inx].ch[0]
#define RCH tree[inx].ch[1]
using namespace std;

struct Splay_tree
{
	int fa,ch[2],tag,val;
}tree[100010];


void readx(int& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Update(int inx)
{
	
}
void Pushdown(int inx)
{
	
}
void Rotate(int inx)
{
	int f=tree[inx].fa,g=tree[f].fa,flag=(tree[f].ch[1]==pos);
	
	tree[f].ch[flag]=tree[inx].ch[!flag]; tree[f].fa=inx;
	if (tree[inx].ch[!flag]) tree[tree[inx].ch[!flag]].fa=f;
	if (g) tree[g].ch[tree[g].ch[1]==f]=inx;
	tree[inx].ch[!flag]=f; tree[inx].fa=g;
	
	Update(f); Update(inx);
}
void Splay(int inx,int targ)
{
	
	
	
}


int main()
{
		
	
	
}
