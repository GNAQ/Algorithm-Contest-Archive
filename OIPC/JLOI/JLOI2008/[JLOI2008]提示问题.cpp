#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;

char chs[100]={0},cac[100];
int len=0;
char qaq[11]="aeiouAEIOU";

inline void output(){ for (int i=1;i<=len;i++) printf("%c",cac[i]); putchar('\n'); }
int main()
{
    cin.getline(chs+1,99);
    len=strlen(chs+1);
    
    memcpy(cac,chs,sizeof chs); double wnum=0.0;
    for (int i=1;i<=len;i++) if ((cac[i]>='A' && cac[i]<='Z') || (cac[i]>='a' && cac[i]<='z')) 
        { cac[i]='.'; wnum++; }
    output();
    
    memcpy(cac,chs,sizeof chs); int upat=round(wnum/3.0); double onion=0.0;
    for (int i=1;i<=len;i++) if ((cac[i]>='A' && cac[i]<='Z') || (cac[i]>='a' && cac[i]<='z')) 
    {
        if (upat) upat--;
        else cac[i]='.';
    }
    for (int i=1;i<=len;i++) if (cac[i]=='.') for (int w=0;w<=9;w++) if (chs[i]==qaq[w]) onion++;
    output();
    
    if (onion==0.0)
    {
        memcpy(cac,chs,sizeof chs); upat=round(wnum*(2.0/3.0));
        for (int i=1;i<=len;i++) if ((cac[i]>='A' && cac[i]<='Z') || (cac[i]>='a' && cac[i]<='z')) 
        {
            if (upat) upat--;
            else cac[i]='.';
        }
    }
    else for (int i=1;i<=len;i++) for (int w=0;w<=9;w++) if (chs[i]==qaq[w]) cac[i]=chs[i];
    output();
}