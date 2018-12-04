#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define ll long long
#define LCH tree[inx].ch[0]
#define RCH tree[inx].ch[1]
using std::min; using std::max;

int n,m,seq[1000010],maxval;
bool debug=1;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace Splay
{
	struct Splay_tree { int ch[2],fa,val,siz,w; }tree[4000010];
	int troo[4000010],tsiz;
	
	void Update(int inx)
	{
		tree[inx].siz=tree[inx].w;
		if (LCH) tree[inx].siz+=tree[LCH].siz;
		if (RCH) tree[inx].siz+=tree[RCH].siz;
	}
	void Clear(int inx)
	{
		tree[inx].fa=LCH=RCH=tree[inx].siz=tree[inx].val=tree[inx].w=0;
	}
	void Rotate(int inx)
	{
		int f=tree[inx].fa , g=tree[f].fa , flag=(tree[f].ch[1]==inx);
		
		tree[f].ch[flag]=tree[inx].ch[!flag];
		if (tree[inx].ch[!flag]) tree[tree[inx].ch[!flag]].fa=f;
		tree[inx].fa=g;
		if (g) tree[g].ch[tree[g].ch[1]==f]=inx;
		tree[f].fa=inx;
		tree[inx].ch[!flag]=f;
		
		Update(f); Update(inx);
	}
	void Splay(int rot,int inx,int targ)
	{
		for (;tree[inx].fa!=targ;)
		{
			int f=tree[inx].fa,g=tree[f].fa;
			if (g!=targ)
			{
				if ( (tree[g].ch[0]==f) == (tree[f].ch[0]==inx) ) Rotate(f);
				else Rotate(inx);
			}
			Rotate(inx);
		}
		if (!targ) troo[rot]=inx;
	}
	int Pre(int rot,int VAL)
	{
		int inx=troo[rot],ret=-2147483647;
		while (inx)
		{
			if (tree[inx].val<VAL) 
			{
				ret=max(ret,tree[inx].val);
				inx=RCH;
			}
			else inx=LCH;
		}
		return ret;
	}
	int Suc(int rot,int VAL)
	{
		int inx=troo[rot],ret=2147483647;
		while (inx)
		{
			if (tree[inx].val>VAL) 
			{
				ret=min(ret,tree[inx].val);
				inx=LCH;
			}
			else inx=RCH;
		}
		return ret;
	}
	int GetPre(int rot)
	{
		int inx=tree[troo[rot]].ch[0];
		while (RCH) inx=RCH;
		return inx;
	}
	int Getinx(int rot,int VAL)
	{
		int inx=troo[rot];
		while (inx)
		{
			if (tree[inx].val==VAL) { Splay(rot,inx,0); return inx; }
			inx=tree[inx].ch[tree[inx].val<VAL];
		}
		return inx;
	}
	int Getrk(int rot,int VAL)
	{
		int inx=troo[rot],ret=0;
		while (inx)
		{
			if (tree[inx].val==VAL) return tree[LCH].siz+ret;
			if (tree[inx].val<VAL)
			{
				ret+=tree[LCH].siz+tree[inx].w;
				inx=RCH;
			}
			else inx=LCH;
		}
		return ret;
	}
	void Ins(int rot,int VAL)
	{
		int inx=troo[rot];
		if (!inx)
		{
			troo[rot]=inx=++tsiz;
			tree[inx].siz=tree[inx].w=1;
			tree[inx].val=VAL;
			tree[inx].fa=0;
			return;
		}
		int f=0;
		while (1)
		{
			if (VAL==tree[inx].val)
			{
				tree[inx].siz++; tree[inx].w++;
				Update(f);
				break;
			}
			f=inx;
			inx=tree[inx].ch[VAL>tree[inx].val];
			if (!inx)
			{
				inx=++tsiz;
				tree[inx].val=VAL;
				tree[inx].siz=tree[tsiz].w=1;
				tree[f].ch[VAL>tree[f].val]=inx;
				tree[inx].fa=f;
				Update(f); break;
			}
		}
		Splay(rot,inx,0);
	}
	void Del(int rot,int VAL)
	{
		int inx=Getinx(rot,VAL);
		if (tree[inx].w>1) { tree[inx].w--; Update(inx); return; }
		if (!LCH && !RCH) { Clear(troo[rot]); troo[rot]=0; return; }
		if (!(LCH*RCH))
		{
			troo[rot]=LCH+RCH;
			tree[LCH+RCH].fa=0; return;
		}
		int now=GetPre(rot),old=troo[rot];
		Splay(rot,now,0);
		
		tree[troo[rot]].ch[1]=tree[old].ch[1];
		tree[tree[old].ch[1]].fa=troo[rot];
		Clear(old); Update(troo[rot]);
	}
};
namespace SGT
{
	struct Seg_Tree { int l,r,mid; }tree[200010];
	int ans,lx,rx;
	
