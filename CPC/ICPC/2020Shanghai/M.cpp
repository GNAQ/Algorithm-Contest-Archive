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

struct File_St
{
	map<string, int> table;
	vector<int> sons;
	int v[2], fcnt;
	bool all_ok;
} f[10010];
int cnt=0, ans;
int n,m;

char inp[10010];
int ins_val;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Clear()
{
	for (int i=1;i<=cnt;i++)
	{
		f[i].table.clear();
		f[i].fcnt=f[i].v[0]=f[i].v[1]=0;
		f[i].all_ok=false;
		f[i].sons.clear();
	}
	cnt=0;
	ans=0;
}

void Ins(int pos, int len, int id)
{	
	int flag=1;
	for (int i=pos;i<=len;i++) 
	{
		if (inp[i]=='/') 
			flag = 0;
	}
	
	if (flag)
	{
		f[id].v[ins_val]++;
		return;
	}
	
	string name; int npos;
	for (int i=pos; true; i++)
	{
		if (inp[i]=='/')
		{
			npos=i+1;
			break;
		}
		name += inp[i];
	}
	
	int sonid=f[id].table[name];
	if (sonid==0)
	{
		cnt++;
		f[id].table[name]=sonid=cnt;
		f[id].sons.push_back(sonid);
	}
	
	Ins(npos, len, sonid);
}

bool Sol(int id)
{
	if (f[id].sons.size()==0)
	{
		f[id].fcnt=f[id].v[1];
		if (f[id].v[0]==0)
			return true;
		else 
			return false;
	}
	
	f[id].all_ok=true; f[id].fcnt=f[id].v[1];
	
	for (auto i:f[id].sons)
	{
		int tmp = Sol(i);
		f[id].all_ok &= tmp;
		if (tmp) f[id].fcnt+=1;
		else f[id].fcnt+=f[i].fcnt;
	}
	
	if (f[id].all_ok==true && f[id].v[0]==0) return true;
	else return false;
}

void Go()
{
	readx(n); readx(m);
	
	cnt=1;
	f[1].v[0]=f[1].v[1]=0;
	
	int len;
	ins_val = 1; // y
	for (int i=1;i<=n;i++)
	{
		scanf("%s", inp+1);
		len=strlen(inp+1);
		Ins(1, len, 1);
	}
	
	ins_val = 0; // n
	for (int i=1;i<=m;i++)
	{
		scanf("%s", inp+1);
		len=strlen(inp+1);
		Ins(1, len, 1);
	}
	
	ans=f[1].v[1];
	for (auto i:f[1].sons)
	{
		int tmp=Sol(i);
		if (tmp) ans++;
		else ans+=f[i].fcnt;
	}
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Go();
		
		printf("%d\n", ans);
		
		Clear();
	}
	
	return 0;
}
