#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<ctime>
#define ll long long
using namespace std;

string src,trc,ans_s;
int n,a_val;
ll vals[10],as[10];

const long long ADD_C=-2000000000000000;
const long long MIN_C=-2000000000000001;
const long long MUL_C=-2000000000000002;
const long long POW_C=-2000000000000003;
const long long mod=998244353LL;

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
	for (;p;p>>=1,an=(an*an)%mod) if (p&1) ret=(ret*an)%mod;
	return ret;
}

ll Get_Val(string input_str)
{
	int len=input_str.length()-1; ll cac=0;
	ll seq[50],ptr=0; memset(seq,0,sizeof seq);
	
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
		else if (input_str[i]=='+') seq[++ptr]=ADD_C;
		else if (input_str[i]=='-') seq[++ptr]=MIN_C;
		else if (input_str[i]=='*') seq[++ptr]=MUL_C;
		else if (input_str[i]=='^') seq[++ptr]=POW_C;
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
	
	int lp,rp;
	for (int i=1;i<=ptr;i++) if (seq[i]==POW_C)
	{
		lp=i-1; while (!seq[lp] && lp>1) lp--;
		rp=i+1; while (!seq[rp] && rp<ptr) rp++;
		if (seq[lp]<=ADD_C) lp++;
		if (seq[rp]<=ADD_C) rp--;
		seq[i]=fastpow(seq[lp],seq[rp]);
		seq[lp]=seq[rp]=0;
	}
	for (int i=1;i<=ptr;i++) if (seq[i]==MUL_C)
	{
		lp=i-1; while (!seq[lp] && lp>1) lp--;
		rp=i+1; while (!seq[rp] && rp<ptr) rp++;
		if (seq[lp]<=ADD_C) lp++;
		if (seq[rp]<=ADD_C) rp--;
		seq[i]=(seq[lp]*seq[rp])%mod;
		seq[lp]=seq[rp]=0;
	}
	for (int i=1;i<=ptr;i++) if (seq[i]==MIN_C)
	{
		lp=i-1; while (!seq[lp] && lp>1) lp--;
		rp=i+1; while (!seq[rp] && rp<ptr) rp++;
		if (seq[lp]<=ADD_C) lp++;
		if (seq[rp]<=ADD_C) rp--;
		seq[i]=(seq[lp]-seq[rp])%mod;
		seq[lp]=seq[rp]=0;
	}
	for (int i=1;i<=ptr;i++) if (seq[i]==ADD_C)
	{
		lp=i-1; while (!seq[lp] && lp>1) lp--;
		rp=i+1; while (!seq[rp] && rp<ptr) rp++;
		if (seq[lp]<=ADD_C) lp++;
		if (seq[rp]<=ADD_C) rp--;
		seq[i]=(seq[lp]+seq[rp])%mod;
		seq[lp]=seq[rp]=0;
	}
	
	for (int i=1;i<=ptr;i++) if (seq[i]) return (seq[i]%mod+mod)%mod;
	return 0;
}

string Erase_Spaces(string input_str)
{
	string ret_s;
	for (auto c:input_str)
		if (c!=' ') ret_s.push_back(c);
	return ret_s;
}

bool Legal_Expression(string input_str)
{
	int ret=0;
	for (auto c:input_str) 
	{
		if (c=='(') ret++;
		else if (c==')') ret--;
	}
	return (ret==0);
}

bool Judge()
{
	for (int i=1;i<=5;i++)
	{
		a_val=as[i];
		if (Get_Val(trc)!=vals[i]) return false;
	}
	return true;
}

int main()
{
	srand(time(0));
	getline(cin,src); src=Erase_Spaces(src);
	
	if (!Legal_Expression(src)) return 0;
	
	for (int tim=1;tim<=5;tim++)
	{
		a_val=abs(rand())%100+1;
		as[tim]=a_val;
		vals[tim]=Get_Val(src);
	}
	
	readx(n);
	for (int i=1;i<=n;i++)
	{
		getline(cin,trc); trc=Erase_Spaces(trc);
		if (!Legal_Expression(trc)) continue;
		if (Judge()) ans_s.push_back('A'-1+i);
	}
	cout<<ans_s<<endl;
	return 0;
}