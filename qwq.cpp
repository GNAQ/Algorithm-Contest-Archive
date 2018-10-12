#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<queue>
#include<vector>
#define ll long long
using namespace std;

string src;
string trc;
int n,a_val;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll Get_Singal_Val(string input_str)
{
	
}

ll Get_Val(string input_str)
{
	int len=input_str.length()-1;
	ll ret=0,cac=0;
	int seq[50],ptr=0; memset(seq,0,sizeof seq);
	
	for (int i=0;i<=len;i++)
	{
		if (input_str[i]=='a') seq[++ptr]=a_val;
		else if (input_str[i]>='0' && input_str[i]<='9')
		{
			cac=input_str[i]-'0';
			while (input_str[i+1]>='0' && input_str[i+1]<='9')
			{
				i++;
				cac=cac*10+input_str[i]-'0';
			}
			seq[++ptr]=cac; 
		}
		else if (input_str[i]=='+') seq[++ptr]=-1;
		else if (input_str[i]=='-') seq[++ptr]=-2;
		else if (input_str[i]=='^') seq[++ptr]=-3;
		else if (input_str[i]=='(')
		{
			string tmp_s; int hasl=1; i++;
			
			while (hasl)
			{
				tmp_s.push_back(input_str[i]);
				if (input_str[i]=='(') hasl++;
				else if (input_str[i]==')') hasl--;
			}
			i--; tmp_s.pop_back();
			seq[++ptr]=Get_Val(tmp_s);
		}
	}
	
	for (int i=1;i<=ptr;i++)
	{
		
	}
	for (int i=1;i<=ptr;i++)
	{
		
	}
	for (int i=1;i<=ptr;i++)
	{
		
	}
	
	return ret;
}

string Erase_Spaces(string input_str)
{
	string ret_s;
	for (auto c:input_str)
		if (c!=' ') ret_s.push_back(c);
	return ret_s;
}

bool Judge()
{
	
}

int main()
{
	getline(cin,src); src=Erase_Spaces(src);
	readx(n);
	for (int i=1;i<=n;i++)
	{
		getline(cin,trc); trc=Erase_Spaces(trc);
		if (Judge()) printf("%c",'A'-1+i);
	}
	putchar('\n');
	return 0;
}