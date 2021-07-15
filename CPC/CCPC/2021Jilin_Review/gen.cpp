#include<bits/stdc++.h>
using namespace std;


int main()
{
	srand(time(NULL));
	freopen("in.in","w", stdout);
	
	puts("5");
	for (int w=1;w<=5;w++)
	{
		int n = 100000;
		printf("%d\n", n);
		for (int i=1;i<=n;i++) printf("%d%c", rand(), " \n"[i==n]);
		
	}
}