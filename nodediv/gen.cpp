#include<bits/stdc++.h>

using namespace std;


int main()
{
	freopen("in.in", "w", stdout);
	srand(time(0));
	
	int n = 7, m = 6;
	
	printf("%d %d\n", n, m);
	
	for (int i=1;i<=n;i++) printf("%d%c", rand()%50+1, " \n"[i==n]);
	
	for (int i=2;i<=n;i++) 
	{
		printf("%d %d\n", rand()%(i-1)+1, i);
	}
	
	for (int i=1;i<=m;i++)
	{
		if (rand()&1)
		{
			printf("0 %d %d\n", rand()%n+1, rand()%(n/2)+1);
		}
		else
		{
			printf("1 %d %d\n", rand()%n+1, rand()%50+1);
		}
	}
}