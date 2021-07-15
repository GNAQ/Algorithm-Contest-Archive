#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
typedef long long ll;
using namespace std;

int n;
char s1[2000010], s2[400010];
int ans[400010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

vector<int> edge[400010];

void Is(int u, int v)
{
	edge[u].push_back(v);
}

namespace ACAM
{
	struct ACAM
	{
		int ch[27], fil, val;
		vector<int> ids;
	}ac[400010];
	int tsiz = 1;
	
	void Ins(char *wd, int id)
	{
		int len = strlen(wd + 1);
		for (int i=1;i<=len;i++) wd[i] = wd[i] - 'a' + 1;
		
		int u = 1;
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
		int u, cac;
		
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
	
	void Qry(char *str)
	{
		int len = strlen(str + 1), u = 1;
		
		for (int i=1;i<=len;i++) 
			str[i] = str[i] - 'a' + 1;
		
		for (int i=1;i<=len;i++)
		{
			u = ac[u].ch[str[i]];
			ac[u].val++;
		}
	}
	
	void DFS(int u)
	{
		for (int i=0;i<edge[u].size();i++)
		{
			DFS(edge[u][i]);
			ac[u].val+=ac[edge[u][i]].val;
		}
	}
}

int main()
{
	readx(n);
	for (int i=1;i<=n;i++)
	{
		scanf("%s", s2+1);
		ACAM::Ins(s2, i);
	}
	
	ACAM::GetFail();
	
	scanf("%s", s1+1);
	int len1 = strlen(s1+1);
	
	ACAM::Qry(s1);
	ACAM::DFS(1);
	
	{
		using namespace ACAM;
		for (int i=1;i<=tsiz;i++)
		{
			if (ac[i].ids.size())
			{
				for (int j=0;j<ac[i].ids.size();j++)
				{
					ans[ac[i].ids[j]]+=ac[i].val;
				}
			}
		}
	}
	
	for (int i=1;i<=n;i++)
	{
		printf("%d\n", ans[i]);
	}
	
	return 0;
}