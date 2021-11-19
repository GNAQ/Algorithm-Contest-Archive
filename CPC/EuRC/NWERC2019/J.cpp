#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, C, R;
struct _Nd
{
	int v, id;
	bool operator < (const _Nd &b) const
		{ return abs(this->v) < abs(b.v); }
}bi[500010];
int si[500010];

int l[500010], r[500010];
ll tans, fans = 1e18;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int GetS(int x)
{
	if (si[x] > 0) return 1;
	return -1;
}

void Del(int x)
{
	int ll = l[x], rr = r[x];
	if (l[x]!=-1)
		if (abs(x - l[x])%2 != (GetS(x) != GetS(l[x]))) 
			tans-=2;
	if (r[x]!=-1)
		if (abs(x - r[x])%2 != (GetS(x) != GetS(r[x]))) 
			tans-=2;
	r[ll] = rr;
	l[rr] = ll;
	if (l[x]!=-1 && r[x]!=-1)
		if (abs(r[x]-l[x])%2 != (GetS(r[x]) != GetS(l[x]))) 
			tans+=2;
}

int main()
{
	readx(n); readx(C); readx(R);
	for (int i=1;i<=n;i++)
	{
		readx(si[i]);
		bi[i].id = i;
		bi[i].v = si[i];
		l[i]=i-1;
		r[i]=i+1;
	}
	sort(bi+1, bi+n+1);
	l[1] = r[n] = -1; 
	
	// Remove all zeros
	ll ans1 = 0, ans2 = 0;
	for (int i=1;i<=n;i++)
	{
		if (si[i]==0)
			ans1++;
		else
		{
			int r = i + 1;
			int l = i - 1;
			while (r<=n && si[r] == 0) r++;
			while (l>=1 && si[l] == 0) l--;
			if (l>=1 && GetS(l)==GetS(i))
				ans2++;
			if (r<=n && GetS(r)==GetS(i))
				ans2++;
		}
	}
	fans = min(fans, 1LL * R * (ans1 + ans2 / 2));
	
	// cover all zeros
	for (int i=1;i<=n;i++)
	{
		if (l[i]!=-1)
			if (abs(i - l[i])%2 != (GetS(i) != GetS(l[i]))) 
				tans++;
		if (r[i]!=-1)
			if (abs(i - r[i])%2 != (GetS(i) != GetS(r[i]))) 
				tans++;
	}
	int pos = 1;
	for (;pos<=n;pos++)
	{
		int frt = pos;
		while (pos<n && bi[pos+1].v == bi[pos].v) pos++;
		ans1 = 1LL * C * (abs(bi[pos].v) + 1);
		
		for (int i=frt;i<=pos;i++)
			Del(bi[i].id);
		fans = min(fans, 1LL * tans / 2 * R + ans1);
	}
	
	printf("%lld\n", fans);
	return 0;
}