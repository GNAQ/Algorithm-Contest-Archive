#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<string>
using namespace std;
typedef long long ll;

const ll mod1=998244353, mod2=1000000007; // 双模 191 进制。 
int n,hi[300010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace H
{
	struct hash
	{
		ll a,b;
		hash () {}
		hash (ll ai) { a=b=ai; }
		hash (ll ai, ll bi) { a=ai; b=bi; }
		hash operator + (const hash i)
			{ return hash( (a+i.a)%mod1, (b+i.b)%mod2 ); }
		hash operator - (const hash i)
			{ return hash( (a-i.a+mod1)%mod1, (b-i.b+mod2)%mod2 ); }
		hash operator * (const hash i)
			{ return hash(a*i.a%mod1, b*i.b%mod2); }
		bool operator == (const hash i)
			{ return ( a == i.a ) && ( b == i.b ); }
	};
}

H::hash pw[300010];

namespace SGT
{
	struct seg_tree
	{
		int l,r,siz;
		H::hash lv,rv; // 1~n排列正逆序状压 
	} t[1200010];
	int pos;
	bool flag;
	
	void Lift(int inx)
	{
		t[inx].lv = t[inx<<1].lv + t[inx<<1|1].lv * pw[ t[inx<<1].siz ];
		t[inx].rv = t[inx<<1].rv * pw[ t[inx<<1|1].siz ] + t[inx<<1|1].rv;
	}
	
	void BuildTree(int inx,int lxx,int rxx)
	{
		t[inx].l=lxx; t[inx].r=rxx; t[inx].siz=rxx-lxx+1;
		t[inx].rv=t[inx].lv=H::hash(0);
		if (lxx==rxx) return;
		int m=(lxx+rxx)>>1;
		BuildTree(inx<<1,lxx,m);
		BuildTree(inx<<1|1,m+1,rxx);
	}
	
	void Ins(int inx)
	{
		if (t[inx].l==t[inx].r)
		{
			t[inx].lv=t[inx].rv=H::hash(1);
			return;
		}
		int m=(t[inx].l+t[inx].r)>>1;
		if (pos<=m) Ins(inx<<1);
		else Ins(inx<<1|1);
		Lift(inx);
	}

	H::hash Qry(int inx,int lx,int rx)
	{
		if (t[inx].l==lx && t[inx].r==rx) 
			return flag? t[inx].rv : t[inx].lv;
		int m=(t[inx].l+t[inx].r)>>1;

		if (lx>m) return Qry(inx<<1|1,lx,rx);
		if (rx<=m) return Qry(inx<<1,lx,rx);

		if (!flag)
			return Qry(inx<<1,lx,m) + ( Qry(inx<<1|1,m+1,rx) * pw[ m-lx+1 ] ) ;
		else 
			return Qry(inx<<1|1,m+1,rx) + ( Qry(inx<<1,lx,m) * pw[ rx-m ] ) ;
	}
}

int main()
{
	readx(n);
	for (int i=1;i<=n;i++) readx(hi[i]);
	pw[0] = H::hash(1);
	for (int i=1;i<=n;i++) pw[i]=pw[i-1]*H::hash(191LL);
	
	SGT::BuildTree(1,1,n); int k=0;
	for (int i=1;i<=n;i++)
	{
		k=min(n-hi[i],hi[i]-1);
		if (k)
		{
			SGT::flag=0;
			H::hash Lval = SGT::Qry(1,hi[i]-k,hi[i]-1);
			SGT::flag=1;
			H::hash Rval = SGT::Qry(1,hi[i]+1,hi[i]+k);
			if (!(Lval == Rval)) 
			{
				printf("YES\n");
				
				// cout<<i<<" "<<hi[i]<<endl;
				return 0;
			}
		}
		SGT::pos=hi[i];
		SGT::Ins(1);
	}
	
	printf("NO\n");
	return 0;
}