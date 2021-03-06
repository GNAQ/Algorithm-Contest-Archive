#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
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

char str[1010][110];
int len[1010];
int n;

struct DocT
{
	vector< pair<string,DocT> > dvec;
	int ok;
};

void Clear()
{
}

int GetLev(int p)
{
	int ex=1;
	while (str[p][ex]==' ') ex++;
	return ex-1;
}

string GetName(int p)
{
	string ret;
	for (int i=1;i<=len[p];i++) ret+=str[p][i];
	return ret;
}

DocT Build(int st, int ed)
{
	DocT ret;
	ret.ok = 1;
	
	int lvl = GetLev(st);
	
	for (int i=st;i<=ed;i++)
	{
		int lvi = GetLev(i);
		if (lvi != lvl) continue;
//		ret.dvec.push_back(GetName(i));
		if (i<ed && GetLev(i+1)>lvi)
		{
			int j=i+1;
			while (j+1<=ed && GetLev(j+1)>lvi) j++;
			ret.dvec.push_back( make_pair(GetName(i), Build(i+1,j)) );
		}
		else
		{
			DocT tmp;
			tmp.ok = 0;
			ret.dvec.push_back( make_pair(GetName(i),tmp) );
		}
	}
	
	return ret;
}

bool cmp(pair<string,DocT> a, pair<string,DocT> b)
{
	return a.first<b.first;
}

void Sort(DocT *now)
{
	sort(now->dvec.begin(), now->dvec.end(), cmp);
	int siz = now->dvec.size()-1;
	for (int i=0;i<=siz;i++)
	{
		if (now->dvec[i].second.ok==1)
		{
			Sort(&(now->dvec[i].second));
		}
	}
}

void Print(DocT* now)
{
	int siz = now->dvec.size()-1;
	for (int i=0;i<=siz;i++)
	{
		cout<<now->dvec[i].first<<endl;
		if (now->dvec[i].second.ok==1)
		{
			Print(&(now->dvec[i].second));
		}
	}
}

void Solve()
{
	DocT ans = Build(1,n);
	
	Sort(&ans);
	Print(&ans);
}

int main()
{
	int T; readx(T);
	for (int tt=1;tt<=T;tt++)
	{
		printf("CASE: %d\n", tt);
		readx(n);
		for (int i=1;i<=n;i++)
		{
			gets(str[i]+1);
			len[i]=strlen(str[i]+1);
		}
		
		Solve();
		
		Clear();
	}
	return 0;
}
