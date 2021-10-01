#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, m, X, Y;
int ai[100010], bi[100010];
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
	int x, y;
	Node(int inx, int iny) : x(inx), y(iny)
		{}
	Node() {}
};

int hd, tl;
Node q[100010];

double Slp(Node a, Node b)
{
	return (double)(b.y-a.y) / (double)(b.x-a.x);
}



int main()
{
	readx(n); readx(m); readx(X); readx(Y);
	
	for (int i=1;i<=n;i++) readx(ai[i]);
	for (int i=1;i<=m;i++) readx(bi[i]);
	
	for (int i=2;i<=n;i++) ai[i]+=ai[i-1];
	for (int i=2;i<=m;i++) bi[i]+=bi[i-1];
	
	q[hd=tl=1]=Node(0, 0);
	for (int i=1;i<=n;i++)
	{
		
	}
	
	printf("%.12lf %.12lf\n", ans1, ans2);
	printf("%.12lf\n", ans1+ans2);
}