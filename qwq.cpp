#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<vector>
#include<queue>
#include<map>
#include<set>
#define ll long long
using namespace std;

int n;

template<typename int_t>
void readx(int_t& x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

struct BNUM
{
    int len,a[10010];
    
    void readstr(char* chr)
    {
        len=strlen(chr+1);
        for (int i=1;i<=len;i++) a[10000-len+i]=chr[i]-'0';
    }
    void Output()
    {
        if (!len) { printf("0\n"); return; }
        while (!a[10000-len+1] && len>1) len--;
        for (int i=10000-len+1;i<=10000;i++) printf("%d",a[i]);
        printf("\n"); return;
    }
    
    
};

int main()
{
    readx(n);
    
    
    
}