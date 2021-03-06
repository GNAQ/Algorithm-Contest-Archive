#include<bits/stdc++.h>

using namespace std;

int result[100];

int get(int l,int r,int nl,int nr)
{
	if (l<=nl && r>=nr) 
	{
		printf("RET [%d %d]\n", nl, nr);
		return 1;
	}
	int mid = (nl+nr)/2;
	int ret = 0;
	if (l<=mid) ret+=get(l,r,nl,mid);
	if (r>mid) ret+=get(l,r,mid+1,nr); 
	return ret;
}

int calc(int n)
{
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			printf("Get [%d, %d]\n", i, j);
			sum+=get(i,j,1,n);
			system("pause");
		}
	}
	return sum;
}

int main()
{
	// cin>>n;
	for (int n=2;n<=20;n++) 
	{
		result[n]=calc(n);
		printf("\n\n\n");
		
	}
	
	for (int i=1;i<=20;i++)
		printf("{%d} %d |%d|\n", i, result[i], result[i]-result[i-1]);
	
	
	return 0;
}