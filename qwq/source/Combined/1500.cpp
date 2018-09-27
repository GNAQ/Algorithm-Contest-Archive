#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define LCH ch[_pos][0]
#define RCH ch[_pos][1]
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e6+17;
int n,m,rt,cnt;
int a[N],id[N],fa[N],ch[N][2];
int sum[N],siz[N],val[N],tmax[N],lmax[N],rmax[N];
bool tag[N],rev[N];

queue<int> q;
int read()
{
    int x=0,f=1; char chr=getchar();
    while (chr<'0' || chr>'9'){if (chr=='-') f=-1; chr=getchar();}
    while ('0'<=chr && chr<='9')x=(x<<1)+(x<<3)+(chr^48),chr=getchar();
    return x*f;
}


void pushup(int _pos)//my
{
	siz[_pos]=siz[LCH]+siz[RCH]+1;
	sum[_pos]=sum[LCH]+sum[RCH]+val[_pos];
	lmax[_pos]=max(lmax[LCH],sum[LCH]+val[_pos]+lmax[RCH]);
	rmax[_pos]=max(rmax[RCH],sum[RCH]+val[_pos]+rmax[LCH]);
	tmax[_pos]=max(rmax[LCH]+val[_pos]+lmax[RCH],max(tmax[LCH],tmax[RCH]));
}

void pushdown(int _pos)//OK
{
	if (tag[_pos])
	{
		int _val=val[_pos],CH; tag[_pos]=0; rev[_pos]=0;
		for (int i=0;i<=1;i++) if (CH=ch[_pos][i])
		{
			val[CH]=_val;
			sum[CH]=_val*siz[CH];
			tag[CH]=1;
			
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

void Rotate(int _pos)//OK
{
	int f=fa[_pos],g=fa[f],flag=(_pos==ch[f][1]),flag2=(ch[g][1]==f);
	
	ch[f][flag]=ch[_pos][!flag]; fa[f]=_pos;
	if (ch[_pos][!flag]) fa[ch[_pos][!flag]]=f;
	fa[_pos]=g; ch[_pos][!flag]=f;
	if (g) ch[g][flag2]=_pos;
	
	pushup(f); pushup(_pos);
}
void Splay(int _pos,int _targ)//OK
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
	if (!_targ) rt=_pos;
}

int find(int _pos,int _val)//OK
{
	pushdown(_pos);
	if (_val==1+siz[LCH]) return _pos;
	if (_val>siz[LCH]) return find(RCH,_val-siz[LCH]-1);
	return find(LCH,_val);
}

void recycle(int _pos)//OK
{
	fa[_pos]=lmax[_pos]=rev[_pos]=rmax[_pos]=0;
	siz[_pos]=tag[_pos]=sum[_pos]=tmax[_pos]=val[_pos]=0;
	q.push(_pos);
	if (LCH) recycle(LCH);
	if (RCH) recycle(RCH);
	LCH=RCH=0;
}

int split(int k,int tot)
{
    int x=find(rt,k),y=find(rt,k+tot+1);
    Splay(x,0); Splay(y,x);
    return ch[y][0];
}

void query(int k,int tot)
{
    int x=split(k,tot);
    printf("%d\n",sum[x]);
}

void modify(int _l,int _r,int _val)
{
	_r=_r+_l+1;
	_l=find(rt,_l); _r=find(rt,_r);
	Splay(_l,0); Splay(_r,_l);
	
	int _pos=ch[_r][0];
	tag[_pos]=1; val[_pos]=_val; sum[_pos]=_val*siz[_pos];
	if (_val>=0) lmax[_pos]=rmax[_pos]=tmax[_pos]=sum[_pos];
	else { lmax[_pos]=rmax[_pos]=0; tmax[_pos]=_val; }
	
	pushup(_r); pushup(_l);
}

void rever(int _l,int _r)
{
	_r=_l+_r+1;
	_l=find(rt,_l); _r=find(rt,_r);
	Splay(_l,0); Splay(_r,_l);
	
	int _pos=ch[_r][0];
	if (!tag[_pos])
	{
		swap(LCH,RCH); swap(lmax[_pos],rmax[_pos]);
		rev[_pos]^=1;
	}
	
	pushup(_r); pushup(_l);
}

void erase(int k,int tot)
{
    int x=split(k,tot),y=fa[x];
    recycle(x); ch[y][0]=0;
    pushup(y); pushup(fa[y]);
    
}

void build(int l,int r,int f)
{
    int mid=(l+r)>>1,now=id[mid],pre=id[f];
    if (l==r) 
    {
        tmax[now]=sum[now]=a[l];
        tag[now]=rev[now]=0;
        
        lmax[now]=rmax[now]=max(a[l],0);
        siz[now]=1;
    }
    if (l<mid) build(l,mid-1,mid);
    if (mid<r) build(mid+1,r,mid);
    val[now]=a[mid]; fa[now]=pre;
    pushup(now);
    
    ch[pre][mid>=f]=now;
    
}

int Ask_Max() { return tmax[rt]; }

void insert(int _pos,int len)
{
	for (int i=1; i<=len; i++) a[i]=read();
    for (int i=1; i<=len; i++)
        if (!q.empty()) id[i]=q.front(),q.pop();
        else id[i]=++cnt;
	
	int _l=find(rt,_pos+1),_r=find(rt,_pos+2);
	Splay(_l,0); Splay(_r,_l);
	
	int tmp=id[(1+len)>>1];
	build(1,len,0);
	
	ch[_r][0]=tmp; fa[tmp]=_r;
	
	pushup(_r); pushup(_l);
}

int main()
{
    n=read(),m=read();
    tmax[0]=a[1]=a[n+2]=-inf;
    for (int i=1; i<=n; i++) a[i+1]=read();
    for (int i=1; i<=n+2; i++) id[i]=i;
    build(1,n+2,0);
    rt=(n+3)>>1; cnt=n+2;
    int k,tot,_val; char chs[10];
    while (m--)
    {
        scanf("%s",chs);
        if (chs[0]!='M' || chs[2]!='X')  k=read(),tot=read();
        if (chs[0]=='I') insert(k,tot);
        if (chs[0]=='D') erase(k,tot);
        if (chs[0]=='M') 
        {
            if (chs[2]=='X') printf("%d\n",Ask_Max());
            else _val=read(),modify(k,tot,_val);
        }
        if (chs[0]=='R') rever(k,tot);
        if (chs[0]=='G') query(k,tot);
    }
    return 0;
}
