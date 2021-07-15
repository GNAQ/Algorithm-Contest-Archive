#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<set>

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

set<int>s;

int main()
{
	int n;
	readx(n);
	while("GNAQAKWF")
	{
		s.insert(n);
		int sum=0;
		while(n)
		{
			int tmp=n%10;
			sum+=tmp*tmp;
			n/=10;			
		}
		if(s.find(sum)!=s.end()) 
		{
			cout<<"UNHAPPY\n";
			return 0;
		} 
		else if (sum==1)
		{
			cout<<"HAPPY\n";
			return 0;
		}
		else
		{
			n=sum;
		}
		
	}
}