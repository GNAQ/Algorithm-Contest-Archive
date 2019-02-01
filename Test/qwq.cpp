#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>
#include<random>
#include<vector>
typedef long long ll;
using namespace std;

double a,b,p,q;
int t;

mt19937 rand_seed;
uniform_real_distribution<double> rand_dev(0.0,1.0);

int GetStep()
{
	int ret=t+1;
	for (int i=1;i<=t;i++)
	{
		double find=rand_dev(rand_seed);
		double cat=rand_dev(rand_seed);
		if (find<0.5) 
		{
			if (cat<=a)
			{
				ret=i;
				break;
			}
		}
		else
		{
			if (cat<=b) 
			{
				ret=i;
				break;
			}
		}
	}
	
	
	return t+1;
}

int main()
{
	rand_seed.seed(std::random_device()());
	
	int times;
	scanf("%d",&times);
	
	scanf("%d",&t);
	scanf("%lf%lf%lf",&p,&a,&b);
	q=1-p;
	
	double ans=0;
	for (int i=1;i<times;i++) ans=ans+(double)GetStep()/times;
	
	printf("%.5lf\n",ans);
	
}