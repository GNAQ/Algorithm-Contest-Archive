// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#define ll long long
#define LCH ch[_pos][0]
#define RCH ch[_pos][1]
using namespace std;

const int LIMIT = 1000100;
int fa[LIMIT],ch[LIMIT][2],val[LIMIT],sum[LIMIT],siz[LIMIT];
int lmax[LIMIT],rmax[LIMIT],tmax[LIMIT];
bool stag[LIMIT],rev[LIMIT];

int tsiz,troo;
queue<int> memque;

int n,m,seq[LIMIT];

void readx(int& x)
{
    x=0; int k=1; char chr=0;
    while (chr<'0' || chr>'9') { chr=getchar(); if (chr=='-') k=-1; }
    while (chr>='0' && chr<='9') { x=x*10+chr-'0'; chr=getchar(); }
    x*=k;
}

void Update_Node(int _pos)
{
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
        int _val=val[_pos],CH; stag[_pos]=0; rev[_pos]=0;
        for (int i=0;i<=1;i++) if (CH=ch[_pos][i])
        {
            val[CH]=_val;
            sum[CH]=_val*siz[CH];
            stag[CH]=1;
            
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
int Get_Pos(int _pos,int _val)
{
    Pushdown_Node(_pos);
    if (_val==1+siz[LCH]) return _pos;
    if (_val>siz[LCH]) return Get_Pos(RCH,_val-siz[LCH]-1);
    return Get_Pos(LCH,_val);
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
int Split(int _pos,int len)
{
    int _l=Get_Pos(troo,_pos),_r=Get_Pos(troo,_pos+len+1);
    Splay(_l,0); Splay(_r,_l);
    
    return ch[_r][0];
}
int Build(int _l,int _r,int _fa)
{
    int mid=(_l+_r)>>1,_pos=memque.front(); memque.pop();
    if (_l==_r) 
    {
        tmax[_pos]=sum[_pos]=seq[_l];
        stag[_pos]=rev[_pos]=0;
        
        lmax[_pos]=rmax[_pos]=max(seq[_l],0);
        siz[_pos]=1;
    }
    
    if (_l<mid) LCH=Build(_l,mid-1,_pos);
    if (mid<_r) RCH=Build(mid+1,_r,_pos);
    
    val[_pos]=seq[mid]; fa[_pos]=_fa;
    Update_Node(_pos);
    return _pos;
}
void Insert(int _pos,int len)
{
    for (int i=1;i<=len;i++) readx(seq[i]);
    int _l=Get_Pos(troo,_pos+1),_r=Get_Pos(troo,_pos+2);
    Splay(_l,0); Splay(_r,_l);
    
    int tmp=Build(1,len,0);
    ch[_r][0]=tmp; fa[tmp]=_r;
    
    Update_Node(_r); Update_Node(_l);
}
void Delete(int _l,int _r)
{
    int _pos=Split(_l,_r),tmp=fa[_pos];
    ReCollect(_pos);
    ch[tmp][0]=0;
    Update_Node(tmp); Update_Node(fa[tmp]);
}
void Put_Rev(int _l,int _r)
{
    int _pos=Split(_l,_r);
    if (!stag[_pos])
    {
        swap(LCH,RCH); swap(lmax[_pos],rmax[_pos]);
        rev[_pos]^=1;
    }
    
    Update_Node(fa[_pos]); Update_Node(fa[fa[_pos]]);
}
void Put_Cov(int _l,int _r,int _val)
{
    int _pos=Split(_l,_r);
    stag[_pos]=1; val[_pos]=_val; sum[_pos]=_val*siz[_pos];
    if (_val>=0) lmax[_pos]=rmax[_pos]=tmax[_pos]=sum[_pos];
    else { lmax[_pos]=rmax[_pos]=0; tmax[_pos]=_val; }
    
    Update_Node(fa[_pos]); Update_Node(fa[fa[_pos]]);
}
int Ask_Max() { return tmax[troo]; }
int Ask_Sum(int _l,int _r)
{
    int _pos=Split(_l,_r);
    return sum[_pos];
}

void _Init()
{
    seq[1]=seq[n+2]=tmax[0]=-0x3f3f3f3f;
    for (int i=1;i<=n;i++) readx(seq[i+1]);
    for (int i=1;i<=1e6;i++) memque.push(i);
    troo=Build(1,n+2,0);
}

int main()
{
    readx(n); readx(m);
    _Init();
    
    char opts[20]; int lxin,rxin,value;
    for (int i=1;i<=m;i++)
    {
        scanf("%s",opts+1);
        if (opts[1]=='I')
        {
            readx(lxin); readx(rxin);
            Insert(lxin,rxin);
        }
        else if (opts[1]=='D')
        {
            readx(lxin); readx(rxin);
            Delete(lxin,rxin);
        }
        else if (opts[1]=='M' && opts[3]=='K')
        {
            readx(lxin); readx(rxin); readx(value);
            Put_Cov(lxin,rxin,value);
        }
        else if (opts[1]=='R')
        {
            readx(lxin); readx(rxin);
            Put_Rev(lxin,rxin);
        }
        else if (opts[1]=='G')
        {
            readx(lxin); readx(rxin);
            printf("%d\n",Ask_Sum(lxin,rxin));
        }
        else if (opts[1]=='M' && opts[3]=='X') printf("%d\n",Ask_Max());
    }
    return 0;
}
