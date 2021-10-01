#include<bits/stdc++.h>

using namespace std;

string s[110];
string t;
int cnt;
int tax[26],num;

int lcm(int x,int y)
{
	return x*y/__gcd(x,y);
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		memset(tax,0,sizeof(tax));
		num=cnt=0;
		t="";
		
		int n;
		cin>>n;
		int siz=1;
		for(int i=1;i<=n;i++)
		{
			cin>>s[i];
			siz=lcm(siz,(int)s[i].size());
		}
		for(int i=1;i<=n;i++)
		{
			int len=s[i].size();
			for(int j=0;j<len;j++)
			{
				if(!tax[s[i][j]-'a']) cnt++;
				tax[s[i][j]-'a']++;
			}
		}
		for(int j=0;j<siz;j++)
		{
			for(int i=1;i<=n;i++)
			{
				t+=s[i][j%s[i].size()];
			}
		}
		t+=t;
		// cout<<t<<'\n';
		// cout<<cnt<<'\n';
		memset(tax,0,sizeof(tax));
		int len=t.size();
		int r=0;
		int ans=0x7f7f7f7f;
		for(int i=0;i<len;i++)
		{
			tax[t[i]-'a']++;
			if(tax[t[i]-'a']==1) num++;
			while(num==cnt)
			{
				tax[t[r]-'a']--;
				if(!tax[t[r]-'a']) num--;
				r++;
			}
			if(r)
			{
				r--;
				if(!tax[t[r]-'a']) num++;
				tax[t[r]-'a']++;
			}
			if(num==cnt&&r!=0) ans=min(ans,i-r+1);
		}
		cout<<ans<<'\n';
	}
}