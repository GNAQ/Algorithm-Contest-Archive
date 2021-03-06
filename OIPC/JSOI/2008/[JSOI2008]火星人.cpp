// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
#include<cmath>
#include<cstdlib>
#define basex 27
#define ull unsigned long long
using namespace std;

struct splay_tree
{
    int siz,fa,ch[2];
    char val;
    ull hashx;
} tree[100010];
int troo,tsiz,val,len,onum,lp,rp,lm,rm;
ull ex_p[100010]={0};
char chs[100010]={0},cht=0,opt=0;

inline void updata(int pos)
{
    tree[pos].siz=0; tree[pos].hashx=0;
    if (tree[pos].ch[1])
    {
        tree[pos].hashx+=tree[tree[pos].ch[1]].hashx;
        tree[pos].siz+=tree[tree[pos].ch[1]].siz;
    }
    tree[pos].hashx+=tree[pos].val*ex_p[tree[pos].siz];
    tree[pos].siz++;
    if (tree[pos].ch[0])
    {
        tree[pos].hashx+=tree[tree[pos].ch[0]].hashx*ex_p[tree[pos].siz];
        tree[pos].siz+=tree[tree[pos].ch[0]].siz;
    }
}
inline void rotatex(int pos)
{
    int f=tree[pos].fa,g=tree[f].fa; bool flag=(tree[f].ch[1]==pos),flag2=(tree[g].ch[1]==f);
    
    tree[f].ch[flag]=tree[pos].ch[!flag]; tree[f].fa=pos;
    if (tree[pos].ch[!flag]) tree[tree[pos].ch[!flag]].fa=f;
    tree[pos].fa=g; tree[pos].ch[!flag]=f;
    if (g) tree[g].ch[flag2]=pos;
    
    updata(f); updata(pos);
}
inline void splay(int pos,int targ)
{
    for (;tree[pos].fa!=targ;rotatex(pos)) if (tree[tree[pos].fa].fa!=targ)
    {
        int g=tree[tree[pos].fa].fa;
        if ((tree[g].ch[1]==tree[pos].fa)==(tree[tree[pos].fa].ch[1]==pos)) rotatex(tree[pos].fa);
        else rotatex(pos);
    }
    if (!targ) troo=pos;
}

inline int splay_pos(int pos)
{
    if (tree[tree[pos].ch[0]].siz+1==val) { splay(pos,0); return pos; }
    else if (tree[tree[pos].ch[0]].siz>=val) return splay_pos(tree[pos].ch[0]);
    else
    {
        val-=tree[tree[pos].ch[0]].siz+1;
        return splay_pos(tree[pos].ch[1]);
    }
}
inline int splay_build(int lxx,int rxx,int f)
{
    int mid=(lxx+rxx)>>1;
    tree[mid].val=chs[mid]; tree[mid].fa=f;
    if (mid>lxx) tree[mid].ch[0]=splay_build(lxx,mid-1,mid);
    if (mid<rxx) tree[mid].ch[1]=splay_build(mid+1,rxx,mid);
    updata(mid); return mid;
}
inline void splay_ins(int pos)
{
    val=pos; int pre=splay_pos(troo);
    val=pos+1; int bih=splay_pos(troo);
    splay(pre,0); splay(bih,pre);
    tsiz++;
    tree[tsiz].fa=tree[troo].ch[1]; tree[tree[troo].ch[1]].ch[0]=tsiz;
    tree[tsiz].val=cht; updata(tsiz); updata(tree[tsiz].fa); updata(troo);
}

inline bool judgex(int pos)
{
    int lbound,rbound; ull lh=0,rh=0;
    val=lp+pos+1; lbound=splay_pos(troo);
    val=rp+pos+1; rbound=splay_pos(troo);
    splay(lm,0); splay(lbound,lm); lh=tree[tree[tree[troo].ch[1]].ch[0]].hashx;
    splay(rm,0); splay(rbound,rm); rh=tree[tree[tree[troo].ch[1]].ch[0]].hashx;
    if (rh==lh) return true;
    return false;
}

inline int solve()
{
    int lx=1,rx=len-rp+1,mid,ans=0;
    while (lx<=rx)
    {
        mid=(lx+rx)>>1;
        if (judgex(mid)) { ans=mid; lx=mid+1; }
        else rx=mid-1;
    }
    return ans;
}

int main()
{
    scanf("%s",chs+2);
    chs[0]=chs[1]='$'; chs[strlen(chs)]='$'; len=strlen(chs)-3;
    ex_p[0]=1; for (int i=1;i<=100006;i++) ex_p[i]=ex_p[i-1]*20020201;
    troo=splay_build(1,len+2,0); tsiz=len+2;
        
    scanf("%d",&onum);
    for (int i=1;i<=onum;i++)
    {
        opt=0;
        while (opt<'A' || opt>'Z') opt=getchar();
        if (opt=='Q')
        {
            scanf("%d%d",&lp,&rp); if (lp>rp) swap(lp,rp);
            val=lp; lm=splay_pos(troo);
            val=rp; rm=splay_pos(troo);
            printf("%d\n",solve());
        }
        else if (opt=='R')
        {
            scanf("%d %c",&lp,&cht);
            val=lp+1; splay_pos(troo);
            tree[troo].val=cht; updata(troo);
        }
        else
        {
            scanf("%d %c",&lp,&cht);
            splay_ins(lp+1); len++;
        }
    }
    return 0;
}
