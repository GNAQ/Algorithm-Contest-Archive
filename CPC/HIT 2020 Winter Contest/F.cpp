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

char str[1010];
int len;

vector< pair<string, string> > anss;

bool cmp(pair<string, string> a, pair<string, string> b)
{
	return a.first<b.first;
}

void Clear()
{
	anss.clear();
}

int GetEndPos(int bg)
{
	int ok = 0;
	while (1)
	{
		if (str[bg]=='{') ok++;
		if (str[bg]=='}') ok--;
		bg++;
		if ((ok==0) && (str[bg]==',' || str[bg]=='}')) break;
	}
	return bg;
}

string GetName(int l)
{
	if (str[l]=='"') l++;
	string ret;
	while (1)
	{
		if (str[l]=='"') break;
		ret+=str[l];
		l++;
	}
	return ret;
}

void Parse(int L, int R, string prefix)
{
	int l=L+1,r=L+1;
	
	string name;
	string value;
	
	while (str[l]==' ') l++;
	
	while (r<R)
	{
		r=GetEndPos(l);
		
		name.clear(); value.clear();
		
		name = GetName(l);
		
		l++;
		while (str[l]!='"') l++;
		l++;
		while (str[l]==':' || str[l]==' ') l++;
		
		if (str[l]=='{')
		{
			Parse(l, r-1, prefix + '.' + name);
		}
		else 
		{
			while (l<r)
			{
				value+=str[l];
				l++;
			}
			name = prefix + '.' + name;
			
			anss.push_back( make_pair(name, value) );
		}
		
		l=r+1;
		while (str[l]==' ') l++;
	}
}

void Solve()
{
	gets(str+1);
	len = strlen(str+1);
	
	string pref;
	
	Parse(1, len, pref);
	
	sort(anss.begin(), anss.end(), cmp);
	
	int siz = anss.size()-1;
	for (int i=0;i<=siz;i++)
	{
		int alen = anss[i].first.length()-1;
		for (int j=1;j<=alen;j++) putchar(anss[i].first[j]);
		putchar('=');
		cout<<anss[i].second<<endl;
	}
	return;
}

int main()
{
	int T; readx(T);
	for (int tt=1;tt<=T;tt++)
	{
		printf("CASE %d:\n", tt);
		
		Solve();
		Clear();
	}
	
}
