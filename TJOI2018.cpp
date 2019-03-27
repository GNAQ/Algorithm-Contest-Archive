#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<iterator>
#include<queue>
#include<vector>
#include<map>
#include<set>
typedef long long ll;
using namespace std;

struct ed { int pre,to; }edge[200010];
int at=1,ptr[100010];

int n,nodev[100010],q;


template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
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

int dfn[100010],nnv[100010],dfsid[100010];
int dep[100010],tsiz[100010];

namespace LCA
{
	int dfstime,laa[100010][22];
	
	void DFS1(int now,int fa,int ndep)
	{
		laa[now][0]=fa;
		for (int i=1;i<=20;i++) laa[now][i]=laa[laa[now][i-1]][i-1];
		
		dfn[++dfstime]=now; nnv[dfstime]=nodev[now]; 
		
		dfsid[now]=dfstime; dep[now]=ndep; tsiz[now]=1;
		for (int v=ptr[now];v;v=edge[v].pre) if (edge[v].to!=fa)
		{
			DFS1(edge[v].to,now,ndep+1);
			tsiz[now]+=tsiz[edge[v].to];
		}
	}
	
	int LCA(int u,int v)
	{
		if (dep[v]>dep[u]) swap(u,v);
		for (int i=20;i>=0;i--) if (dep[laa[u][i]]>=dep[v]) u=laa[u][i];
		if (u==v) return v;
		for (int i=20;i>=0;i--) if (laa[u][i]!=laa[v][i])
		{
			u=laa[u][i];
			v=laa[v][i];
		}
		return laa[u][0];
	}
};

// Presistable Trie 可持久化 Trie
struct Trie
{
	Trie* ch[2];
	int val;
	
	Trie() 
	{
		ch[0]=ch[1]=nullptr;
		val=0;
	}
};
Trie* EmptyTrie()
{
	Trie* ret=new Trie;
	ret->ch[0]=ret->ch[1]=ret;
	ret->val=0;
	return ret;
}
typedef vector<Trie*> PTrie;

void Ins(Trie* inx,Trie* nowx,int tar,int dep) // dep start from 1
{
	if (nowx==nullptr) nowx=new Trie;
	if (inx==nullptr) inx=EmptyTrie();

	if (dep==31)
	{
		nowx->val=inx->val+1;
		return;
	}
	bool dir = tar & (1 << (30 - dep));
	Ins(inx->ch[dir],nowx->ch[dir],tar,dep+1);
	if (nowx->ch[0]!=nullptr) nowx->val+=nowx->ch[0]->val;
	if (nowx->ch[1]!=nullptr) nowx->val+=nowx->ch[1]->val;
}

int Qry1(Trie* inx,Trie* nowx,int tar,int dep)
{
	if (dep==31) return 0;
	if (inx==nullptr) inx=EmptyTrie();
	for (int i=0;i<2;i++)
	{
		if (nowx->ch[i]==nullptr) nowx->ch[i]=EmptyTrie();
		if (inx->ch[i]==nullptr) inx->ch[i]=EmptyTrie();
	}
	
	printf("dep = %d, tar = %d, old = %d, new = %d\n",dep,tar,inx->val,nowx->val);
	printf("Old 0 = %d, 1 = %d\n",inx->ch[0]->val,inx->ch[1]->val);
	printf("New 0 = %d, 1 = %d\n",nowx->ch[0]->val,nowx->ch[1]->val);
	
	bool dir = tar & (1 << (30 - dep));
	int ret=0;
	if (nowx->ch[dir^1]->val - inx->ch[dir^1]->val == 0)
	{
		cout<<"Qry with xor 0"<<endl;
		ret=Qry1(inx->ch[dir],nowx->ch[dir],tar,dep+1);
	}
	else
	{
		cout<<"Qry with xor 1"<<endl;
		ret=Qry1(inx->ch[dir^1],nowx->ch[dir^1],tar,dep+1)
			+(1 << (30 - dep));
	}
	
	return ret;
}

// int Qry2()
// {
// 	;
// }


PTrie r1,r2;

int main()
{
	readx(n); readx(q); int fx,tx;
	for (int i=1;i<=n;i++) readx(nodev[i]);
	for (int i=1;i<n;i++)
	{
		readx(fx); readx(tx); 
		Is(fx,tx);
	}
	
	
	r1.push_back(EmptyTrie()); r2.push_back(EmptyTrie());
	LCA::DFS1(1,0,1);
	
	for (int i=1;i<=n;i++) 
	{
		r1.push_back(new Trie);
		Ins(r1[i-1],r1[i],nnv[i],1);
	}
	
	int opt,u,v,val;
	while (q--)
	{
		readx(opt);
		if (opt==1)
		{
			readx(u); readx(val);
			
			const int& l=dfsid[u],r=dfsid[u+tsiz[u]-1];
			
			printf("	%d\n",Qry1(r1[l-1],r1[r],val,1));
		}
		else
		{
			readx(u); readx(v); readx(val);
			continue;
		}
	}
	
	
}