#include<bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int a;
        cin>>a;
        cout<<min(a,(a+1)/2+1)<<'\n';
    }
}
