#include <bits/stdc++.h>
typedef long long ll;
using namespace std;


template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace DS
{
	struct SN
	{
		int l, r;
		int lch, rch;
		int val;
	}t[100010 * 18];
	int tcnt = 0;
	int fwt[100010];
	int LIM;
	
	int segQry(int u, int ql, int qr)
	{
		if (!u) return 0;
		if (t[u].l >= ql && t[u].r <= qr)
			return t[u].val;
		int mid = (t[u].l + t[u].r) / 2, ret = 0;
		if (ql <= mid) ret += segQry(t[u].lch, ql, qr);
		if (qr >  mid) ret += segQry(t[u].rch, ql, qr);
		return ret;
	}
	void segUpd(int &u, int qx, int cL, int cR)
	{
		if (!u)
		{
			u = ++tcnt;
			t[u].l = cL; t[u].r = cR;
			t[u].val = t[u].lch = t[u].rch = 0;
		}
		t[u].val++;
		if (cL == cR)
			return;
		int mid = (cL + cR) / 2;
		if (qx <= mid) segUpd(t[u].lch, qx, cL, mid);
		else segUpd(t[u].rch, qx, mid + 1, cR);
	}
	
	void fwtUpd(int px, int py)
	{
		while (px < LIM)
		{
			segUpd(fwt[px], py, 1, LIM);
			px += (px & (-px));
		}
	}
	int fwtQry(int px, int py)
	{
		int ret = 0;
		while (px)
		{
			ret += segQry(fwt[px], 1, py);
			px - (px & (-px));
		}
		return ret;
	}
}

// for general use
pair<double, double> TransPos(int px, int py, int a, int b) // a < b
{
	if (a != 90 && b != 90)
	{
		double ta = tan((360.0 - a) / 360.0), tb = tan((360.0 - b) / 360.0);
		double v = (px * ta - py) / (ta - tb);
		double u = px - v;
		return {u, v};
	}
	else if (a != 90) // b == 90
	{
		
	}
	else // a == 90
	{
		
	}
}

int main()
{
	
	
	
}