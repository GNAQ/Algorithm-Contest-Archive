#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>
#include<vector>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<map>
#include<set>
#define ll long long
using namespace std;

struct ed
{
	int pre,to;
}edge[2000010];
int n,m,at=1,ptr[100010];

vector<int> theta_list[100010];
int id[100010],peo[100010],theta[100010];
int cor[100010],exist[100010];

void readx(int& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') ch=getchar();
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx)
{
	at++;
	edge[at].pre=ptr[fx];
	edge[at].to=tx;
	ptr[fx]=at;
	at++;
	edge[at].pre=ptr[tx];
	edge[at].to=fx;
	ptr[tx]=at;
}

void Solve_PEO()
{
	for (int i=1;i<=n;i++) theta_list[0].push_back(i);
	int max_theta=0;
	for (int i=n;i;i--)
	{
		int now;
		while (1)
		{
			while (theta_list[max_theta].empty()) max_theta--;
			now=theta_list[max_theta].back();
			if (id[now]) theta_list[max_theta].pop_back();
			else break;
		}
		id[now]=i; peo[i]=now;
		for (int v=ptr[now];v;v=edge[v].pre) if (!id[edge[v].to])
		{
			theta[edge[v].to]++;
			theta_list[theta[edge[v].to]].push_back(edge[v].to);
			max_theta=max(max_theta,theta[edge[v].to]);
		}
	}
}

int main()
{
	readx(n); readx(m); int fx,tx;
	for (int i=1;i<=m;i++)
	{
		readx(fx); readx(tx);
		Is(fx,tx);
	}
	Solve_PEO();
	
	cor[peo[n]]=1;
	for (int i=n-1;i;i--)
	{
		int siz=0,now=peo[i];
		for (int v=ptr[now];v;v=edge[v].pre) if (id[edge[v].to]>i)
			{ siz++; exist[siz]=cor[edge[v].to]; }
		if (!siz) { cor[now]=1; continue; }
		sort(exist+1,exist+siz+1); exist[++siz]=1e8;
		
		if (exist[1]>1) { cor[now]=1; continue; }
		for (int j=2;j<=siz;j++) if (exist[j]-exist[j-1]>1)
		{
			cor[now]=exist[j-1]+1;
			break;
		}
	}
	
	int ans=0;
	for (int i=1;i<=n;i++) ans=max(ans,cor[i]);
	printf("%d\n",ans);
}
