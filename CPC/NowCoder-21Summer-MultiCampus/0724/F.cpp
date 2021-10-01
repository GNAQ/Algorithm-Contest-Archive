#include<bits/stdc++.h>

using namespace std;

int calc(int a,int b,int type)
{
	if (a>=1e9+100 || b>=1e9+100) return 1e9+1000;
    if(type==1) return a+b;
    else if(type==2) return a-b;
    else if(type==3) return a*b;
    else if(type==4&&b!=0) return a%b==0?(a/b):1e9+1000;
    return 1e9+1000;
}

double dcalc(double a,double b,int type)
{
	if (a>=1e9+100 || b>=1e9+100) return 1e9+1000;
    if(type==1) return a+b;
    else if(type==2) return a-b;
    else if(type==3) return a*b;
    else if(type==4 && b!=0) return a/b;
    return 1e9+1000;
}

int tp[4];

bool check(int a,int b,int c,int d,int m)
{
    bool fg=0;
    int sec[5]={0,a,b,c,d};
    do
    {
        for(int i=1;i<=4;i++)
        {
            for(int j=1;j<=4;j++)
            {
                for(int k=1;k<=4;k++)
                {
                    tp[1]=i,tp[2]=j,tp[3]=k;
                    if(calc(calc(calc(sec[1],sec[2],tp[1]),sec[3],tp[2]),sec[4],tp[3])==m) 
					{
						cerr << "1## " << sec[1] << " " << tp[1] << " " << sec[2] << " " << tp[2] << " " << sec[3] << " " << tp[3] << " " << sec[4] << endl;
						return 0; //((a+b)+c)+d
					}
                    if(calc(calc(sec[1],calc(sec[2],sec[3],tp[2]),tp[1]),sec[4],tp[4])==m) 
					{
						cerr << "2## " << sec[1] << " " << tp[1] << " " << sec[2] << " " << tp[2] << " " << sec[3] << " " << tp[3] << " " << sec[4] << endl;
						return 0; //(a+(b+c))+d
					}
                    if(calc(calc(sec[1],sec[2],tp[1]),calc(sec[3],sec[4],tp[3]),tp[2])==m) 
					{
						cerr << "3## " << sec[1] << " " << tp[1] << " " << sec[2] << " " << tp[2] << " " << sec[3] << " " << tp[3] << " " << sec[4] << endl;
						return 0; //(a+b)+(c+d)
					}
                    if(calc(sec[1],calc(calc(sec[2],sec[3],tp[2]),sec[4],tp[3]),tp[1])==m) 
					{
						cerr << "4## " << sec[1] << " " << tp[1] << " " << sec[2] << " " << tp[2] << " " << sec[3] << " " << tp[3] << " " << sec[4] << endl;
						return 0; //a+((b+c)+d)
					}
                    if(calc(sec[1],calc(sec[2],calc(sec[3],sec[4],tp[3]),tp[2]),tp[1])==m) 
					{
						cerr << "5## " << sec[1] << " " << tp[1] << " " << sec[2] << " " << tp[2] << " " << sec[3] << " " << tp[3] << " " << sec[4] << endl;
						return 0; //a+(b+(c+d))
					}
                    if(fabs(dcalc(dcalc(dcalc(sec[1],sec[2],tp[1]),sec[3],tp[2]),sec[4],tp[3])-m)<1e-4) 
					{
						// cerr << "1!! " << sec[1] << " " << tp[1] << " " << sec[2] << " " << tp[2] << " " << sec[3] << " " << tp[3] << " " << sec[4] << endl;
						fg=1; //((a+b)+c)+d
					}
                    if(fabs(dcalc(dcalc(sec[1],dcalc(sec[2],sec[3],tp[2]),tp[1]),sec[4],tp[4])-m)<1e-4) 
					{
						// cerr << "2!! " << sec[1] << " " << tp[1] << " " << sec[2] << " " << tp[2] << " " << sec[3] << " " << tp[3] << " " << sec[4] << endl;
						fg=1; //(a+(b+c))+d
					}
                    if(fabs(dcalc(dcalc(sec[1],sec[2],tp[1]),dcalc(sec[3],sec[4],tp[3]),tp[2])-m)<1e-4) 
					{
						// cerr << "3!! " << sec[1] << " " << tp[1] << " " << sec[2] << " " << tp[2] << " " << sec[3] << " " << tp[3] << " " << sec[4] << endl;
						fg=1; //(a+b)+(c+d)
					}
                    if(fabs(dcalc(sec[1],dcalc(dcalc(sec[2],sec[3],tp[2]),sec[4],tp[3]),tp[1])-m)<1e-4) 
					{
						// cerr << "4!! " << sec[1] << " " << tp[1] << " " << sec[2] << " " << tp[2] << " " << sec[3] << " " << tp[3] << " " << sec[4] << endl;
						fg=1; //a+((b+c)+d)
					}
                    if(fabs(dcalc(sec[1],dcalc(sec[2],dcalc(sec[3],sec[4],tp[3]),tp[2]),tp[1])-m)<1e-4) 
					{
						// cerr << "5!! " << sec[1] << " " << tp[1] << " " << sec[2] << " " << tp[2] << " " << sec[3] << " " << tp[3] << " " << sec[4] << endl;
						fg=1; //a+(b+(c+d))
					}
                }
            }
        }
    }while(next_permutation(sec+1,sec+5));
    return fg;
}

int ansa[100010],ansb[100010],ansc[100010],ansd[100010];

int main()
{
    int n,m;
    cin>>n>>m;
	int ans=0;
    if(n==1||n==2) 
	{
		cout<<0<<'\n';
		return 0;
	}
	else if (n==3)
	{
		cout<<0<<'\n';
		return 0;
	}
    else
    {
        for(int a=1;a<=13;a++)
            for(int b=a;b<=13;b++)
                for(int c=b;c<=13;c++)
                    for(int d=c;d<=13;d++)
                        if(check(a,b,c,d,m)) 
                        {
                            ans++;
                            ansa[ans]=a;
                            ansb[ans]=b;
                            ansc[ans]=c;
                            ansd[ans]=d;
                        }
		cout << check(2,5,7,7,1) << endl;
    }
	cout<<ans<<'\n';
	for(int i=1;i<=ans;i++)
	{
		if (n==3) cout<<ansa[i]<<' '<<ansb[i]<<' '<<ansc[i]<<'\n';
		else cout<<ansa[i]<<' '<<ansb[i]<<' '<<ansc[i]<<' '<<ansd[i]<<'\n';
	}
}
