#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<ctime>
#include<vector>
#include<cstdlib>
#include<algorithm>
typedef long long ll;
using namespace std;

int n,q;

int main()
{
	freopen("dat.in","w",stdout);
	srand(time(0));
	
	scanf("%d%d",&n,&q);
	
	printf("%d %d\n",n,q);
	for (int i=2;i<=n;i++)
		printf("%d %d\n",rand()%(i-1)+1,i);
	
	for (int i=1;i<=q;i++)
	{
		printf(rand()%2 ? "C" : "Q");
		printf(" %d\n",rand()%n+1);
	}
}