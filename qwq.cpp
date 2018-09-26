#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#define ll long long
#define LCH ch[_pos][0]
#define RCH ch[_pos][1]
using namespace std;

const int LIMIT = 4100010;
int fa[LIMIT],ch[LIMIT][2],val[LIMIT],sum[LIMIT],siz[LIMIT],lmax[LIMIT],rmax[LIMIT],tmax[LIMIT],stag[LIMIT],rev[LIMIT];

int tsiz,troo;
queue<int> memque;

int n,m,seq[LIMIT];

void readx(int& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Update_Node(int _pos)
{
	if (!_pos) return;
	siz[_pos]=siz[LCH]+siz[RCH]+1;
	sum[_pos]=sum[LCH]+sum[RCH]+val[_pos];
	lmax[_pos]=max(lmax[LCH],sum[LCH]+val[_pos]+lmax[RCH]);
	rmax[_pos]=max(rmax[RCH],sum[RCH]+val[_pos]+rmax[LCH]);
	tmax[_pos]=max(rmax[LCH]+val[_pos]+lmax[RCH],max(tmax[LCH],tmax[RCH]));
}
void Pushdown_Node(int _pos)
{
	if (stag[_pos])
	{
		int _val=stag[_pos],CH; stag[_pos]=0; rev[_pos]=0;
		for (int i=0;i<=1;i++) if (CH=ch[_pos][i])
		{
			val[CH]=_val;
			sum[CH]=_val*siz[CH];
			stag[CH]=_val;
			
			if (_val>=0) lmax[CH]=rmax[CH]=tmax[CH]=sum[CH];
			else 
			{
				rmax[CH]=lmax[CH]=0;
				tmax[CH]=_val;
			}
		}
	}
	else if (rev[_pos])
	{
		rev[LCH]^=1; rev[RCH]^=1; rev[_pos]=0;
		
		swap(ch[LCH][0],ch[LCH][1]);
		swap(ch[RCH][0],ch[RCH][1]);
		swap(lmax[LCH],rmax[LCH]);
		swap(lmax[RCH],rmax[RCH]);
	}
}

void Rotate(int _pos)
{
	int f=fa[_pos],g=fa[f],flag=(_pos==ch[f][1]),flag2=(ch[g][1]==f);
	
	ch[f][flag]=ch[_pos][!flag]; fa[f]=_pos;
	if (ch[_pos][!flag]) fa[ch[_pos][!flag]]=f;
	fa[_pos]=g; ch[_pos][!flag]=f;
	if (g) ch[g][flag2]=_pos;
	
	Update_Node(f); Update_Node(_pos);
}
void Splay(int _pos,int _targ)
{
	for (;fa[_pos]!=_targ;Rotate(_pos))
	{
		int g=fa[fa[_pos]];
		if (g!=_targ)
		{
			if ((ch[g][1]==fa[_pos]) == (ch[fa[_pos]][1]==_pos)) Rotate(fa[_pos]);
			else Rotate(_pos);
		}
	}
	if (!_targ) troo=_pos;
}

void ReCollect(int _pos)
{
	fa[_pos]=lmax[_pos]=rev[_pos]=rmax[_pos]=0;
	siz[_pos]=stag[_pos]=sum[_pos]=tmax[_pos]=val[_pos]=0;
	memque.push(_pos);
	if (LCH) ReCollect(LCH);
	if (RCH) ReCollect(RCH);
	LCH=RCH=0;
}

int Build(int _l,int _r,int _seq[],int _fa)
{
	int mid=(_l+_r)>>1,tnod=memque.front(); memque.pop();
	fa[tnod]=_fa; siz[tnod]=(_r-_l+1); val[tnod]=_seq[mid];
	
	if (_l==_r)
	{
		tmax[tnod]=_seq[_l];
		lmax[tnod]=rmax[tnod]=max(_seq[_l],0);
		sum[tnod]=_seq[_l]; return tnod;
	}
	if (mid>_l) ch[tnod][0]=Build(_l,mid-1,_seq,tnod);
	if (mid<_r) ch[tnod][1]=Build(mid+1,_r,_seq,tnod);
	
	Update_Node(tnod);
	return tnod;
}

int Get_Pos(int _pos,int _val)
{
	Pushdown_Node(_pos); Update_Node(_pos);
	if (_val==1+siz[LCH]) return _pos;
	if (_val>siz[LCH]) return Get_Pos(RCH,_val-siz[LCH]-1);
	return Get_Pos(LCH,_val);
}

void Insert(int _pos,int len,int _seq[])
{
	int _l=Get_Pos(troo,_pos),_r=Get_Pos(troo,_pos+1);
	Splay(_l,0); Splay(_r,_l);
	
	int tmp=Build(1,len,_seq,0);
	ch[_r][0]=tmp; fa[tmp]=_r;
	
	Update_Node(_r); Update_Node(_l);
}
void Delete(int _l,int _r)
{
	_l=Get_Pos(troo,_l); _r=Get_Pos(troo,_r);
	Splay(_l,0); Splay(_r,_l);
	ch[_r][0]=0;
	ReCollect(ch[_r][0]);
	Update_Node(_r); Update_Node(_l);
}
void Put_Rev(int _l,int _r)
{
	_l=Get_Pos(troo,_l); _r=Get_Pos(troo,_r);
	Splay(_l,0); Splay(_r,_l);
	
	int _pos=ch[_r][0];
	if (!stag[_pos])
	{
		swap(LCH,RCH); swap(lmax[_pos],rmax[_pos]);
		rev[_pos]^=1;
	}
	
	Update_Node(_r); Update_Node(_l);
}
void Put_Cov(int _l,int _r,int _val)
{
	_l=Get_Pos(troo,_l); _r=Get_Pos(troo,_r);
	Splay(_l,0); Splay(_r,_l);
	
	int _pos=ch[_r][0];
	stag[_pos]=val[_pos]=_val; sum[_pos]=_val*siz[_pos];
	if (_val>=0) lmax[_pos]=rmax[_pos]=tmax[_pos]=sum[_pos];
	else { lmax[_pos]=rmax[_pos]=0; tmax[_pos]=_val; }
	
	Update_Node(_r); Update_Node(_l);
}
int Ask_Sum(int _l,int _r)
{
	_l=Get_Pos(troo,_l); _r=Get_Pos(troo,_r);
	Splay(_l,0); Splay(_r,_l);
	return sum[ch[_r][0]];
}
int Ask_Max() { return tmax[troo]; }

void _Init()
{
	seq[1]=seq[n+2]=-2*1e9; tmax[0]=-2*1e9;
	for (int i=1;i<=4000008;i++) memque.push(i);
	troo=Build(1,n+2,seq,0);
}

int main()
{
//	freopen("4.in","r",stdin);
//	freopen("data.out","w",stdout);
	
	readx(n); readx(m);
	for (int i=2;i<=n+1;i++) readx(seq[i]);
	_Init();
	
	char opts[20]; int lxin,rxin,value;
	for (int i=1;i<=m;i++)
	{
		scanf("%s",opts+1);
		if (opts[1]=='I')
		{
			readx(lxin); readx(rxin); for (int w=1;w<=rxin;w++) readx(seq[w]);
			Insert(lxin+1,rxin,seq);
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
			readx(lxin); readx(rxin); if (!rxin) continue;
			printf("%d\n",Ask_Sum(lxin,lxin+rxin+1));
		}
		else if (opts[1]=='M' && opts[3]=='X') printf("%d\n",Ask_Max());
	}
	return 0;
}
