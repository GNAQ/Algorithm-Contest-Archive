// #include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
#define PAUSE system("pause")
using namespace std;

struct ACAutomaton
{
	int ch[26],val,fail;
	ACAutomaton()
	{
		memset(ch,0,sizeof ch);
		val=fail=0;
	}
}AC[1000010];
int tsiz=0;
struct answer { int num,pos; }ans[170]={0};

int n;
queue<int> que;
char chs[1001010]={0},w[170][90]={0};

inline void Clear() { memset(AC,0,sizeof AC); tsiz=0; memset(ans,0,sizeof ans); }
inline bool cmp1(answer a,answer b) { if (a.num==b.num) return a.pos<b.pos; return a.num>b.num; }

inline void Insert(char wd[],int cod)
{
	register int pos=0,len=strlen(wd+1);
	for (int i=1;i<=len;i++)
	{
		if (!AC[pos].ch[wd[i]-'a']) AC[pos].ch[wd[i]-'a']=++tsiz;
		pos=AC[pos].ch[wd[i]-'a'];
	}
	AC[pos].val=cod;
}

inline void GetFail()//Build Trie Graph
{
	register int cac;
	for (int i=0;i<26;i++) if (AC[0].ch[i]) que.push(AC[0].ch[i]);
	
	while (!que.empty())
	{
		cac=que.front(); que.pop();
		for (int i=0;i<26;i++) 
		{
			if (AC[cac].ch[i])
			{
				AC[AC[cac].ch[i]].fail=AC[AC[cac].fail].ch[i];
				que.push(AC[cac].ch[i]);
			}
			else AC[cac].ch[i]=AC[AC[cac].fail].ch[i];
		}
	}
}

inline void query(char wd[])
{
	register int len=strlen(wd+1),pos=0;
	for (int i=1;i<=len;i++)
	{
		pos=AC[pos].ch[wd[i]-'a'];
		for (int t=pos;t;t=AC[t].fail) ans[AC[t].val].num++;
	}
}

int main()
{
	scanf("%d",&n); Clear();
	while (n)
	{
		for (int i=1;i<=n;i++) 
		{
			scanf("%s",w[i]+1);
			ans[i].pos=i;
			Insert(w[i],i);
		}
		GetFail();
		scanf("%s",chs+1);
		query(chs); sort(ans+1,ans+n+1,cmp1);
		
		printf("%d\n",ans[1].num);
		cout<<w[ans[1].pos]+1<<endl;
		for (int i=2;i<=n;i++)
		{
			if (ans[i].num==ans[i-1].num) cout<<w[ans[i].pos]+1<<endl;
			else break;
		}
		
		scanf("%d",&n);Clear();
	}
	// PAUSE;
	return 0;
}