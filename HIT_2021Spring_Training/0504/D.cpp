#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
typedef long long ll;
using namespace std;

struct _Ask
{
    int l, r, id, ans;
}ask[200010];

int n, m, ai[200010], aa[200010], ab[200010];

int lg2[200010], st1[200010][19], st2[200010][19];

template<typename int_t>
void readx(int_t &x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

int buc[400010];

int blk[200010];

void Init()
{
    for (int i=1;i<=n;i++) aa[i]=ai[i];
    sort(aa+1, aa+n+1);
    
    ab[1]=1;
    for (int i=2;i<=n;i++)
    {
        ab[i]=ab[i-1]+1;
        if (aa[i]>aa[i-1]+1) ab[i]++;
        if (aa[i]==aa[i-1]) ab[i]--;
    }
    
    for (int i=1;i<=n;i++)
    {
        ai[i]=ab[lower_bound(aa+1, aa+n+1, ai[i])-aa];
    }
    
    // cout << "A:" << endl;
    // for (int i=1;i<=n;i++) printf("%d%c", ai[i], " \n"[i==n]);
    
    for (int i=1;i<=n;i++) st1[i][0]=st2[i][0]=ai[i];
    for (int w=1;w<=18;w++)
        for (int i=1;i<=n;i++) if (i+(1<<w)-1<=n)
        {
            st1[i][w]=min(st1[i][w-1],st1[i+(1<<(w-1))][w-1]);
            st2[i][w]=max(st2[i][w-1],st2[i+(1<<(w-1))][w-1]);
        }
}

pair<int, int> QRng(int l, int r)
{
    int tmp=lg2[r-l+1];
    return make_pair(min(st1[l][tmp],st1[r-(1<<tmp)+1][tmp]), 
                     max(st2[l][tmp],st2[r-(1<<tmp)+1][tmp]));
}

bool cmp1(const _Ask &a, const _Ask &b)
{
    if (blk[a.l]==blk[b.l])
    {
        if (blk[a.l]&1) return a.r<b.r;
        else return a.r>b.r;
    }
    return blk[a.l]<blk[b.l];
}

bool cmp2(const _Ask &a, const _Ask &b)
{
    return a.id < b.id;
}

void Add(int x, int &v)
{
    if (buc[x]==0) v++;
	buc[x]++;
}

void Sub(int x, int &v)
{
	buc[x]--;
    if (buc[x]==0) v--;
}

void Solve()
{
    readx(n); readx(m);
    for (int i=1;i<=n;i++)
    {
        readx(ai[i]);
    }
    Init();
    
    for (int i=1;i<=m;i++)
    {
        readx(ask[i].l); readx(ask[i].r);
        ask[i].id = i; ask[i].ans = 0;
    }
    
    int bsize = sqrt(n);
    for (int i=1;i<=n;i++) blk[i]=(i-1)/bsize+1;
    sort(ask+1, ask+m+1, cmp1);
    
    int ll=ask[1].l, rr=ask[1].l-1, tot=0;
    for (int i=1;i<=m;i++)
    {
        int al = ask[i].l, ar = ask[i].r;
        
        while (rr<ar)
        {
            rr++;
            Add(ai[rr], tot);
        }
        while (rr>ar)
        {
            Sub(ai[rr], tot);
            rr--;
        }
        while (ll>al)
        {
            ll--;
            Add(ai[ll], tot);
        }
        while (ll<al)
        {
            Sub(ai[ll], tot);
            ll++;
        }
        
        pair<int, int> tmp = QRng(al, ar);
        
        ask[i].ans = (tot==tmp.second-tmp.first+1);
    }
    
    sort(ask+1, ask+m+1, cmp2);
    const string anss[2]={"NO", "YES"};
    for (int i=1;i<=m;i++) 
    {
        cout << anss[ask[i].ans] << endl;
    }
}

void Clear()
{
    memset(buc,0,sizeof(buc));
}

int main()
{
    lg2[1]=0; lg2[2]=1;
    for (int i=3;i<=200000;i++) lg2[i]=lg2[i>>1]+1;
    int T; readx(T);
    while (T--)
    {
        Solve();
        Clear();
    }
    
}