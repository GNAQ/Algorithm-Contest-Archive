#pragma GCC optimize(3)
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#define ll long long
#define mo 30007
#define mp make_pair
using namespace std;

int valx[13][13]={0};
int n=0; ll all_ans=-2*1e9;

int bits[10]={0},s[20]={0};
struct hash_table
{
    int pre,state,dp;
}idx[2][1001000]={0};
int ptr[2][30010]={0},tots[2],pre=1,cnt=0;

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}
inline void reads()
{
    readx(n);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++) readx(valx[i][j]);
}
inline void init_bits() { for (int i=1;i<=10;i++) bits[i]=i*3; }

inline int hah(int sta,int val)
{
    register int key=sta%mo;
    for (int prex=ptr[cnt][key];prex;prex=idx[cnt][prex].pre) if (idx[cnt][prex].state==sta)
        return idx[cnt][prex].dp=max(idx[cnt][prex].dp,val);
    
    idx[cnt][++tots[cnt]].pre=ptr[cnt][key];
    ptr[cnt][key]=tots[cnt];
    idx[cnt][tots[cnt]].dp=val;
    idx[cnt][tots[cnt]].state=sta;
    return val;
}

inline void get_state(int sta)
{
    for (int i=1;i<=n;i++) s[i]=(sta>>bits[i])&7;
    s[0]=0;
}

inline int relabel(int val)
{
    int t[20]; memset(t,0,sizeof t); int ctr1=0,sta=0;
    
    for (int i=1;i<=n;i++) if (s[i])
    {
        if (t[s[i]]) s[i]=t[s[i]];
        else s[i]=t[s[i]]=++ctr1;
    }
    for (int i=1;i<=n;i++) sta+=(s[i]<<bits[i]);
    
    if (ctr1 && ctr1<=1) all_ans=max(all_ans,(ll)val);
    return sta;
}

inline void DP()
{
    register int r_plug,d_plug,nowans,cac1;
    tots[cnt]=0; hah(0,0);
    
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        {
            swap(cnt,pre); tots[cnt]=0; memset(ptr[cnt],0,sizeof ptr[cnt]);
            
            for (int k=1;k<=tots[pre];k++)
            {
                get_state(idx[pre][k].state);
                
                d_plug=s[j]; r_plug=s[j-1]; nowans=idx[pre][k].dp;
                
                //case 1
                s[j]=cac1=0;
                for (int l=1;l<=n;l++) if (d_plug==s[l]) cac1++;
                if (!d_plug || cac1) hah( relabel(nowans) , nowans );
                
                get_state(idx[pre][k].state);
                nowans=idx[pre][k].dp+valx[i][j];
                
                if ((!r_plug) && (!d_plug)) s[j]=7; //case 2 create new
                else  //case 3
                {
                    s[j]=max(r_plug,d_plug);
                    for (int l=1;l<=n;l++) if (s[l] && s[l]==min(r_plug,d_plug)) s[l]=max(r_plug,d_plug); //connect 2 components
                }
                
                hah( relabel(nowans) , nowans );
            }
        }
}

int main()
{
    init_bits(); reads();
    DP();
    printf("%d\n",all_ans);
    return 0;
}