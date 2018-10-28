#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#define ll long long
#define LCH tree[inx].ch[0]
#define RCH tree[inx].ch[1]
#define lch (inx<<1)
#define rch (inx<<1|1)
using std::cout; using std::endl;
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
	
	//Debug
	void Print(int inx)
	{
		printf("node [%d]\n",inx);
		printf("| %d %d | %d\n",LCH,RCH,tree[inx].val);
		printf("siz = %d , w = %d\n",tree[inx].siz,tree[inx].w);
	}
	
	// Update a node.
	void Update(int inx)
	{
		tree[inx].siz=tree[LCH].siz+tree[RCH].siz+tree[inx].w;
	}
	void Clear(int inx) // Recycle a node.
	{
		tree[inx].fa=LCH=RCH=tree[inx].siz=tree[inx].val=tree[inx].w=0;
	}
	void Rotate(int inx)
	{
		int f=tree[inx].fa,g=tree[f].fa,flag=(tree[f].ch[1]==inx);
		
		tree[f].ch[flag]=tree[inx].ch[!flag]; tree[f].fa=inx;
		if (tree[inx].ch[!flag]) tree[tree[inx].ch[!flag]].fa=f;
		tree[inx].fa=g; tree[inx].ch[!flag]=f;
		if (g) tree[g].ch[(tree[g].ch[1]==f)]=inx;
		
		Update(f); Update(inx);
	}
	void Splay(int rot,int inx,int targ)
	{
		for (;tree[inx].fa!=targ;Rotate(inx))
		{
			if (debug)
			{
				cout<<"Splay!!"<<inx<<" "<<tree[inx].fa<<" "<<targ<<endl;
			}
			
			int g=tree[tree[inx].fa].fa;
			if (g==targ) continue;
			if ( (tree[g].ch[1]==tree[inx].fa) == (tree[tree[inx].fa].ch[1]==inx) ) Rotate(tree[inx].fa);
			else Rotate(inx);
		}
		if (targ==0) troo[rot]=inx;
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
	int GetSuc(int rot)
	{
		int inx=tree[troo[rot]].ch[1];
		while (LCH) inx=LCH;
		return inx;
	}
	
	int Getinx(int rot,int VAL) // find the variable val and rotate it to root;
	{
		int inx=troo[rot];
		while (inx)
		{
			if (debug)
			{
				cout<<"Splay inx ["<<inx<<"] |-> ["<<tree[inx].ch[tree[inx].val>VAL]<<"]"<<endl;
			}
			
			if (tree[inx].val==VAL) { Splay(rot,inx,0); return inx; }
			inx=tree[inx].ch[tree[inx].val>VAL];
		}
		return inx;
	}
	
	int Getrk(int rot,int VAL) // the number of variable that less than val
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
	
	void Ins(int rot,int VAL) // Add a variable val to tree rot
	{
	    if (debug)
	    {
	        cout<<"Splay Ins ["<<rot<<"] "<<VAL<<endl;
	    }
	    
		int inx=troo[rot];
		if (!inx)
		{
			troo[rot]=inx=++tsiz;
			tree[inx].siz=tree[inx].w=1;
			tree[inx].val=VAL;
			tree[inx].fa=0;
			return;
		}
		while (1)
		{
			if (VAL==tree[inx].val) { tree[inx].siz++; tree[inx].w++; break; }
			int flag=(tree[inx].val<VAL);
			if (!tree[inx].ch[flag])
			{
				tsiz++;
				tree[inx].ch[flag]=tsiz;
				tree[tsiz].fa=inx;
				tree[tsiz].val=VAL;
				tree[tsiz].siz=tree[tsiz].w=1;
				Update(inx); break;
			}
			else inx=tree[inx].ch[flag];
		}
		Splay(rot,inx,0);
	}
	
	void Del(int rot,int VAL) // Delete a variable val in tree rot
	{
		int inx=Getinx(rot,VAL);
		
		if (debug)
		{
			cout<<"Splay Del ["<<rot<<"] "<<VAL<<endl;
		}
		
		if (tree[inx].w>1) { tree[inx].w--; Update(inx); return; }
		if (!LCH && !RCH) { Clear(inx); troo[rot]=0; return; }
		if (!(LCH*RCH))
		{
			troo[rot]=LCH+RCH;
			tree[LCH+RCH].fa=0; return;
		}
		Splay(rot,GetSuc(rot),inx);
		troo[rot]=LCH; tree[LCH].fa=0;
		tree[LCH].ch[1]=RCH; tree[RCH].fa=LCH;
		Update(LCH); Clear(inx);
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
		BuildTree(lxx,tree[inx].mid,lch);
		BuildTree(tree[inx].mid+1,rxx,rch);
	}
	
	void Clear() { ans=lx=rx=0; }
	
	void Ins(int inx,int val,int pos) // val -> Insert Value 
	{
		if (debug)
		{
			cout<<"SGT Ins ["<<inx<<"] "<<endl;
		}
		
		Splay::Ins(inx,val); 
		if (tree[inx].l==tree[inx].r) return;
		if (pos<=tree[inx].mid) Ins(lch,val,pos);
		else Ins(rch,val,pos);
	}
	
	void Rank(int inx,int val) //  you need two param lx and rx
	{
		if (tree[inx].l>=lx && tree[inx].r<=rx) { ans+=Splay::Getrk(inx,val); return; }
		if (lx<=tree[inx].mid) Rank(lch,val);
		if (rx>tree[inx].mid) Rank(rch,val);
	}
	
	void Modify(int inx,int pos,int val)
	{
		if (debug)
		{
			cout<<"SGT Mod ["<<inx<<"] "<<endl;
		}
		
		Splay::Del(inx,seq[pos]); Splay::Ins(inx,val);
		if (tree[inx].l==tree[inx].r) return;
		if (pos<=tree[inx].mid) Modify(lch,pos,val);
		else Modify(rch,pos,val);
	}
	
	void Pre(int inx,int val) //  you need two param lx and rx
	{
	    if (debug)
	    {
	        cout<<"SGT Pre ["<<inx<<"] "<<endl;
	    }
	    
		if (tree[inx].l>=lx && tree[inx].r<=rx) { ans=max(ans,Splay::Pre(inx,val)); return; }
		if (lx<=tree[inx].mid) Pre(lch,val);
		if (rx>tree[inx].mid) Pre(rch,val);
	}
	void Suc(int inx,int val) //  you need two param lx and rx
	{
		if (tree[inx].l>=lx && tree[inx].r<=rx) { ans=min(ans,Splay::Suc(inx,val)); return; }
		if (lx<=tree[inx].mid) Suc(lch,val);
		if (rx>tree[inx].mid) Suc(rch,val);
	}
	
	int Kth(int val) //  you need two param lx and rx
	{
		int l=0,r=maxval+1,mid;
		while (l<r)
		{
			mid=(l+r)>>1; ans=0; Rank(1,mid);
			
			if (debug)
			{
				cout<<"Val = "<<mid<<" Rank = "<<ans<<endl;
			}
			
			if (ans<val) l=mid+1;
			else r=mid;
		}
		return l-1;
	}
	
};

