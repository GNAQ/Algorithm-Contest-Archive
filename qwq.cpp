#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<queue>
#include<cstdlib>
#include<vector>
#include<string>
#include<map>
#include<set>
#define ll long long

namespace Po
{
	std::string dates[8];
	std::string guilty_s,not_s;
	
	struct Person
	{
		std::string name;
		std::vector<std::string> disc;
	};
	
	void _Init()
	{
		dates[1]="Monday"; dates[2]="Tuesday"; dates[3]="Wednesday";
		dates[4]="Thursday"; dates[5]="Friday"; dates[6]="Saturday";
		dates[7]="Sunday";
		guilty_s="guilty"; not_s="not";
	}
	
	int Get_Date(std::string input_str)
	{
		for (int i=1;i<=7;i++) if (dates[i]==input_str) return i;
		return 0;
	}
	
	int Get_Guilty(std::string input_str)
	{
		if (input_str.find(not_s)) return 0;
		if (input_str.find(guilty_s)) return 1;
		return -1;
	}
	
	std::string Get_Name(std::string input_str)
	{
		std::string ret_str;
		for (int i=0;i<input_str.length();i++)
		{
			if (input_str[i]<'A' || input_str[i]>'Z') break;
			ret_str[i]=input_str[i];
		}
		return ret_str;
	}
	
	std::string Get_Word(std::string input_str)
	{
		int pos=0,len=input_str.length(); std::string ret_str;
		for (pos=0;pos<len;pos++) if (input_str[pos]==':') break;
		for (int i=pos+2;i<len;i++) ret_str[i-pos-2]=input_str[i];
		return ret_str;
	}
	
	void Output_S(std::string input_str)
	{
		std::cout<<input_str<<std::endl;
	}
	
};

int n,m,p;

Po::Person pr[110];
std::map<std::string,int> map_n;

int sta[110];
int ans,t_p,f_p,crime,week;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool judge()
{
	//init
	int tmp=0,cod; bool tmp_f=0;
	std::string tmp_n;
	
	memset(sta,-1,sizeof sta);
	t_p=f_p=0;
	
	for (int i=1;i<=n;i++)
	{
		for (auto W:pr[i].disc)
		{
			tmp=Po::Get_Date(W);
			if (tmp)
			{
				tmp_f=(tmp==week);
				if (sta[i]==-1) sta[i]=tmp_f;
				else if (sta[i]!=tmp_f) return false;
			}
			else
			{
				tmp=Po::Get_Guilty(W);
				tmp_n=Po::Get_Name(W);
				if (tmp_n=="I") cod=i;
				else cod=map_n[tmp_n];
				
				if (tmp) // Someone is guilty
				{
					tmp_f=(crime==cod);
					if (sta[i]==-1) sta[i]=tmp_f;
					else if (sta[i]!=tmp_f) return false;
				}
				else // Someone is NOT guilty
				{
					tmp_f=(crime!=cod);
					if (sta[i]==-1) sta[i]=tmp_f;
					else if (sta[i]!=tmp_f) return false;
				}
			}
		}
	}
	
}

int main()
{
	Po::_Init();
	readx(n); readx(m); readx(p);
	for (int i=1;i<=n;i++) std::cin>>pr[i].name;
	for (int i=1;i<=n;i++) map_n[pr[i].name]=i;
	
	std::string tmp_s,tmp_n,tmp_w;
	for (int i=1;i<=p;i++)
	{
		std::cin>>tmp_s;
		tmp_n=Po::Get_Name(tmp_s);
		tmp_w=Po::Get_Word(tmp_s);
		pr[map_n[tmp_n]].disc.push_back(tmp_w);
	}
	
	for (crime=1;crime<=n;crime++)
	{
		for (week=1;week<=7;week++)
		{
			judge();
		}
	}
	
}
