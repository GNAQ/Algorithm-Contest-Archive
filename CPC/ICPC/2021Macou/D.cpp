#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <vector>
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

string hp="HP+", ATK="ATK+", ATK_R="ATK Rate+", DEF="DEF+", DEF_R="DEF_Rate+",
	phy="Physical DMG Rate+", elm="Elemental DMG Rate+", elm_m="Elemental Mastery+",
	chrg="Energy Recharge Rate+", crit="Crit Rate+", crit_d="Crit DMG Rate+", 
	heal="Healing Bonus Rate+";

double _atk = 1500.00, _atk_r = 0, _crit=0.0500, _crit_d=0.5000, _atk_d = 0;

bool OK(char ch)
{
	if (ch!='.' && (ch<'0' || ch>'9')) 
		return false;
	return true;
}

double GetNum(string &s, int pos)
{
	double ret = 0; int flag = 0;
	for (int i=pos;OK(s[i]) && i < s.size();i++)
	{
		if (s[i]=='.')
		{
			flag = 1;
			continue;
		}
		else
		{
			if (!flag)
			{
				ret = ret * 10 + s[i]-'0';
			}
			else
			{
				ret = ret + (s[i]-'0') * pow(0.1, flag);
				flag++;
			}
		}
	}
	return ret;
}

int main()
{
	string s;
	for (int i=1;i<=25;i++)
	{
		getline(cin, s);
		
		// cerr << "!!" << s << endl;
		
		if (s.find(ATK_R)!=s.npos) // 大攻击
		{
			_atk_r += GetNum(s, ATK_R.size()) * 0.01;
		}
		else if (s.find(ATK)!=s.npos) // 小攻击
		{
			_atk_d += GetNum(s, ATK.size());
		}
		else if (s.find(crit)!=s.npos) // 暴击
		{
			_crit += GetNum(s, crit.size()) * 0.01;
		}
		else if (s.find(crit_d)!=s.npos) // 爆伤
		{
			_crit_d += GetNum(s, crit_d.size()) * 0.01;
		}
	}
	
	if (_crit > 1.0) _crit = 1.0;
	
	_atk = _atk * (1.0 + _atk_r) + _atk_d;
	
	printf("%.12lf\n", _atk * (1.0 - _crit) + _atk * _crit * (1.0 + _crit_d));
	return 0;
} 