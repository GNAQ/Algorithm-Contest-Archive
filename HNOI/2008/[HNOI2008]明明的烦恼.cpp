#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

int n,seq[3010],tmp;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

struct BNUM
{
	int len,a[5010];
	
	BNUM(){ memset(a,0,sizeof a); len=0; }
	
	void Output()
	{
		if (!len) { putchar('0'); putchar('\n'); return; }
		while (!a[5000-len+1] && len>1) len--;
		for (int i=5000-len+1;i<=5000;i++) putchar(a[i]+'0'); putchar('\n');
	}
	
	void InputNum(ll qwq)
	{
		if (!qwq) { len=1; a[5000]=0; return; }
		while (qwq)
		{
			a[5000-len]=qwq%10;
			qwq/=10; len++;
		}
	}
	
	BNUM operator + (const BNUM& B)
	{
		BNUM C;
		C.len=max(len,B.len);
		for (int i=5000;i>5000-C.len;i--)
		{
			C.a[i]+=a[i]+B.a[i];
			if (C.a[i]>9) { C.a[i]-=10; C.a[i-1]++; }
		}
		if (C.a[5000-C.len]) C.len++;
		return C;
	}
	
	BNUM operator * (const BNUM& B)
	{
		BNUM C;
		C.len=len+B.len;
		for (int i=5000;i>5000-B.len;i--)
			for (int j=5000;j>5000-len;j--)
			{
				C.a[i+j-5000]+=a[j]*B.a[i];
				if (C.a[i+j-5000]>9)
				{
					C.a[i+j-5001]+=C.a[i+j-5000]/10;
					C.a[i+j-5000]%=10;
				}
			}
		while (!C.a[5001-C.len]) C.len--;
		return C;
	}
	
	BNUM operator / (const int& val)
	{
		BNUM C; int ret=0;
		C.len=len;
		for (int i=5001-len;i<=5000;i++)
		{
			ret=ret*10+a[i];
			C.a[i]=ret/val;
			ret%=val;
		}
		while (!C.a[5001-C.len]) C.len--;
		return C;
	}
};

BNUM fastpow(BNUM an,ll p)
{
	BNUM ret; ret.InputNum(1);
	for (;p;p>>=1,an=an*an) if (p&1) ret=ret*an;
	return ret;
}

int main()
{
	readx(n);
	for (int i=1;i<=n;i++) 
	{
		readx(seq[i]);
		if (!seq[i]) { printf("0\n"); return 0; }
	}
	
	int cnt=0,sum=0; 
	for (int i=1;i<=n;i++) if (seq[i]>0) 
	{
		cnt++;
		sum+=seq[i]-1;
	}
	if (sum>2*n-2) { printf("0\n"); return 0; }
	
	BNUM ans; ans.InputNum(1);
	for (int i=n-2-sum+1;i<=n-2;i++) 
	{
		BNUM Btmp; Btmp.InputNum(i);
		ans=ans*Btmp;
	}
	BNUM Btmp; Btmp.InputNum(n-cnt);
	ans=ans*fastpow(Btmp,n-2-sum);
	
	for (int i=1;i<=n;i++)
		for (int j=2;j<=seq[i]-1;j++) ans=ans/j;
	
	ans.Output();
}
