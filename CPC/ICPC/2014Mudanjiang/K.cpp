#include<iostream>
#include<string.h>
#include<cstring>
#include<cstdio>
using namespace std;
string s;
int main()
{
	int T;cin>>T;
	while(T--)
	{
		cin>>s;
		int n=s.size(),num=0,ans=0;
		for(int i=0;i<=n-1;i++)
			if(s[i]=='*') num--;
			else num++;
		if(num<1) ans+=1-num;
		num=max(1-num,0);
		for(int i=0;i<=n-1;i++)
		{
			if(s[i]=='*')
				num--;
			else num++;
			if(num<1)
			{
				for(int j=n-1;j>=i;j--)
					if(s[j]!='*')
					{
						swap(s[i],s[j]);
						ans++;break;
					}
				num+=2;
			}
		}
		cout<<ans<<endl;
	}
}