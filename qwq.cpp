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

const long long ADD_C=-2000000000000000;
const long long MIN_C=-2000000000000001;
const long long MUL_C=-2000000000000002;
const long long POW_C=-2000000000000003;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll fastpow(ll an,ll p)
{
	ll ret=1;
	for (;p;p>>=1,an*=an) if (p&1) ret*=an;
	return ret;
}

ll Get_Val(string input_str)
{
	int len=input_str.length()-1; ll cac=0;
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
		else if (input_str[i]=='*') seq[++ptr]=-3;
		else if (input_str[i]=='^') seq[++ptr]=-4;
		else if (input_str[i]=='(')
		{
			string tmp_s; int hasl=1; i++;
			
			while (hasl)
			{
				tmp_s.push_back(input_str[i]);
				if (input_str[i]=='(') hasl++;
				else if (input_str[i]==')') hasl--;
				i++;
			}
			i--; tmp_s.pop_back();
			seq[++ptr]=Get_Val(tmp_s);
		}
	}
	
	for (int i=1;i<=ptr;i++)
	{
		if (seq[i]<0)
		{
			if (seq[i]==POW_C) printf("^");
			else if (seq[i]==MUL_C) printf("*");
			else if (seq[i]==MIN_C) printf("-");
			else if (seq[i]==ADD_C) printf("+");
		}
		else if (seq[i]) printf("%d ",seq[i]);
	}
	cout<<endl;
	
	int lval,rval,lp,rp;
	for (int i=1;i<=ptr;i++) if (seq[i]==-4)
	{
		lp=i-1; while (!seq[lp] && lp>1) lp--;
		rp=i+1; while (!seq[rp] && rp<ptr) rp++;
		if ()
		if ()
		seq[i]=fastpow(seq[lp],seq[rp]);
		seq[lp]=seq[rp]=0;
	}
	
	for (int i=1;i<=ptr;i++)
	{
		if (seq[i]<0)
		{
			if (seq[i]==POW_C) printf("^");
			else if (seq[i]==MUL_C) printf("*");
			else if (seq[i]==MIN_C) printf("-");
			else if (seq[i]==ADD_C) printf("+");
		}
		else if (seq[i]) printf("%d ",seq[i]);
	}
	cout<<endl;
		
	for (int i=1;i<=ptr;i++) if (seq[i]==-3)
	{
		lp=i-1; while (!seq[lp] && lp>1) lp--;
		rp=i+1; while (!seq[rp] && rp<ptr) rp++;
		seq[i]=seq[lp]*seq[rp];
		seq[lp]=seq[rp]=0;
	}
	
	for (int i=1;i<=ptr;i++)
	{
		if (seq[i]<0)
		{
			if (seq[i]==POW_C) printf("^");
			else if (seq[i]==MUL_C) printf("*");
			else if (seq[i]==MIN_C) printf("-");
			else if (seq[i]==ADD_C) printf("+");
		}
		else if (seq[i]) printf("%d ",seq[i]);
	}
	cout<<endl;
		
	for (int i=1;i<=ptr;i++) if (seq[i]==-2)
	{
		lp=i-1; while (!seq[lp] && lp>1) lp--;
		rp=i+1; while (!seq[rp] && rp<ptr) rp++;
		seq[i]=seq[lp]-seq[rp];
		seq[lp]=seq[rp]=0;
	}

	for (int i=1;i<=ptr;i++)
	{
		if (seq[i]<0)
		{
			if (seq[i]==POW_C) printf("^");
			else if (seq[i]==MUL_C) printf("*");
			else if (seq[i]==MIN_C) printf("-");
			else if (seq[i]==ADD_C) printf("+");
		}
		else if (seq[i]) printf("%d ",seq[i]);
	}
	cout<<endl;
	
	for (int i=1;i<=ptr;i++) if (seq[i]==-1)
	{
		lp=i-1; while (!seq[lp] && lp>1) lp--;
		rp=i+1; while (!seq[rp] && rp<ptr) rp++;
		seq[i]=seq[lp]+seq[rp];
		seq[lp]=seq[rp]=0;
	}

	for (int i=1;i<=ptr;i++)
	{
		if (seq[i]<0)
		{
			if (seq[i]==POW_C) printf("^");
			else if (seq[i]==MUL_C) printf("*");
			else if (seq[i]==MIN_C) printf("-");
			else if (seq[i]==ADD_C) printf("+");
		}
		else if (seq[i]) printf("%d ",seq[i]);
	}
	cout<<endl;
	
	for (int i=1;i<=ptr;i++) if (seq[i]) return seq[i];
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
	
	a_val=2;
	cout<<Get_Val(src)<<endl;
	return 0;
	
	
	readx(n);
	for (int i=1;i<=n;i++)
	{
		getline(cin,trc); trc=Erase_Spaces(trc);
		if (Judge()) printf("%c",'A'-1+i);
	}
	putchar('\n');
	return 0;
}