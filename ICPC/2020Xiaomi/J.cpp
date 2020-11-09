#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

struct Seg_T
{
	int l, r;
	ll val, tag;
}t[2010][1010*4];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

#define LCH (inx<<1)
#define RCH (inx<<1|1)
void BuildTree(int inx, int lxx,int rxx, int id)
{
	t[id][inx].l=lxx; t[id][inx].r=rxx;
	t[id][inx].tag=t[id][inx].val=0;
	if (lxx==rxx)
		return;
	int m=(lxx+rxx)>>1;
	BuildTree(LCH,lxx,m,id); BuildTree(RCH,m+1,rxx, id);
	return;
}

void Pushdown(int inx,int id)
{
	ll c=t[id][inx].tag;
	t[id][LCH].tag+=c;
	t[id][RCH].tag+=c;
	t[id][LCH].val+=1LL*c*(t[id][LCH].r-t[id][LCH].l+1);
	t[id][RCH].val+=1LL*c*(t[id][RCH].r-t[id][RCH].l+1);
	t[id][inx].tag=0;
}

int lx,rx;
ll vx;

void Upd(int inx, int id)
{
	if (t[id][inx].l>=lx && t[id][inx].r<=rx)
	{
		t[id][inx].val+=1LL*vx*(t[id][inx].r-t[id][inx].l+1);
		t[id][inx].tag+=vx;
		return;
	}
	if (t[id][inx].tag) Pushdown(inx, id);
	int m=(t[id][inx].l+t[id][inx].r)/2;
	if (lx<=m) Upd(LCH, id);
	if (rx>m) Upd(RCH, id);
	t[id][inx].val=t[id][LCH].val+t[id][RCH].val;
}

ll Qry(int inx, int id)
{
	if (t[id][inx].l>=lx && t[id][inx].r<=rx)
		return t[id][inx].val;
	if (t[id][inx].tag) Pushdown(inx, id);
	int m=(t[id][inx].l+t[id][inx].r)/2;
	ll ret=0;
	if (lx<=m) ret+=Qry(LCH, id);
	if (rx>m) ret+=Qry(RCH, id);
	return ret;
}

int n,m,a,b,G[1010][1010];

void Check()
{
    cout<<"Check"<<endl;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            lx=rx=j;
            printf("%10lld%c",Qry(1,i), " \n"[j==m]);
        }
    }
     
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            lx=rx=i;
            printf("%10lld%c",Qry(1,n+j), " \n"[j==m]);
        }
    }
    cout<<endl;
}

int Go()
{
	readx(n); readx(m); readx(a); readx(b);
	for (int i=1;i<=n;i++)	
		for (int j=1;j<=m;j++)
			readx(G[i][j]);
	for (int i=1;i<=n;i++) // 行
		BuildTree(1,1,m,i);
	for (int i=1;i<=m;i++) // 列
		BuildTree(1,1,n,n+i);
	
	for (int i=1;i<=n-a+1;i++)
	{
		// update pre sums
		for (int j=1;j<=m-b+1;j++)
		{
			lx=rx=i;
			ll cac=Qry(1, j+n);
			lx=j; rx=j+b-1;
			vx=cac;
			if(vx>1e9) return -1;
			Upd(1, i);
		}
		
		for (int j=1;j<=m-b+1;j++)
		{
			lx=rx=j;
			ll sum = Qry(1, i);
			if(sum>1e9) return -1;
			int cac = G[i][j]-sum;
			if (cac<0) return -1;
			vx=cac;
			
			// row
			lx=j; rx=j+b-1;
			Upd(1,i);
			// Col
			lx=i; rx=i+a-1;
			Upd(1,j+n);
			
			G[i][j]=0;
			// printf("[%lld, %lld] %d %d\n",i,j,cac,sum);
			// Check();
		}
	}
	
	for (int i=n-a+2;i<=n;i++)
	{
		for (int j=1;j<=m-b+1;j++)
		{
			lx=rx=i;
			ll cac=Qry(1, j+n);
			lx=j; rx=j+b-1;
			vx=cac;
			if(vx>1e9) return -1;
			Upd(1, i);
		}
	}
	
	for (int i=1;i<=n;i++) 
		for (int j=1;j<=m;j++)
			if (i>n-a+1 || j>m-b+1)
			{
				lx=rx=j;
				ll cac = Qry(1, i);
				if (cac!=G[i][j]) return -1;
			}
	
	return 1;
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		int ans = Go();
		printf("%s\n", ans==1? "^_^" : "QAQ");
	}
}