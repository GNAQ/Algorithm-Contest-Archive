#include<bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        if(a>b) swap(a,b);
        if(c>d) swap(c,d);
        if(a==2&&b==8&&c==2&&d==8)
        {
            cout<<"tie\n";
        }
        else if(a==2&&b==8)
        {
            cout<<"first\n";
        }
        else if(c==2&&d==8)
        {
            cout<<"second\n";
        }
        else if(a==b&&c==d)
        {
            if(a>c) cout<<"first\n";
            else if(a==c) cout<<"tie\n";
            else cout<<"second\n";
        }
        else if(a==b) cout<<"first\n";
        else if(c==d) cout<<"second\n";
        else 
        {
            int f1=(a+b)%10,f2=(c+d)%10;
            if(f1>f2) cout<<"first\n";
            else if(f1<f2) cout<<"second\n";
            else 
            {
                if(b>d) cout<<"first\n";
                else if(b<d) cout<<"second\n";
                else cout<<"tie\n";
            }
        }
    }
}