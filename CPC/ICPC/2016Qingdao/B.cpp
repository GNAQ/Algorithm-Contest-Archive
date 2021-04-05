#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<set>
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

bool ok(int a1, int a2, int a3, int a4)
{
	if (a1==a2 && a2==a3 && a3==a4) return true;
	return false;
}

void Solve()
{
	int a,b,c,d,
		e,f,g,h,
		i,j,k,l,
		m,n,o,p,
		q,r,s,t,
		u,w,v,x;
	scanf("%d%d%d%d", &a, &b, &c, &d);
	scanf("%d%d%d%d", &e, &f, &g, &h);
	scanf("%d%d%d%d", &i, &j, &k, &l);
	scanf("%d%d%d%d", &m, &n, &o, &p);
	scanf("%d%d%d%d", &q, &r, &s, &t);
	scanf("%d%d%d%d", &u, &v, &w, &x);
	
	if (ok(a,b,c,d) && ok(e,f,g,h) && ok(i,j,k,l) && 
		ok(m,n,o,p) && ok(q,r,s,t) && ok(u,v,w,x)) cout<<"YES"<<endl;
	else if (ok(q,r,s,t) && ok(u,v,w,x) && ok(a,c,f,h) && ok(e,g,j,l) &&
			 ok(i,k,n,p) && ok(m,o,b,d)) cout<<"YES"<<endl;
	else if (ok(q,r,s,t) && ok(u,v,w,x) && ok(a,c,n,p) && ok(e,g,b,d) &&
			 ok(i,k,f,h) && ok(m,o,j,l)) cout<<"YES"<<endl;
	else if (ok(a,b,c,d) && ok(i,j,k,l) && ok(r,t,g,h) && ok(e,f,x,v) &&
			 ok(w,u,n,m) && ok(p,o,q,s)) cout<<"YES"<<endl;
	else if (ok(a,b,c,d) && ok(i,j,k,l) && ok(r,t,n,m) && ok(e,f,q,s) && 
			 ok(w,u,g,h) && ok(p,o,x,v)) cout<<"YES"<<endl;
	else if (ok(e,f,g,h) && ok(m,n,o,p) && ok(q,r,c,d) && ok(a,b,w,x) &&
			 ok(u,v,j,i) && ok(l,k,s,t)) cout<<"YES"<<endl;
	else if (ok(e,f,g,h) && ok(m,n,o,p) && ok(q,r,j,i) && ok(a,b,s,t) && 
			 ok(u,v,c,d) && ok(l,k,w,x)) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return;
}

int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		Solve();
	}
}