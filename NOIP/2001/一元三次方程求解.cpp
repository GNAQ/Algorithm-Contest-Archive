// luogu-judger-enable-o2
#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

double A,B,C,D;
const double eps=1e-8;

template<typename int_t>
void readx(int_t& x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

double F(double X)
{
    return A*X*X*X+B*X*X+C*X+D;
}

double BS(int _pos)
{
    double l=_pos,r=_pos+1;
    for (int tim=1;tim<=30;tim++)
    {
        double mid=(l+r)/2;
        if (F(mid)*F(r)<0) l=mid;
        else r=mid;
    }
    return l;
}

int main()
{
    scanf("%lf%lf%lf%lf",&A,&B,&C,&D);
    
    for (int i=-100;i<=99;i++)
    {
        if (fabs(F(i))<eps) printf("%.2lf ",(double)i);
        else if (F(i)*F(i+1.0)<0)
        {
            double tmp=BS(i);
            if (fabs(tmp-i-1.0)<0.01) continue;
            printf("%.2lf ",tmp);
        }
    }
    putchar('\n');
    return 0;
}
