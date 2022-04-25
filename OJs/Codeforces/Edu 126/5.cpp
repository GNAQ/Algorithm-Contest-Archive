#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

#define LCH (u<<1)
#define RCH (u<<1|1)

struct SegN
{
	int l, r;
	int ans, ds[7]; // 123L  456R
}t[500050*4];
int lx, rx;

int n;
bool r[500010][4];
char tmp[500010];

SegN Pushup(SegN a, SegN b)
{
	SegN ret;
	ret.l = a.l; ret.r = b.r;
	ret.ans = a.ans + b.ans;

	for (int i=1;i<=3;i++)
	{
		if (r[a.r][i] && r[b.l][i] && b.ds[i] != a.ds[i + 3])
		{
			ret.ans--;
			if (i == 3 && (b.ds[i] == a.ds[4] || b.ds[i] == a.ds[5])) // 101 <-> 111
			{
				for (int j=1;j<=6;j++)
					if (j != (i + 3) && a.ds[j] == a.ds[i + 3])
						a.ds[j] = b.ds[i];
				a.ds[i + 3] = b.ds[i];
			}
			else
			{
				for (int j=1;j<=6;j++) 
					if (j != i && b.ds[j] == b.ds[i])
						b.ds[j] = a.ds[i + 3];
				b.ds[i] = a.ds[i + 3];
			}
		}
	}
	for (int i=1;i<=3;i++) ret.ds[i] = a.ds[i];
	for (int i=4;i<=6;i++) ret.ds[i] = b.ds[i];
	return ret;
}

void BuildTree(int u, int L, int R)
{
	t[u].l = L; t[u].r = R;
	if (L == R)
	{
		for (int i=1;i<=3;i++) if (r[L][i])
		{
			t[u].ds[i] = t[u].ds[i + 3] = L + (i - 1) * n;
			t[u].ans++;
		}
		for (int i=2;i<=3;i++) if (r[L][i] && r[L][i - 1])
		{
			t[u].ds[i] = t[u].ds[i + 3] = t[u].ds[i - 1];
			t[u].ans--;
		}
		return;
	}
	int mid = (L + R) / 2;
	BuildTree(LCH, L, mid);
	BuildTree(RCH, mid + 1, R);
	t[u] = Pushup(t[LCH], t[RCH]);
}

SegN Qry(int u, int l, int r)
{
	if (l >= lx && r <= rx)
		return t[u];
	int mid = (l + r) / 2;
	if (lx > mid) return Qry(RCH, mid + 1, r);
	if (rx <= mid) return Qry(LCH, l, mid);
	return Pushup(Qry(LCH, l, mid), Qry(RCH, mid + 1, r));
}

int main()
{
	scanf("%d", &n);
	for (int i=1;i<=3;i++)
	{
		scanf("%s", tmp + 1);
		for (int j=1;j<=n;j++)
			r[j][i] = tmp[j] - '0';
	}
	BuildTree(1, 1, n);
	int q;
	scanf("%d", &q);
	for (int i=1;i<=q;i++)
	{
		scanf("%d%d", &lx, &rx);
		printf("%d\n", Qry(1, 1, n).ans);
	}
}