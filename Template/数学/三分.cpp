#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<queue>
#include<iterator>
#include<vector>
#include<map>
#include<set>
#define ll long long
#define eps 1e-6
using namespace std;

double coe[20]={0},L,R;
int N;

inline double f(double x)
{
    double sum=0;
    for (int i=N;i>=0;i--) sum=sum*x+coe[i];
    return sum;
}

inline double TriSearch(double l,double r)
{
    register double k,ml,mr;
    while (l+eps<=r)
    {
        k=(r-l)/3.0;
        ml=l+k; mr=r-k;
        if (f(ml)<f(mr)) l=ml;
        else r=mr;
    }
    return l;
}

int main()
{
    scanf("%d%lf%lf",&N,&L,&R);
    for (int i=N;i>=0;i--) scanf("%lf",&coe[i]);
    printf("%.5lf\n",TriSearch(L,R));
}
