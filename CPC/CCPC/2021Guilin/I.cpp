#include <bits/stdc++.h>
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

string s;

int main()
{
	int T;
	cin>>T;
	while (T--)
	{
		int n;
		cin>>n;
		cin>>s;
		s="@"+s;
		int cnt=0;
		long long ans=0;
		for(int i=n;i>=1;i--)
		{
			if(cnt==0||s[i]=='0') cnt++;
			else
			{
				cnt--;
				ans+=i;
			}
		}
		cout<<ans<<"\n";
	}
	
	
}