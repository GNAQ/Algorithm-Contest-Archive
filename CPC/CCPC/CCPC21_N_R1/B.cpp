#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<map>
typedef long long ll;
using namespace std;

int n;
char str[200010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Solve()
{
	readx(n);
	scanf("%s", str+1);
	
	ll ans = 0; ll x=0, y=0;
	map< pair<int, int>, int> mapx;
	for (int i=1;i<=n;i++) 
	{
		ans+=mapx[make_pair(x, y)];
		mapx[make_pair(x, y)]++;
		if (str[i]=='U')
		{
			x++;
		}
		else if (str[i]=='D')
		{
			x--;
		}
		else if (str[i]=='L')
		{
			y++;
		}
		else
		{
			y--;
		}
	}
	ans+=mapx[make_pair(x, y)];
	
	cout << ans << endl;
}

void Clear()
{
	for (int i=1;i<=n+4;i++)
	{
		str[i]=0;
	}
	n=0; 
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
	
	
}