#include<bits/stdc++.h>

using namespace std;

string s;

int main()
{
    cin>>s;
    long long ans=0;
    int cnt=0;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='0') cnt++,ans+=i+1;
    }
    ans-=1ll*cnt*(cnt+1)/2;
    if(ans%3) cout<<"Alice\n";
    else cout<<"Bob\n";
}