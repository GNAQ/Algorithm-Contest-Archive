#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<set>
#include<map>
#define ll long long
using namespace std;

vector<pair<int, int>> edge[100010];
int n, m;

int tsiz[100010], hson[100010];

template<typename int_t>
void readx(int_t& x)
{
	x = 0; int_t k = 1; char ch = 0;
	while (ch < '0' || ch > '9') { ch = getchar(); if (ch == '-') k = -1; }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	x *= k;
}

void Is(int fx, int tx, int wx)
{
	edge[fx].push_back({tx, wx});
	edge[tx].push_back({fx, wx});
}


void GetHr(int now)
{
	
	
	
}

void Divs(int now)
{
	
}
int main()
{
	readx(n); int fx,tx,wx;
	
	for (int i = 1; i < n; i++) 
	{
		readx(fx); readx(tx); readx(wx);
		Is(fx,tx,wx);
	}
	
	for (int i=1; i<=n; i++)
	{
		
	}
	
}
