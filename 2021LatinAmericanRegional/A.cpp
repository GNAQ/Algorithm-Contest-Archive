#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
	if (!b) return a;
	return gcd(b, a%b);
}

struct fr {
	int a, b;
	int id() { return a * 100 + b; }
	void simp()
	{
		int g = gcd(a, b);
		if (g != 1)
		{
			a /= g;
			b /= g;
		}
	}
	bool operator == (fr &x) { return a == x.a && b == x.b; }
	bool operator < (fr &x)
	{
		return a * x.b < x.a * b;
	}
};

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int lv_lim;
fr targ;
fr ve[13], anse[13];
int ans_lvl;
pair<int, int> ansid[13], vid[13];
int vis[10010];

bool IDFS(int lvl)
{
	for (int i=1;i<=lvl;i++) if (targ < ve[i])
	{
		for (int j=1;j<=lvl;j++) if (targ < ve[j])
		{
			vid[lvl] = {i, j};
			fr t1;
			t1.a = ve[i].a * ve[j].a;
			t1.b = ve[i].a * ve[j].b + ve[i].b * ve[j].a;
			t1.simp();
			if (t1.a > 100 || t1.b > 100) continue;
			
			if (t1 == targ)
			{
				for (int k=1;k<=lvl;k++)
				{
					ansid[k] = vid[k];
					anse[k] = ve[k];
					ans_lvl = lvl;
				}
				return true;
			}
			else if ((vis[t1.id()] == -1 || vis[t1.id()] == lvl) && lvl < lv_lim)
			{
				vis[t1.id()] = lvl;
				ve[lvl+1] = t1;
				if (IDFS(lvl+1)) 
					return true;
			}
		}
	}
	return false;
}

int main()
{
	readx(targ.a); readx(targ.b);
	
	fr base;
	base.a = 1; base.b = 2;
	if (base < targ) 
	{
		puts("*");
		return 0;
	}
	
	memset(vis, -1, sizeof(vis));
	ve[1].a = ve[1].b = 1;
	vis[ve[1].id()] = 1;
	for (int i=1;i<=9;i++)
	{
		lv_lim = i;
		bool ok = IDFS(1);
		if (ok)
		{
			for (int j=1;j<=ans_lvl;j++)
			{
				printf("%d %d\n%d %d\n", anse[ansid[j].first].a, anse[ansid[j].first].b,
					anse[ansid[j].second].a, anse[ansid[j].second].b);
			}
			return 0;
		}
	}
	puts("*");
	return 0;
}