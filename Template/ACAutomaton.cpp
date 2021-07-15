#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<cmath>
#include<queue>
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

vector<int> e[1000010];

void Is(int u, int v)
{
	e[u].push_back(v);
}

struct ACAM
{
	int fil, ch[27], val;
	vector<int> ids;
}ac[100010];
int tsiz=1;

int n;
char s1[1000010], s2[155][85];
int maxans;
vector<int> ansid;

int cnt;

void Ins(char *wd, int id)
{
	int u = 1, len = strlen(wd + 1);
	
	for (int i=1;i<=len;i++) wd[i]=wd[i]-'a'+1;
	
	for (int i=1;i<=len;i++)
	{
		if (!ac[u].ch[wd[i]]) 
			ac[u].ch[wd[i]]=++tsiz;
		u = ac[u].ch[wd[i]];
	}
	ac[u].ids.push_back(id);
}

void GetFail()
{
	queue<int> que;
	int u = 1, cac;
	
	for (int i=1;i<=26;i++) 
	{
		if (ac[1].ch[i])
		{
			ac[ac[1].ch[i]].fil = 1;
			
			// Add Edge
			Is(1, ac[1].ch[i]);
			
			que.push(ac[1].ch[i]);
		}
		else
			ac[1].ch[i]=1;
	}
	
	while (!que.empty())
	{
		u = que.front(); que.pop();
		
		for (int i=1;i<=26;i++)
		{
			int v = ac[u].ch[i];
			if (v)
			{
				ac[v].fil = ac[ac[u].fil].ch[i];
				
				// Add Edge
				Is(ac[v].fil, v);
				
				que.push(v);
			}
			else
				ac[u].ch[i] = ac[ac[u].fil].ch[i];
		}
	}
}

void DFS(int u)
{
	for (int i=0;i<e[u].size();i++)
	{
		DFS(e[u][i]);
		ac[u].val+=ac[e[u][i]].val;
	}
	if (ac[u].ids.size())
	{
		if (ac[u].val==maxans)
		{
			for (int i=0;i<ac[u].ids.size();i++)
				ansid.push_back(ac[u].ids[i]);
		}
		if (ac[u].val>maxans)
		{
			maxans = ac[u].val;
			ansid.clear();
			for (int i=0;i<ac[u].ids.size();i++)
				ansid.push_back(ac[u].ids[i]);
		}
	}
}

void Qry(char *str)
{
	int len = strlen(str + 1), u = 1;
	
	for (int i=1;i<=len;i++)	
		str[i]=str[i]-'a'+1;
		
	for (int i=1;i<=len;i++)
	{
		u = ac[u].ch[str[i]];
		ac[u].val++;
	}
}

void Solve()
{
	for (int i=1;i<=n;i++)
	{
		scanf("%s", s2[i]+1);
		Ins(s2[i], i);
	}
	
	GetFail();
	
	scanf("%s", s1+1);
	Qry(s1);
	
	DFS(1);
	
	sort(ansid.begin(), ansid.end());
	for (int i=1;i<=n;i++)
	{
		int len = strlen(s2[i] + 1);
		for (int j=1;j<=len;j++) 
			s2[i][j]+='a'-1;
	}
	
	printf("%d\n", maxans);
	for (int i=0;i<ansid.size();i++)
		printf("%s\n", s2[ansid[i]]+1);
}

void Clear()
{
	for (int i=1;i<=tsiz;i++) ac[i]=ac[100009];
	for (int i=1;i<=tsiz;i++) e[i].clear();
	
	memset(s2, 0, sizeof(s2));
	memset(s1, 0, sizeof(s1));
	
	ansid.clear(); maxans = 0;
	tsiz = 1;
}

int main()
{
	while (1)
	{
		readx(n); cnt++;
		if (n==0) return 0;
		Solve();
		Clear();
	}
}