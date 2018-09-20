#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
#define LCH tree[_pos].ch[0]
#define RCH tree[_pos].ch[1]
using namespace std;

struct Splay_Tree
{
	int fa,ch[2],sum,val,siz,stag,rev;
}tree[100010];
int tsiz,troo;
queue<int> memque;

void readx(int& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Update_Rev(int _pos)
{
	if (!tree[_pos].rev) return;
	tree[LCH].rev^=1; tree[RCH].rev^=1;
	swap(LCH,RCH);
	tree[_pos].rev=0;
}

void Update_Node(int _pos)
{
	tree[_pos].siz=tree[LCH].siz+tree[RCH].siz; Update_Rev(_pos);
	if (!tree[_pos].stag) { tree[_pos].sum=tree[LCH].sum+tree[RCH].sum; return; }
	
	tree[LCH].val=tree[_pos].stag;
	tree[RCH].val=tree[_pos].stag;
	tree[LCH].sum=tree[_pos].stag*tree[LCH].siz;
	tree[RCH].sum=tree[_pos].stag*tree[RCH].siz;
	tree[LCH].stag=tree[_pos].stag;
	tree[RCH].stag=tree[_pos].stag;
	tree[_pos].sum=tree[LCH].sum+tree[RCH].sum;
	tree[_pos].stag=0;
}

void Rotate(int _pos)
{
	int f=tree[_pos].fa,g=tree[f].fa,flag=(_pos==tree[f].ch[1]);
	
	tree[f].ch[flag]=tree[_pos].ch[!flag]; tree[f].fa=_pos;
	if (tree[_pos].ch[!flag]) tree[tree[_pos].ch[!flag]].fa=f;
	tree[_pos].fa=g; tree[_pos].ch[!flag]=f;
	if (g) tree[g].ch[(f==tree[g].ch[1])]=_pos;
	
	Update_Node(f); Update_Node(_pos);
}

void Splay(int _pos,int _targ)
{
	for (;tree[_pos].fa!=_targ;Rotate(_pos))
	{
		int g=tree[tree[_pos].fa].fa;
		Update_Node(g); Update_Node(tree[_pos].fa); Update_Node(_pos);
		
		if (g!=_targ)
		{
			if ((tree[g].ch[1]==tree[_pos].fa) == (tree[tree[_pos].fa].ch[1]==_pos)) Rotate(tree[_pos].fa);
			else Rotate(_pos);
		}
	}
}

int Build(int _l,int _r,int _seq[],int _fa)
{
	int mid=(_l+_r)>>1,tnod=memque.front(); memque.pop();
	tree[tnod].fa=_fa; tree[tnod].siz=(_r-_l+1);
	tree[tnod].val=_seq[mid];
	if (_l==_r) return tsiz;
}

int Get_Pos(int _pos,int _val)
{
	
}


void Insert(int _pos,int _seq[],int len)
{
	int tmp=Build(1,len,_seq[],0);
	splay(_pos,0);
	splay(_pos+1,_pos);
	tree[_pos+1].ch[0]=tmp;
	tree[tmp].fa=_pos+1;
}

void Delete()
{
	
}



int main()
{
	
	
	
}