	void BuildTree(int lxx,int rxx,int inx)
	{
		tree[inx].l=lxx; tree[inx].r=rxx;
		if (lxx==rxx) return;
		tree[inx].mid=(lxx+rxx)>>1;
		BuildTree(lxx,tree[inx].mid,inx<<1);
		BuildTree(tree[inx].mid+1,rxx,inx<<1|1);
	}
	void Clear() { ans=lx=rx=0; }
	void Ins(int inx,int val,int pos)
	{
		Splay::Ins(inx,val); 
		if (tree[inx].l==tree[inx].r) return;
		if (pos<=tree[inx].mid) Ins(inx<<1,val,pos);
		else Ins(inx<<1|1,val,pos);
	}
	void Rank(int inx,int val)
	{
		if (tree[inx].l>=lx && tree[inx].r<=rx)
		{
			ans+=Splay::Getrk(inx,val);
			return;
		}
		if (lx<=tree[inx].mid) Rank(inx<<1,val);
		if (rx>tree[inx].mid) Rank(inx<<1|1,val);
	}
	void Modify(int inx,int pos,int val)
	{
		Splay::Del(inx,seq[pos]); Splay::Ins(inx,val);
		if (tree[inx].l==tree[inx].r) return;
		if (pos<=tree[inx].mid) Modify(inx<<1,pos,val);
		else Modify(inx<<1|1,pos,val);
	}
	void Pre(int inx,int val)
	{
		if (tree[inx].l>=lx && tree[inx].r<=rx) { ans=max(ans,Splay::Pre(inx,val)); return; }
		if (lx<=tree[inx].mid) Pre(inx<<1,val);
		if (rx>tree[inx].mid) Pre(inx<<1|1,val);
	}
	void Suc(int inx,int val)
	{
		if (tree[inx].l>=lx && tree[inx].r<=rx) { ans=min(ans,Splay::Suc(inx,val)); return; }
		if (lx<=tree[inx].mid) Suc(inx<<1,val);
		if (rx>tree[inx].mid) Suc(inx<<1|1,val);
	}
	int Kth(int val)
	{
		int l=0,r=maxval+1,mid;
		while (l<r)
		{
			mid=(l+r)>>1; ans=0; Rank(1,mid);
			if (ans<val) l=mid+1;
			else r=mid;
		}
		return l-1;
	}
	
};

int main()
{
	readx(n); readx(m); SGT::BuildTree(1,n,1);
	for (int i=1;i<=n;i++) 
	{
		readx(seq[i]);
		SGT::Ins(1,seq[i],i);
		maxval=max(maxval,seq[i]);
	}
	
	int opt,val,pos;
	while (m--)
	{
		readx(opt);
		switch(opt)
		{
			case 1:
				SGT::Clear();
				readx(SGT::lx); readx(SGT::rx); readx(val); 
				SGT::Rank(1,val);
				printf("%d\n",SGT::ans+1);
				break;
			case 2:
				SGT::Clear();
				readx(SGT::lx); readx(SGT::rx); readx(val);
				printf("%d\n",SGT::Kth(val));
				break;
			case 3:
				readx(pos); readx(val); 
				SGT::Modify(1,pos,val);
				seq[pos]=val; maxval=max(maxval,val);
				break;
			case 4:
				SGT::Clear(); SGT::ans=-2147483647;
				readx(SGT::lx); readx(SGT::rx); readx(val);
				SGT::Pre(1,val);
				printf("%d\n",SGT::ans);
				break;
			case 5:
				SGT::Clear(); SGT::ans=2147483647;
				readx(SGT::lx); readx(SGT::rx); readx(val);
				SGT::Suc(1,val);
				printf("%d\n",SGT::ans);
				break;
		}
	}
	return 0;
}
