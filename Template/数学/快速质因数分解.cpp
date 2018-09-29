#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<iterator>
using namespace std;

int n,n1,upat;

int main()
{
	scanf("%d",&n);
	upat=sqrt(n)+1;
	n1=n;
	for (int i=2;i<=upat;i++)
	{
		while (n1%i==0)
		{
			printf("%d ",i);
			n1=n1/i;
			upat=sqrt(n1)+1;
		}
	}
	if (n1!=0 && n1!=1) printf("%d\n",n1);
	return 0;
}
