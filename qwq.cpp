#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
#include<queue>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<iterator>
#define ll long long 
using namespace std;

int n,k,t;
int seq[100010];

template<typename int_t>
void readx(int_t& x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}



int main()
{
    readx(t); 
    while (t--)
    {
        readx(n); readx(k);
        for (int i=1;i<=n;i++) readx(seq[i]);
        
        int ans=0;
        for (int i=1;i<=n;i++)
        {
            
        }
    }
    
    
}