#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<ctime>
using namespace std;
int n;
struct ben
{
    double x,y;
}p[10005],s[10005];
int cnt = 1;
double check(ben a1,ben a2,ben b1,ben b2)//检查叉积是否大于0，如果是a就逆时针转到b 
{
    return (a2.x-a1.x)*(b2.y-b1.y)-(b2.x-b1.x)*(a2.y-a1.y);
}
double d(ben p1,ben p2)//两点间距离。。。 
{
    return sqrt((p2.y-p1.y)*(p2.y-p1.y)+(p2.x-p1.x)*(p2.x-p1.x));
}
bool cmp(ben p1,ben p2)//排序函数，这个函数别写错了，要不然功亏一篑 
{
    double tmp=check(p[1],p1,p[1],p2);
    if(tmp>0) 
		return 1;
    if(tmp==0&&d(p[0],p1)<d(p[0],p2)) 
		return 1;
    return 0;
}

void ConvHull()
{
    double mid;
    for(int i=1;i<=n;i++)
    {
        if(i!=1&&p[i].y<p[1].y)//这是是去重 
        {
            mid=p[1].y;p[1].y=p[i].y;p[i].y=mid;
            mid=p[1].x;p[1].x=p[i].x;p[i].x=mid;
        }
    } 
    sort(p+2,p+1+n,cmp);//系统快排 
    s[1]=p[1];//最低点一定在凸包里 
    // int cnt=1;
    for(int i=2;i<=n;i++)
    {
        while(cnt>1&&check(s[cnt-1],s[cnt],s[cnt],p[i])<=0) //判断前面的会不会被踢走，如果被踢走那么出栈
			cnt--;
        cnt++;
        s[cnt]=p[i];
    }
    s[cnt+1]=p[1];//最后一个点回到凸包起点
}

bool Valid(double x, double y)
{
	double rslt = 0;
	for (int i=1;i<=cnt;i++)
	{
		int xo = s[i].x - x, xt = s[i+1].x - s[i].x;
		int yo = s[i].y - y, yt = s[i+1].y - s[i].y;
		rslt += (xo*yt-yo*xt);
	}
	return fabs(rslt) > 1e-8;
}

int main()
{
	freopen("in.in", "w", stdout);
	srand(time(NULL));
	puts("1");
	
	int nn = 40, mm = 7;
	// printf("%d %d", nn, mm);
	n = nn;
	for (int i=1;i<=nn;i++)
	{
		p[i].x = rand() % 70 * (rand()%2 ? 1 : -1);
		p[i].y = rand() % 70 * (rand()%2 ? 1 : -1);
	}
	
	ConvHull();

	printf("%d %d\n", cnt, mm);
	for (int i=1;i<=cnt;i++)
	{
		printf("%.0lf %.0lf\n", s[i].x, s[i].y);
	}
	for (int i=1;i<=mm;i++)
	{
		int x =  rand() % 400 * (rand()%2 ? 1 : -1);
		int y =  rand() % 400 * (rand()%2 ? 1 : -1);
		while (!Valid(x, y))
		{
			x =  rand() % 400 * (rand()%2 ? 1 : -1);
			y =  rand() % 400 * (rand()%2 ? 1 : -1);
		}
		printf("%d %d\n", x, y);
	}
	
}