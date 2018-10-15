#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<iterator>
#include<algorithm>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

string key,code;
int klen,clen;
int k[1010],c[1010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}



int main()
{
	getline(cin,key); getline(cin,code);
	klen=key.length(); clen=code.length();
	
	int pos=0;
	for (int i=0;i<clen;i++)
	{
		code[i]=(+26)%26;
	}
	
	
	
}