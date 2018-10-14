#include<bits/stdc++.h>
#define ll long long
using namespace std;

bool used[110][110];

const int mod=20;

int main()
{
	freopen("t1.in","w",stdout);
	srand(time(0));
	
	int n,m,K;
	n=abs(rand())%mod+2;
	m=abs(rand())%mod+2;
	K=abs(rand())%6+1;
	// K=(abs(rand())%(n*m-2))+1;
	
	printf("%d %d %d\n",n,m,K);
	
	used[1][1]=used[n][m]=1;
	int tmp_x,tmp_y;
	for (int i=1;i<=K;i++)
	{
		tmp_x=abs(rand())%n+1;
		tmp_y=abs(rand())%m+1;
		while (used[tmp_x][tmp_y]) 
		{
			tmp_x=abs(rand())%m+1;
			tmp_y=abs(rand())%n+1;
		}
		used[tmp_x][tmp_y]=1;
		printf("%d %d\n",tmp_x,tmp_y);
	}
	
	return 0;
}