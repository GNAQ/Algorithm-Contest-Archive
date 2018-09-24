#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
#define p_b push_back
#define m_p make_pair
#define fst first
#define snd second
using namespace std;

vector<pair<int,int>> edge[100010];

int dis[100010],dptr=0;
bool vis[100010]={0};

void readx(int& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx,int wx)
{
	edge[fx].p_b({tx,wx});
	edge[tx].p_b({fx,wx});
}

void _Init(int now,int fa,int nowdis)
{
	dis[++dptr]=nowdis;
	for (auto v:edge[now]) if (!vis[v.fst] && v.fst!=fa) _Init(v.fst,now,v.snd+nowdis);
}

int main()
{
	
	
	
}
