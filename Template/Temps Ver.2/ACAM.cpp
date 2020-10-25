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
#include<map>
#include<set>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

int n;
char sstr[180][100],mstr[1000010];

struct Answer
{
	int cnt,id;
	bool operator < (const Answer& B) 
	{ 
		if (cnt==B.cnt) return id<B.id;
		return cnt>B.cnt; 
	}
}ans[200];

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace ACAM
{
	struct ACAM_Node
	{
		int ch[27],val,fail;
	}node[1000010];
	int nsiz;
	
	void Ins(char* str,int id)
	{
		int now=0,len=strlen(str+1);
		for (int i=1;i<=len;i++)
		{
			if (!node[now].ch[str[i]-'a']) node[now].ch[str[i]-'a']=++nsiz;
			now=node[now].ch[str[i]-'a'];
		}
		node[now].val=id;
	}
	
	queue<int> que;
	void GetFail()
	{
		int cac;
		for (int i=0;i<26;i++) if (node[0].ch[i]) 
		{
//			node[node[0].ch[i]].fail=0;
			que.push(node[0].ch[i]);
		}
//		que.push(0);
		
		while (!que.empty())
		{
			cac=que.front(); que.pop(); 
			for (int i=0;i<26;i++)
			{
				if (node[cac].ch[i])
				{
					node[node[cac].ch[i]].fail=node[node[cac].fail].ch[i];
					que.push(node[cac].ch[i]);
				}
				else node[cac].ch[i]=node[node[cac].fail].ch[i];
			}
		}
	}
};

void Clear()
{
	memset(ACAM::node,0,sizeof(ACAM::node)); ACAM::nsiz=0; 
	memset(ans,0,sizeof ans);
}

void Query()
{
	using namespace ACAM;
	int len=strlen(mstr+1),now=0;
	
	for (int i=1;i<=len;i++)
	{
		now=node[now].ch[mstr[i]-'a'];
		for (int i=now;i;i=node[i].fail) 
			ans[node[i].val].cnt++;
	}
}

int main()
{
	scanf("%d",&n); 
	while (n)
	{
		for (int i=1;i<=n;i++) 
		{
			scanf("%s",sstr[i]+1);
			ans[i].id=i;
			ACAM::Ins(sstr[i],i);
		}
		scanf("%s",mstr+1);
		ACAM::GetFail(); 
		
		Query(); sort(ans+1,ans+n+1);
		
		printf("%d\n",ans[1].cnt);
		for (int i=1;i<=n;i++) 
			if (ans[i].cnt==ans[1].cnt)
				cout<<sstr[ans[i].id]+1<<endl;
		
		Clear(); scanf("%d",&n);
	}
}
