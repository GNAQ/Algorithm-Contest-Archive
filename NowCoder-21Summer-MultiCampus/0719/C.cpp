#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,m;
    cin>>n>>m;
    cout<<(((n-1)*m+(m-1)*n-(m-1)*(n-1))&1?"YES":"NO")<<'\n';
}