#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<queue>
#define ll long long
#define LCH tree[_pos].ch[0]
#define RCH tree[_pos].ch[1]
using namespace std;

struct Splay_Tree
{
	int fa,ch[2],val;
	int sum,siz,lmax,rmax,tmax;
	int stag,rev;
}tree[100010];
int tsiz,troo;
queue<int> memque;

int n,m,seq[100010];

void readx(int& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int max5(int v1,int v2,int v3,int v4,int v5)
{
	if (v1>v2) v2=v1;
	if (v2>v3) v3=v2;
	if (v3>v4) v4=v3;
	if (v4>v5) v5=v4;
	return v5;
}

void Pushdown_STag(int _pos)//priority == 1
{
	tree[LCH].val=tree[_pos].stag;
	tree[RCH].val=tree[_pos].stag;
	tree[LCH].sum=tree[_pos].stag*tree[LCH].siz;
	tree[RCH].sum=tree[_pos].stag*tree[RCH].siz;
	tree[LCH].stag=tree[_pos].stag;
	tree[RCH].stag=tree[_pos].stag;
	tree[_pos].sum=tree[LCH].sum+tree[RCH].sum;
	tree[_pos].stag=0;
}
void Pushdown_Rev(int _pos)//priority == 1
{
	if (!tree[_pos].rev) return;
	tree[LCH].rev^=1; tree[RCH].rev^=1;
	swap(LCH,RCH);
	tree[_pos].rev=0;
}
void Update_Max(int _pos)//priority == 2
{
	tree[_pos].lmax=max(tree[LCH].lmax,tree[LCH].sum+tree[RCH].lmax);
	tree[_pos].rmax=max(tree[RCH].rmax,tree[RCH].sum+tree[LCH].rmax);
	tree[_pos].tmax=max5(tree[LCH].rmax+tree[RCH].lmax,tree[LCH].tmax,tree[RCH].tmax,
						 tree[LCH].sum+tree[RCH].lmax,tree[RCH].sum+tree[LCH].rmax);
}

void Update_Node(int _pos)
{
	tree[_pos].siz=tree[LCH].siz+tree[RCH].siz+1;//priority == 1
	tree[_pos].sum=tree[LCH].sum+tree[RCH].sum;//priority == ?
	
	if (tree[_pos].rev) Pushdown_Rev(_pos);
	if (tree[_pos].stag) Pushdown_STag(_pos);
	Update_Max(_pos);
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
	if (!_targ) troo=_pos;
}

void ClearNode(int _pos)
{
	tree[_pos].fa=tree[_pos].lmax=tree[_pos].rev=tree[_pos].rmax=0;
	tree[_pos].siz=tree[_pos].stag=tree[_pos].sum=tree[_pos].tmax=tree[_pos].val=0;
	LCH=RCH=0;
}

void ReCollect(int _pos)
{
	ClearNode(_pos);
	memque.push(_pos);
	if (LCH) ReCollect(LCH);
	if (RCH) ReCollect(RCH);
}

int Build(int _l,int _r,int _seq[],int _fa)
{
	int mid=(_l+_r)>>1,tnod=memque.front(); memque.pop();
	tree[tnod].fa=_fa;
	if (_l==_r)
	{
		tree[tnod].lmax=tree[tnod].rmax=tree[tnod].tmax=_seq[_l];
		tree[tnod].sum=tree[tnod].val=_seq[_l];
		tree[tnod].siz=1; return tnod;
	}
	tree[tnod].ch[0]=Build(_l,mid,_seq,tnod);
	tree[tnod].ch[1]=Build(mid+1,_r,_seq,tnod);
	Update_Node(tnod);
	return tnod;
}

int Get_Pos(int _pos,int _val)//树上第_val个位置
{
	if (_val==1+tree[LCH].val) return _pos;
	if (_val>tree[LCH].val) return Get_Pos(RCH,_val-tree[LCH].siz-1);
	return Get_Pos(LCH,_val);
}

void Insert(int _pos,int len,int _seq[])
{
	int tmp=Build(1,len,_seq,0); _pos++;
	int _l=Get_Pos(troo,_pos),_r=Get_Pos(troo,_pos+1);
	Splay(_l,0);
	Splay(_r,_l);
	tree[_r].ch[0]=tmp;
	tree[tmp].fa=_r;
	Update_Node(_r); Update_Node(_l);
}

void Delete(int _l,int _r)
{
	_l=Get_Pos(troo,_l); _r=Get_Pos(troo,_r);
	
	Splay(_l,0); Splay(_r,_l);
	tree[_r].ch[0]=0;
	ReCollect(tree[_r].ch[0]);
	Update_Node(_r); Update_Node(_l);
}

int Ask_Sum(int _l,int _r)
{
	_l=Get_Pos(troo,_l); _r=Get_Pos(troo,_r);
	Splay(_l,0); Splay(_r,_l);
	
	int ret;
	ret=tree[tree[_r].ch[0]].sum;
	return ret;
}

int Ask_Max()
{
	Update_Node(troo);
	int ret=max(max(tree[troo].lmax,tree[troo].rmax),tree[troo].tmax);
	return ret;
}

void Put_Rev(int _l,int _r)
{
	_l=Get_Pos(troo,_l); _r=Get_Pos(troo,_r);
	Splay(_l,0); Splay(_r,_l);
	tree[tree[_r].ch[0]].rev^=1;
}

void Put_Cov(int _l,int _r,int _val)
{
	_l=Get_Pos(troo,_l); _r=Get_Pos(troo,_r);
	Splay(_l,0); Splay(_r,_l);
	tree[tree[_r].ch[0]].stag=tree[tree[_r].ch[0]].val=_val;
	tree[tree[_r].ch[0]].sum=_val*tree[tree[_r].ch[0]].siz;
	Update_Node(tree[_r].ch[0]);
	Update_Node(_r); Update_Node(_l);
}

void _Init()
{
	troo=1;
	tree[1].ch[1]=2;
	tree[2].fa=1;
	tree[1].siz=2; tree[2].siz=1;
}

int main()
{
	readx(n); readx(m);
	for (int i=1;i<=n;i++) readx(seq[i]);
	
	_Init();
	for (int i=3;i<=100008;i++) memque.push(i);
	Insert(1,n,seq);
	
	char opts[20]; int lxin,rxin,value;
	for (int i=1;i<=m;i++)
	{
		scanf("%s",opts+1);
		if (opts[1]=='I')
		{
			readx(lxin); readx(rxin); for (int w=1;w<=rxin;w++) readx(seq[w]);
			Insert(lxin,rxin,seq);
		}
		else if (opts[1]=='D')
		{
			readx(lxin); readx(rxin);
			Delete(lxin,lxin+rxin+1);
		}
		else if (opts[1]=='M' && opts[3]=='K')
		{
			readx(lxin); readx(rxin); readx(value);
			Put_Cov(lxin,lxin+rxin+1,value);
		}
		else if (opts[1]=='R')
		{
			readx(lxin); readx(rxin);
			Put_Rev(lxin,lxin+rxin+1);
		}
		else if (opts[1]=='G')
		{
			readx(lxin); readx(rxin);
			printf("%d\n",Ask_Sum(lxin,lxin+rxin+1));
		}
		else if (opts[1]=='M' && opts[3]=='X') printf("%d\n",Ask_Max());
	}
	return 0;
}
