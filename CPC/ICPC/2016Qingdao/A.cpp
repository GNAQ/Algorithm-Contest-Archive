#include<bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;
        int sum=0;
        for(int i=1;i<=n;i++)
        {
            int a,b;
            cin>>a>>b;
            sum+=a*b;
        }
        cout<<sum<<'\n';
    }
}