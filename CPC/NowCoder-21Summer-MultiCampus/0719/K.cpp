#include<bits/stdc++.h>
using namespace std;

const int inf = 1e9;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

#define LCH (u<<1)
#define RCH (u<<1|1)

struct SGT
{
	int val, l, r, pos;
}t[4000010];
int lx, rx;

int b[1000010], ans[1000010], nn[1000010];
int n, k, cnt;

SGT Update(SGT L, SGT R)
{
	SGT ret; 
	ret.l=L.l; ret.r=R.r;
	if (R.val<=L.val)
	{
		ret.val = R.val;
		ret.pos = R.pos;
	}
	else 
	{
		ret.val = L.val;
		ret.pos = L.pos;
	}
	return ret;
}

void BuildTree(int u, int lxx, int rxx)
{
	t[u].l = lxx; t[u].r = rxx;
	if (lxx == rxx)
	{
		t[u].val = b[lxx];
		t[u].pos = lxx;
		return;
	}
	int mid = (lxx + rxx) / 2;
	BuildTree(LCH, lxx, mid);
	BuildTree(RCH, mid+1, rxx);
	t[u]=Update(t[LCH], t[RCH]);
}

SGT Qry(int u)
{
	if (t[u].l >= lx && t[u].r <= rx)
		return t[u];
	int mid = (t[u].l+t[u].r)/2;
	int ret;
	if (rx<=mid) return Qry(LCH);
	else if (lx>mid) return Qry(RCH);
	else return Update(Qry(LCH), Qry(RCH));
}

SGT ZQry(int ll, int rr)
{
	lx = ll; rx = rr;
	return Qry(1);
}

void Solve(int L, int R, int ad)
{
	if (L>R) return;
	SGT mr = ZQry(L, R);
	
	// cerr << "Solve " << L << " " << R << " " << ad << endl;
	// cerr << mr.val << " " << mr.pos << endl;
	
	if (mr.val>n)
	{
		for (int i=L;i<=R;i++) ans[i]=++cnt;
		return;
	}
	
	while (mr.val>ad)
	{
		ans[L]=++cnt;
		L++;
		ad++;
	}
	
	// for (int i=1;i<=n;i++) printf("%d%c", ans[i], " \n"[i==n]);
	
	ans[mr.pos] = ++cnt;
	Solve(L, mr.pos-1, ad);
	Solve(mr.pos+1, R, ad+1);
}

int main()
{
	readx(n); readx(k); 
	int t1, t2; memset(b, -1, sizeof(b));
	for (int i=1;i<=k;i++)
	{
		readx(t1); readx(b[t1]);
	}
	
	t2 = 1;
	while (b[t2]==-1) t2++;
	if (b[t2]>t2) 
	{
		printf("-1\n");
		return 0;
	}
	for (int i=t2+1;i<=n;i++)
	{
		if (b[i]==-1) continue;
		else
		{
			if (b[i]-b[t2]>i-t2) 
			{
				printf("-1\n");
				return 0;
			}
			t2 = i;
		}
	}
	
	for (int i=1;i<=n;i++)
		if (b[i]==-1) b[i]=inf;
	
	BuildTree(1, 1, n);
	Solve(1, n, 1);
	
	for (int i=1;i<=n;i++) printf("%d%c", ans[i], " \n"[i==n]);
}