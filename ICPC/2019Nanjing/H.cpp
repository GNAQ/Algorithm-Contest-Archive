#include<bits/stdc++.h>

using namespace std;

int main()
{
    int a,b,c;
    cin>>a>>b>>c;
    int ans=(b+c)*2+1,sum=a+b+c;
    if(sum==1) return cout<<"YES\n0\n",0;
    if(sum>=ans) cout<<"YES\n"<<ans<<'\n';
    else cout<<"NO\n";
}