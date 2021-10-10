//D2 A
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int a,b,n;
    cin>>b>>a>>n;
    int la=0,lb=0;
    int ra=a,rb=b;
    for(int i=1;;i++)
    {
        if(i&1)
        {
            rb=ra;
            lb=rb-b;
            if(rb>=n) return cout<<i<<'\n',0;
        }
        else
        {
            la=lb;
            ra=la+a;
        }
    }
}