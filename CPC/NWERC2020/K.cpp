//D1  K
#include<bits/stdc++.h>

using namespace std;

string a,b;

set<char>sticky;

int main()
{
    getline(cin,a);
    getline(cin,b);
    int ptra=0,ptrb=0;
    int lena=a.size(),lenb=b.size();
    for(;ptra<lena&&ptrb<lenb;ptra++,ptrb++)
    {
        int cnta=1,cntb=1;
        while(a[ptra+1]==a[ptra]) ptra++,cnta++;
        while(b[ptrb+1]==b[ptrb]) ptrb++,cntb++;
        if(cntb==2*cnta) sticky.insert(a[ptra]); 
    }
    for(auto i:sticky) cout<<i;
}