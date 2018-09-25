#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

int main()
{
	char afx[200]={0};
	string innumber;
	long long xten=0,lenin,inbin,tobin,xcount=0;
	scanf("%lld",&inbin);
	cin>>innumber;
	scanf("%lld",&tobin);
	lenin=innumber.length();
	
	for (int i=0;i<lenin;i++)
	{
		if (innumber[i]>'9') innumber[i]-=7;
		xten+=(innumber[i]-48)*(pow(inbin,lenin-i-1));
	}
	while (xten>0)
	{
		afx[xcount]=(xten%tobin)+48;
		xcount++;
		xten=xten/tobin;
	}
	for (int i=xcount-1;i>=0;i--)
	{
		if (afx[i]>'9') afx[i]+=7;
		printf("%c",afx[i]);
	}
	return 0;
}
