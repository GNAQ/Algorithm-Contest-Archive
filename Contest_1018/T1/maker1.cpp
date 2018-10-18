#include<bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
	freopen("data.in","w",stdout);
	srand(time(0));
	
	int n=abs(rand())%1000+1;
	printf("%d\n",n);
	for (int i=1;i<=n;i++)
		printf("%d%c",abs(rand())%100+2," \n"[i==n]);
}