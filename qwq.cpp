#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
typedef long long ll;
using namespace std;

int n,str[100010],m,A,B,C,D;
char str1[100010];

template<typename inp_typ>
void readx(inp_typ& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace SA
{
	int high[200010],rk[200010],sa[200010];
	int setx[200010],chr[200010],fst[200010],snd[200010];
	int bac[200010],tmp[200010];
	
	void New(int* str,int len)
	{
		memcpy(setx,str,sizeof(int)*(len+2));
		sort(setx+1,setx+len+1); int CST=unique(setx+1,setx+len+1)-(setx+1);
		for (int i=1;i<=len;i++)
			chr[i]=lower_bound(setx+1,setx+CST+1,str[i])-setx;
		
		for (int i=1;i<=len;i++) bac[chr[i]]++;
		for (int i=1;i<=len;i++) bac[i]+=bac[i-1];
		for (int i=1;i<=len;i++) rk[i]=bac[chr[i]-1]+1;
		
		for (int w=1;w<=len;w<<=1)
		{
			for (int i=1;i<=len;i++) fst[i]=rk[i];
			for (int i=1;i<=len;i++) snd[i]=(i+w>len) ? 0 : rk[i+w];
			
			memset(bac,0,sizeof(int)*(len+2));
			for (int i=1;i<=len;i++) bac[snd[i]]++;
			for (int i=1;i<=len;i++) bac[i]+=bac[i-1];
			for (int i=1;i<=len;i++) tmp[len-(--bac[snd[i]])]=i; //tmp[x] 排名为 x 的第二关键字是谁
			
			memset(bac,0,sizeof(int)*(len+2));
			for (int i=1;i<=len;i++) bac[fst[i]]++;
			for (int i=1;i<=len;i++) bac[i]+=bac[i-1];
			for (int j=1,i;j<=len;j++) { i=tmp[j]; sa[bac[fst[i]]--]=i; }
			
			bool uniq=1; int last=0;
			for (int j=1,i;j<=len;j++)
			{
				i=sa[j];
				if (!last) rk[i]=1;
				else if (fst[i]==fst[last] && snd[i]==snd[last]) { rk[i]=rk[last]; uniq=0; }
				else rk[i]=rk[last]+1;
				last=i;
			}
			if (uniq) break;
		}
		
		for (int i=1,k=0;i<=len;i++)
		{
			if (rk[i]==1) k=0; 
			else
			{
				if (k>0) k--;
				int j=sa[rk[i]-1];
				while (i+k<=len && j+k<=len && chr[i+k]==chr[j+k]) k++;
			}
			high[rk[i]]=k;
		}
	}
}

namespace SGT
{
	#define LCH (tree[inx].ch[0])
	#define RCH (tree[inx].ch[1])
	#define lch (tree[newx].ch[0])
	#define rch (tree[newx].ch[1])
	
	struct Pre_Tree
	{
		int ch[2],val;
	}tree[100010*22];
	int tsiz,root[100010],_val,_pos,lx,rx;
	
	void Upd(int& newx,int inx)
	{
		newx=++tsiz; tree[newx].val=tree[inx].val+1;
		if (lx==rx) return;
		
		int mid=(lx+rx)>>1;
		lch=LCH; rch=RCH; 
		if (_pos<=mid) { rx=mid; Upd(rch,RCH); }
		else { lx=mid+1; Upd(lch,LCH); }
	}
	
	int Qry(int inx,int newx,int l,int r)
	{
		if (l>=lx && r<=rx) return tree[newx].val-tree[inx].val;
		
		int mid=(l+r)>>1,ret=0;
		if (lx<=mid) ret+=Qry(LCH,lch,l,mid);
		if (rx>mid) ret+=Qry(RCH,rch,mid+1,r);
		return ret;
	}
}

namespace ST
{
	int st[100010][22],lg2[100010];
	
	void New(int* seq,int len)
	{
		lg2[1]=0; lg2[2]=1;
		for (int i=3;i<=len;i++) lg2[i]=lg2[i>>1]+1;
		for (int i=1;i<=len;i++) st[i][0]=seq[i];
		for (int w=1;w<=20;w++) 
			for (int i=1;i<=len;i++) if (i+(1<<w)-1<=len)
				st[i][w]=min(st[i][w-1],st[i+(1<<(w-1))][w-1]);
	}
	
	int Qry(int l,int r)
	{
		if (r<l) return 0;
		int tmp=lg2[r-l+1];
		return min(st[l][tmp],st[r-(1<<tmp)+1][tmp]);
	}
}

bool Solve2(int lcp) // 迷路第二層
{
	int Lx,Rx;
	// 第一次二分 => Lx
	int l=1,r=SA::rk[C],mid;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (ST::Qry(mid+1,SA::rk[C])>=lcp) { Lx=mid; r=mid-1; }
		else l=mid+1;
	}
	l=SA::rk[C],r=n;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (ST::Qry(SA::rk[C]+1,mid)>=lcp) { Rx=mid; l=mid+1; }
		else r=mid-1;
	}
	
	SGT::lx=Lx; SGT::rx=Rx;
	int ret=SGT::Qry(SGT::root[A-1],SGT::root[])
	
	if (ret>0) return true;
	return false;
}

int Solve()
{
	int l=1,r=min(B-A+1,D-C+1),mid,ans=0;
	while (l<=r) // close range
	{
		int mid=(l+r)>>1;
		if (Solve2(mid)) 
		{
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	return ans;
}

int main()
{
	readx(n); readx(m);
	scanf("%s",str1+1); for (int i=1;i<=n;i++) str[i]=str1[i];
	SA::New(str,n); ST::New(SA::high,n);
	
	for (int i=1;i<=n;i++)
	{
		using namespace SGT;
		_pos=SA::rk[i]; lx=1; rx=n;
		Upd(root[i],root[i-1]);
	}
	
	while (m--)
	{
		readx(A); readx(B); readx(C); readx(D);
		cout<<Solve()<<endl;
	}
	
	
}

/*
 * solution sketch
 * 首先二分答案.
 * 查询 LCP 考虑用 SA + ST O(1) 解决.
 * 
 * 找一下性质:
 * 对于某个子序列 [x,y] 来说, 如果与 [c,d] 有 LCP
 * 那么考虑<big>所有</big>子序列 [x,y] 在 SA 上的 rank r(x,y) 和 r(c,d)
 * 然后显然因为有 LCP 那么排名都在一段定区间内.
 * 然后显然, 根据 height 的定义和 SA 的构造方法,
 * 会发现 LCP([x,y],[c,d]) 这个函数是单峰的
 * 
 * 那么套路就是(再次二分)先二分这个定区间的左右端点 [Lx,Rx]
 * 然后直接在主席树上问一下有没有 [a,b] 里面的点出现在 [Lx,Rx] 里。
 * 
 */