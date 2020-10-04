#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;

ll x,y;
char z[1000100];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

struct Bignum
{
		friend ostream &operator << (ostream &out, const Bignum &x);
	/*------构造、赋值等--------*/
	Bignum(const ll &x) { *this = x; }
	Bignum(const Bignum &b, bool sign)
	{
		*this = b;
		this->sign = sign;
	}
	Bignum(const Bignum &b) { *this = b; }
	Bignum()
	{
		num.clear();
		sign = 0;
	}
	Bignum operator = (int x)
	{
		num.clear();
		sign = (x < 0 ? (x = -x), 1 : 0);
		num.push_back(x % mod);
		x /= mod;
		if (x)
			num.push_back(x);
		return *this;
	}
	Bignum operator = (ll x)
	{
		num.clear();
		if (x < 0)
		{
			sign = 1;
			x = -x;
		}
		else
			sign = 0;
		while (x >= mod)
		{
			num.push_back(x % mod);
			x /= mod;
		}
		num.push_back(x);
		return *this;
	}
	Bignum operator = (const string &str)
	{
		num.clear();
		int i = str.size();
		if (str[0] == '-')
		{
			sign = 1;
		}
		else
			sign = 0;
		while (i - sign >= width)
		{
			int x = 0;
			for (int j = i - width; j < i; j++)
			{
				x = x * 10 + (str[j] - '0');
			}
			num.push_back(x);
			i -= width;
		}
		if (i - sign)
		{
			int x = 0;
			for (int j = sign; j < i; j++)
			{
				x = x * 10 + (str[j] - '0');
			}
			num.push_back(x);
		}
		return *this;
	}
	/*------关于大小的比较------*/
	bool operator < (const Bignum &b) const
	{
		if (sign ^ b.sign)
			return sign;
		int size1 = num.size(), size2 = b.num.size();
		if (size1 == size2)
		{
			for (int i = size1 - 1; i >= 0; i--)
			{
				if (num[i] != b.num[i])
					return (num[i] < b.num[i]) ^ sign;
			}
		}
		return (size1 < size2) ^ sign;
	}
	bool operator > (const Bignum &b) const { return b < *this; }
	bool operator == (const Bignum &b) const { return !(*this < b || *this > b); }
	bool operator <= (const Bignum &b) const { return !(*this > b); }
	bool operator >= (const Bignum &b) const { return !(*this < b); }
	bool operator != (const Bignum &b) const { return *this < b || *this > b; }
	/*------加减乘除膜------------*/
	Bignum operator + (const Bignum &b) const
	{
		if ((sign & b.sign) || !(sign | b.sign))
		{
			return Bignum(add(b), sign & b.sign);
		}
		else if (!sign)
		{
			return sub(b);
		}
		else
		{
			return b.sub(*this);
		}
	}
	Bignum operator - (const Bignum &b) const
	{
		if ((sign & b.sign) || !(sign | b.sign))
		{
			Bignum c = sub(b);
			c.sign = ((c.num.size() == 1 && !c.num[0]) ? 0 : (c.sign ^ (sign & b.sign)));
			return c;
		}
		else if (!sign)
		{
			return add(b);
		}
		else
		{
			return Bignum(add(b), 1);
		}
	}
	Bignum operator * (int x)
	{
		return mul(x);
	}
	Bignum operator / (int x)
	{
		return div(x, 0);
	}
	Bignum operator % (int x)
	{
		return div(x, 1);
	}
	Bignum operator * (const Bignum &b) const
	{
		return mul(b);
	}
	/*------+=等----------------*/
	Bignum operator += (const Bignum &b)
	{
		return *this = *this + b;
	}
	Bignum operator -= (const Bignum &b)
	{
		return *this = *this - b;
	}
	Bignum operator *= (int b)
	{
		return *this = *this * b;
	}
	Bignum operator /= (int b)
	{
		return *this = *this / b;
	}
	Bignum operator %= (int b)
	{
		return *this = *this % b;
	}
	Bignum operator *= (const Bignum &b)
	{
		return *this = *this * b;
	}
	/*------变量----------------*/
		static const int mod = 100000000;
	static const int width = 8;
	vector<ll> num;
	bool sign;
	/*------输出----------------*/
	void print() const
	{
		if (sign)
			putchar('-');
		int size = num.size() - 1;
		printf("%lld", num[size]);
		for (int i = size - 1; i >= 0; --i)
		{
			printf("%08lld", num[i]);
		}
		putchar('\n');
	}
	/*------计算----------------*/
	Bignum add(const Bignum &b) const
	{
		Bignum c;
		int last = 0, sizea = num.size();
		int sizeb = b.num.size();
		int size = max(sizea, sizeb);
		for (int i = 0; i < size; ++i)
		{
			int x = last;
			if (i < sizea)
				x += num[i];
			if (i < sizeb)
				x += b.num[i];
			last = x / mod;
			c.num.push_back(x % mod);
		}
		return c;
	}
	Bignum sub(const Bignum &b) const
	{
		Bignum c;
		Bignum const *d;
		if (*this > b)
		{
			c = *this;
			c.sign = 0;
			d = &b;
		}
		else
		{
			c = b;
			c.sign = 1;
			d = this;
		}
		int size = c.num.size(), sized = d->num.size();
		for (int i = 0; i < sized; ++i)
		{
			c.num[i] -= d->num[i];
			if (c.num[i] < 0)
			{
				c.num[i] += mod;
				--c.num[i + 1];
			}
		}
		while (!c.num[size - 1] && size > 1)
			--size;
		c.num.resize(size);
		if (size == 1 && c.num[0] == 0)
			c.sign = 0;
		return c;
	}
	Bignum mul(int x)
	{
		Bignum c;
		c.sign = sign ^ (x < 0);
		if (x < 0)
			x = -x;
		int size = num.size();
		ll last = 0;
		for (int i = 0; i < size; ++i)
		{
			c.num.push_back((last + x * num[i]) % mod);
			last = (last + x * num[i]) / mod;
		}
		while (last)
		{
			c.num.push_back(last % mod);
			last /= mod;
		}
		return c;
	}
	Bignum div(int x, bool flag)
	{
		Bignum c;
		c.sign = sign ^ (x < 0);
		if (x < 0)
			x = -x;
		int size = num.size();
		c.num.resize(size);
		ll last = 0;
		for (int i = size - 1; i >= 0; --i)
		{
			last = last * mod + num[i];
			if (last >= x)
			{
				c.num[i] = last / x;
				last %= x;
			}
		}
		while (c.num[size - 1] == 0 && size > 1)
		{
			--size;
		}
		c.num.resize(size);
		return (flag == 0 ? c : Bignum(last * (sign ? -1 : 1)));
	}
	Bignum mul(const Bignum &b) const
	{
		int size1 = num.size(), size2 = b.num.size(), csize = size1 + size2 + 2;
		Bignum c;
		c.num.resize(csize + 1, 0);
		c.sign = (sign ^ b.sign);
		for (int i = 0; i < size1; ++i)
		{
			for (int j = 0; j < size2; ++j)
			{
				c.num[i + j] += num[i] * b.num[j];
			}
		}
		for (int i = 0; i < csize; ++i)
		{
			if (c.num[i] >= mod)
			{
				c.num[i + 1] += c.num[i] / mod;
				c.num[i] %= mod;
			}
		}
		while (!c.num[csize] && csize > 0)
			--csize;
		c.num.resize(csize + 1);
		return c;
	}
	
