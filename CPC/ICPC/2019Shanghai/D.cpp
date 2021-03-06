#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    int T;cin>>T;
    for(int ii=1;ii<=T;ii++)
    {
        int n;cin>>n;
        printf("Case #%d: %d\n",ii,n/2);
        for(int I=1;I<=n/2;I++)
        {
            int pos=I,f=1,step=1;
            for(int i=1;i<=n-1;i++)
            {
                int to=pos+f*step;
                if(to>n) to-=n;
                if(to<=0) to+=n;
                printf("%d %d\n",pos,to);
                f*=-1;step++;
                pos=to;
            }
        }
    }
}