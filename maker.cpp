#include<bits/stdc++.h>
using namespace std;



int main()
{
	srand(time(0));
	freopen("dat.in","w",stdout);
	int n=10,m=4;
	
	printf("%d %d\n",n,m);
	for (int i=1;i<=n;i++)
	{
		if (rand()%2 || rand()%2) printf("%c",'0'+rand()%2);
		else printf(".");
	}
	cout<<endl;
	
	for (int i=1;i<=m;i++)
	{
		int len=rand()%4+1;
		for (int j=1;j<=len;j++) printf("%c",'0'+rand()%2);
		printf(" %d\n",rand());
	}
	
	
}
