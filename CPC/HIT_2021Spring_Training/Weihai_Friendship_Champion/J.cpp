#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
typedef long long ll;
using namespace std;

int main()
{
	int T;cin>>T;
	while(T--)
	{
		int a,b,c,k;
		cin>>a>>b>>c>>k;
		for(int i=1;i<=k;i++)
		{
			if(a>b) a-=b;
			if(b>c) b-=c;
			if(c>a) c-=a;
			if(a==b&&a==c)
				break;
		}
		cout<<a<<" "<<b<<" "<<c<<endl;
	}
}