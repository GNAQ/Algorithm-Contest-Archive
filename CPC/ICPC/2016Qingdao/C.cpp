#include<bits/stdc++.h>

using namespace std;

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		double a,b;
		cin>>a>>b;
		cout<<log2(a/b)<<'\n';
	}
}