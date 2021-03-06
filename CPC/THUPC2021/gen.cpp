#include<bits/stdc++.h>
using namespace std;


int main()
{
	srand(time(NULL));
	
	freopen("in.in","w",stdout);
	
	int n=rand()%7+1;
	if (n%2==0) n++;
	int m=rand()%9+1;
	
	printf("%d %d\n", n, m);
	for (int i=1;i<=m;i++)
	{
		int tmp=rand()%(n/2+2);
		printf("%d%c", tmp, " \n"[i==m]);
	}
}