#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
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


void pushup(int x)
{
    int l=ch[x][0],r=ch[x][1];
    sum[x]=sum[l]+sum[r]+val[x];
    siz[x]=siz[l]+siz[r]+1;
    tmax[x]=max(tmax[l],max(tmax[r],rmax[l]+val[x]+lmax[r]));
    lmax[x]=max(lmax[l],sum[l]+val[x]+lmax[r]);
    rmax[x]=max(rmax[r],sum[r]+val[x]+rmax[l]);
}




void pushdown(int x)
{
    int l=ch[x][0],r=ch[x][1];
    if (tag[x]) 
    {
        rev[x]=tag[x]=0;
        if (l) tag[l]=1,val[l]=val[x],sum[l]=val[x]*siz[l];
        if (r) tag[r]=1,val[r]=val[x],sum[r]=val[x]*siz[r];
        if (val[x]>=0) 
        {
            if (l) lmax[l]=rmax[l]=tmax[l]=sum[l];
            if (r) lmax[r]=rmax[r]=tmax[r]=sum[r];
        }
        else
        {
            if (l) lmax[l]=rmax[l]=0,tmax[l]=val[x];
            if (r) lmax[r]=rmax[r]=0,tmax[r]=val[x];
        }
    }
    if (rev[x]) 
    {
        rev[x]=0; rev[l]^=1; rev[r]^=1;
        swap(lmax[l],rmax[l]); swap(lmax[r],rmax[r]);
        
        swap(ch[l][0],ch[l][1]); swap(ch[r][0],ch[r][1]);
    }
}

void rotate(int x,int &k)
{
    int y=fa[x],z=fa[y],l=(ch[y][1]==x),r=l^1;
    if (y==k) k=x; else ch[z][ch[z][1]==y]=x;
    fa[ch[x][r]]=y; fa[y]=x; fa[x]=z;
    ch[y][l]=ch[x][r]; ch[x][r]=y;
    pushup(y); pushup(x);
}

void splay(int x,int &k)
{
    while (x!=k)
    {
        int y=fa[x],z=fa[y];
        if (y!=k) 
        {
            if (ch[z][0]==y ^ ch[y][0]==x) rotate(x,k);
                else rotate(y,k);
        }
        rotate(x,k);
    }
}

int find(int x,int rk)
{
    pushdown(x);
    
    int l=ch[x][0],r=ch[x][1];
    if (siz[l]+1==rk) return x;
    if (siz[l]>=rk) return find(l,rk);
        else return find(r,rk-siz[l]-1);
}

void recycle(int x)
{
    int &l=ch[x][0],&r=ch[x][1];
    if (l) recycle(l);
    if (r) recycle(r);
    q.push(x);
    fa[x]=l=r=tag[x]=rev[x]=0;
}

int split(int k,int tot)
{
    int x=find(rt,k),y=find(rt,k+tot+1);
    splay(x,rt); splay(y,ch[x][1]);
    return ch[y][0];
}

void query(int k,int tot)
{
    int x=split(k,tot);
    printf("%d\n",sum[x]);
}
void modify(int k,int tot,int _val)
{
    int x=split(k,tot),y=fa[x];
    val[x]=_val; tag[x]=1; sum[x]=siz[x]*_val;
    if (_val>=0) lmax[x]=rmax[x]=tmax[x]=sum[x];
        else lmax[x]=rmax[x]=0,tmax[x]=_val;
    pushup(y); pushup(fa[y]);
    
    
}
void rever(int k,int tot)
{
    int x=split(k,tot),y=fa[x];
    if (!tag[x]) 
    {
        rev[x]^=1;
        swap(ch[x][0],ch[x][1]);
        swap(lmax[x],rmax[x]);
        pushup(y); pushup(fa[y]);
    }
    
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
void insert(int k,int tot)
{
    for (int i=1; i<=tot; i++) a[i]=read();
    for (int i=1; i<=tot; i++)
        if (!q.empty()) id[i]=q.front(),q.pop();
        else id[i]=++cnt;
    build(1,tot,0);
    int z=id[(1+tot)>>1];
    int x=find(rt,k+1),y=find(rt,k+2);
    
    splay(x,rt); splay(y,ch[x][1]);
    
    fa[z]=y; ch[y][0]=z;
    
    pushup(y); pushup(x);
    
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
            if (chs[2]=='X') printf("%d\n",tmax[rt]);
            else _val=read(),modify(k,tot,_val);
        }
        if (chs[0]=='R') rever(k,tot);
        if (chs[0]=='G') query(k,tot);
    }
    return 0;
}
