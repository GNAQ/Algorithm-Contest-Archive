#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

#define LCH (u<<1)
#define RCH (u<<1|1)

struct Seg_Tree
{
	int l, r;
	int vor[31], vand[31];
	int vcnt[31];
}t[100005*4], dst;
int lx, rx;

int ai[100010], n, q;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void MergeN(Seg_Tree &d, const Seg_Tree &src)
{
	for (int i=0;i<31;i++)
	{
		d.vcnt[i] += src.vcnt[i];
		d.vor[i] |= src.vor[i];
		d.vand[i] &= src.vand[i];
	}
	return;
}

int popcount(unsigned v)
{
	int ret = 0;
	while (v)
	{
		ret += v & 1;
		v >>= 1;
	}
	return ret;
}

void BuildTree(int u, int lxx, int rxx)
{
	t[u].l = lxx; t[u].r = rxx;
	for (int i=0;i<31;i++) 
		t[u].vand[i] = UINT_MAX;
	if (lxx == rxx)
	{
		int pc = popcount(ai[lxx]);
		t[u].vor[pc] |= ai[lxx];
		t[u].vand[pc] &= ai[lxx];
		t[u].vcnt[pc] += 1;
		return;
	}
	int mid = (lxx + rxx) / 2;
	BuildTree(LCH, lxx, mid);
	BuildTree(RCH, mid + 1, rxx);
	MergeN(t[u], t[LCH]);
	MergeN(t[u], t[RCH]);
}

void Qry(int u)
{
	if (t[u].l >= lx && t[u].r <= rx)
	{
		MergeN(dst, t[u]);
		return;
	}
	int mid = (t[u].l + t[u].r) / 2;
	if (lx <= mid) Qry(LCH);
	if (rx > mid) Qry(RCH);
	return;
}

int main()
{
	readx(n); readx(q);
	for (int i=1;i<=n;i++)
		readx(ai[i]);
	
	BuildTree(1, 1, n);
	
	for (int i=1;i<=q;i++)
	{
		for (int w=0;w<31;w++)
		{
			dst.vcnt[w] = 0;
			dst.vand[w] = UINT_MAX;
			dst.vor[w] = 0;
		}
		readx(lx); readx(rx);
		Qry(1);
		
		bool ans = false;
		for (int j=0;j<31;j++) if (dst.vor[j] == dst.vand[j] || (!dst.vcnt[j]))
		{
			int cor = 0, cand = UINT_MAX, orcnt = 0;
			for (int k=0;k<j;k++)
			{
				orcnt += dst.vcnt[k];
				cor |= dst.vor[k];
			}
			for (int k=j+1;k<31;k++)
			{
				cand &= dst.vand[k];
			}
			if (dst.vcnt[j] == 1) // only one to assign
			{
				if ((cor | dst.vor[j]) == cand && orcnt + 1 != rx - lx + 1)
					ans = true;
				if ((cand & dst.vand[j]) == cor && orcnt != 0)
					ans = true;
			}
			if (dst.vcnt[j] >= 2)
				if ((cor | dst.vor[j]) == (cand & dst.vand[j]))
					ans = true;
			if (!dst.vcnt[j]) 
				if (cor == cand && orcnt != 0)
					ans = true;
			if (ans)
				break;
		}
		printf("%s\n", ans ? "YES" : "NO");
	}
	return 0;
}

/*
Solution:

	Please refer to the official solution.

*/