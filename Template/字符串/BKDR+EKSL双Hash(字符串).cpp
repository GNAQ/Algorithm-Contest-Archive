#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#define Xnum 3131313
#define Xnum2 378551
#define XMod 9673131
using namespace std;

bool h[2][10000000]={0};//Hash Table 
char str[1600]={0};//Input String 
int n,ans=0;

unsigned long long EKSLHash(char strx[])//基于字符位置的Hash 
{
    unsigned long long x=0,a=63689;
    for (int i=0;i<strlen(strx);i++)
    {
        x=x*a+strx[i]*i;
        a+=Xnum2;
    }
    return x&0x7FFFFFFF;
}

unsigned long long BKDRHash(char strx[])//基于字符串整体的雪崩效应Hash 
{
    unsigned long long x=0;
    for (int i=0;i<strlen(strx);i++) 
    {
        x=x*Xnum+strx[i];
    }
    return x&0x7FFFFFFF;
}

void InsertHashTable(int n)//插入Hash表 
{
	unsigned long long hash,hash2;
	for (int i=0;i<n;i++)
    {
        scanf("%s",str);
        hash=EKSLHash(str)%Xnum;
        hash2=BKDRHash(str)%XMod;
        cout<<hash<<endl;
        cout<<hash2<<endl;
        if (h[0][hash]==0 || h[1][hash2]==0) //双Hash判重 
        {
            ans++;
            h[0][hash]=1; h[1][hash2]=1;
        }
    }
    return;
}

int main()
{
    scanf("%d",&n);
    InsertHashTable(n);
    cout<<ans<<endl;
    return 0;
}
