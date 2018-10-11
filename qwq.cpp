#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<cmath>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

string src;
string trc;
int n,a;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll Get_Val(string input_str)
{
	int lp=0,rp=input_str.length()-1,len=rp;
	ll ret=0,pre_v=0;
	
	for (int i=0;i<=len;i++)
	{
		if (input_str[i]=='+' || )
		{
			
		}
		else if (input_str[i]=='(')
		{
			string tmp_s; int hasl;
			
			
			while ()
			
			
			pre_v=Get_Val(tmp_s);
		}
	}
	
	
}

bool Judge()
{
	
}

int main()
{
	getline(cin,src);
	readx(n);
	for (int i=1;i<=n;i++)
	{
		getline(cin,trc);
		if (Judge()) printf("%c",'A'-1+i);
	}
	putchar('\n');
	return 0;
}