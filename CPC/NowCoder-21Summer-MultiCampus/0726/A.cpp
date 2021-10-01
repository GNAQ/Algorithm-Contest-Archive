#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, m, X, Y;
ll ai[100010], bi[100010];
double ans1, ans2;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

struct Node
{
	ll x, y;
	Node(ll inx, ll iny) : x(inx), y(iny)
		{}
	Node() {}
};

int hd, tl;
Node q[100010];

double Slp(Node a, Node b)
{
	return (double)(b.y-a.y) / (double)(b.x-a.x);
}

double BiSearch(Node u)
{
	if (tl==hd && hd==1)
	{
		return Slp(q[tl], u);
	}
	if (Slp(q[tl], u)>Slp(q[tl-1], q[tl]))
	{
		return Slp(u, q[tl]);
	}
	if (Slp(q[hd], u)<Slp(q[hd], q[hd+1]))
	{
		return Slp(q[hd], u);
	}
	
	int L = hd+1, R = tl;
	double tans=0;
	while (L<=R)
	{
		int mid = (L+R)/2;
		
		double kab = Slp(q[mid-1], q[mid]);
		double kbc = Slp(q[mid], u);
		
		// printf("Mid = %d, kab = %.2lf, kbc = %.2lf\n", mid, kab, kbc);
		
		if (kab <= kbc)
		{
			tans = Slp(q[mid], u);
			L = mid + 1;
		}
		else
		{
			R = mid - 1;
		}
	}
	return tans;
}

void Debug()
{
	cerr << "QUEUE" << endl;
	for (int i=hd;i<=tl;i++)
		printf("(%d, %d)%c", q[i].x, q[i].y, " \n"[i==tl]);
}

int main()
{
	readx(n); readx(m); readx(X); readx(Y);
	
	for (int i=1;i<=n;i++) readx(ai[i]);
	for (int i=1;i<=m;i++) readx(bi[i]);
	
	for (int i=2;i<=n;i++) ai[i]+=ai[i-1];
	for (int i=2;i<=m;i++) bi[i]+=bi[i-1];
	
	hd = 1; tl = 1; q[1]=Node(0, 0);
	for (int i=X;i<=n;i++)
	{
		Node u = Node(i, ai[i]);
		Node v = Node(i-X+1, ai[i-X+1]);
		
		// cerr << "I = " << i << endl;
		// Debug(); cerr << "!!" << BiSearch(u) << endl;
		
		ans1 = max(ans1, BiSearch(u));
		while (tl > hd && Slp(q[tl], v) <= Slp(q[tl-1], q[tl]))
			tl--;
		q[++tl]=v;
	}
	
	hd = 1; tl = 1; q[1]=Node(0, 0);
	for (int i=Y;i<=m;i++)
	{
		Node u = Node(i, bi[i]);
		Node v = Node(i-Y+1, bi[i-Y+1]);
		// Debug(); cerr << "!!" << BiSearch(u) << endl;
		ans2 = max(ans2, BiSearch(u));
		while (tl > hd && Slp(q[tl], v) < Slp(q[tl-1], q[tl]))
			tl--;
		q[++tl]=v;
	}
	
	// printf("%.12lf %.12lf\n", ans1, ans2);
	printf("%.12lf\n", ans1+ans2);
}