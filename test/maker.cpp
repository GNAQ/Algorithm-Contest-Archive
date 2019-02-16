#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<random>
typedef long long ll;
using namespace std;

random_device rand_dev;
mt19937 rand_gen(rand_dev());
uniform_int_distribution<unsigned long long> rand_distrib(1,1000000000000000000LL);//1e18

int main()
{
	freopen("dat.in","w",stdout);
	printf("100000 1000000009\n");
	
	for (int i=1;i<=100000;i++) 
		printf("%llu%c",rand_distrib(rand_gen)," \n"[i==100000]);
	
}