void Disable_All_Debug_Output() { debug=0; }

int main()
{
	Disable_All_Debug_Output();
	freopen("dat.in","r",stdin);
	freopen("1.out","w",stdout);
	
	readx(n); readx(m); SGT::BuildTree(1,n,1);
	for (int i=1;i<=n;i++) 
	{
		readx(seq[i]);
		SGT::Ins(1,seq[i],i);
		maxval=max(maxval,seq[i]);
	}
	
	if (debug) cout<<"Done!"<<endl;
	
	int opt,val,pos;
	while (m--)
	{
		if (debug)
		{
			cout<<"-----------"<<endl;
		}
		
		readx(opt);
		switch(opt)
		{
			case 1:
				SGT::Clear();
				readx(SGT::lx); readx(SGT::rx); readx(val); 
				
				SGT::Rank(1,val);
				cout<<SGT::ans+1<<endl;
				
				break;
			case 2:
				SGT::Clear();
				readx(SGT::lx); readx(SGT::rx); readx(val);
				
				cout<<SGT::Kth(val)<<endl;
				
				break;
			case 3:
				readx(pos); readx(val);
				SGT::Modify(1,pos,val);
				seq[pos]=val;
				break;
			case 4:
				SGT::Clear(); SGT::ans=-2147483647;
				readx(SGT::lx); readx(SGT::rx); readx(val);
				
				SGT::Pre(1,val);
				cout<<SGT::ans<<endl;
				
				break;
			case 5:
				SGT::Clear(); SGT::ans=2147483647;
				readx(SGT::lx); readx(SGT::rx); readx(val);
				
				SGT::Suc(1,val);
				cout<<SGT::ans<<endl;
				
				break;
		}
	}
	return 0;
}