#include<bits/stdc++.h>
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

int n;

int sec[500010];
int tax[500010];
bitset<500010>s;
bitset<500010>t,tt;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>sec[i];
		s[sec[i]]=1;
	}
	sort(sec+1,sec+n+1);
	
	int mmax=sec[n], mmin=sec[1];
	int ttans = mmax - mmin + 1;
	cout << "!!!\t" << ttans << endl;
	
	if(n<=sqrt(500000))
	//if(n<=0)
	{
		for(int i=n;i<=sec[n]-sec[1]+1;i++)
		{
			bool fg=0;
			for(int j=1;j<=n;j++)
			{
				tax[sec[j]%i]++;
				if(tax[sec[j]%i]>=2)
				{
					fg=1;
				}
			}
			if(!fg)
			{
				cout<<i<<'\n';
				return 0;	
			}
			for(int j=1;j<=n;j++)
			{
				tax[sec[j]%i]--;
			}
		}
	}
	else
	{
		for(int i=n;i<=sec[n]-sec[1]+1;i++)
		{
			tt=t=s;
			tt>>=i;
			bool fg=0;
			while(tt.any())
			{
				if((t&tt).any())
				{
					fg=1;
					break;
				}
				tt>>=i;
			}
			if(!fg) 
			{
				cout<<i<<'\n';
				return 0;
			}
		}
	}
	
	
}