#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;

long N,pnumbers[100000000]={0},countx=0;
bool nnumbers[100000000];

void PrimeNum(int upat)
{
	memset(nnumbers,1,sizeof(nnumbers));
	nnumbers[0]=false; nnumbers[1]=false;
	upat=sqrt(upat)+1;
	for (int i=0;i<=upat;i++) if (nnumbers[i]==true) for (int j=2;j<=N && i*j<=N;j++) nnumbers[i*j]=false;
	for (int i=0;i<=N;i++) if (nnumbers[i]==true)
	{
		pnumbers[countx]=i;
		countx++;
	}
}

int main()
{
	
	scanf("%ld",&N);
	PrimeNum(N);
	for (int i=1;i<countx;i++) printf("%ld ",pnumbers[i]);
	return 0;
}
