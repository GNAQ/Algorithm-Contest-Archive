# include <bits/stdc++.h>
# define LL long long
# define N 100010

using namespace std;

int n,a[N],b[N],ans;

int main() {
    //freopen("data.txt","r",stdin);
    scanf("%d",&n);
    for (int i=1; i<=n; ++i) scanf("%d",&a[i]);
    for (int i=1; i<=n; ++i) scanf("%d",&b[i]);
    sort(a+1, a+n+1);
    sort(b+1, b+n+1);
    for (int i=1,j=1; i<=n; ++i)
        if (a[i] > b[j]) ans++,j++; 
    printf("%d",ans);
}