	ll to_int()
	{
		ll ret = 0, k = 1;
		if (sign)
			k=-1;
		int size = num.size() - 1;
		for (int i=size;i>=0;i--)
		{
			ret+=num[i];
			if (i>0) ret*=width;
		}
		return ret*k;
	}
};

int GetVal(char ch)
{
	if (ch>='0' && ch<='9') return ch-'0';
	if (ch>='A' && ch<='Z') return ch-'A'+10;
	if (ch>='a' && ch<='z') return ch-'a'+36;
	return -2*1e9;
}

char GetChr(int val)
{
	if (val>=0 && val<=9) return val+'0';
	if (val>=10 && val<=35) return val-10+'A';
	if (val>=36 && val<=61) return val-36+'a';
	return '$';
}

Bignum aa=0,ppow=1;
vector<char> ans;

int main()
{
	readx(x); readx(y);
	scanf("%s",z+1);
	int lz=strlen(z+1);
	if (z[1]=='0')
	{
		printf("0\n");
		return 0;
	}
	
	Bignum yy=y, tt, zero = 0, xx=x;
	
		for (int i=1;i<=lz;i++)
	{
		aa*=xx;
		aa+=GetVal(z[i]);
	}
		
	while (aa>=yy)
	{
		tt = aa % y;
		aa = aa / y;
		ans.push_back(GetChr(tt.to_int()));
	}
	if (aa > zero) 
	{
		ans.push_back(GetChr(aa.to_int()));
	}
	
	int lim = ans.size()-1;
	for (int i=lim;i>=0;i--) printf("%c",ans[i]);
	printf("\n");
}