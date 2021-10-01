#include<bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
double x1,y11,z1,r1;
double x2,y2,z2,r2;

double Ax,Ay,Az;
double Bx,By,Bz;
double Cx,Cy,Cz;
double Dx,Dy,Dz;
double k1,k2;
//球冠的体积：PI*h*h/(3*r-h)其中h是圆的半径r-圆心到截圆的平面的距离dis。h1=r1-(r1*r1-r2*r2+d*d)/(2*d)其中d为两圆心之间的距离。 
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        cin>>Ax>>Ay>>Az>>Bx>>By>>Bz>>Cx>>Cy>>Cz>>Dx>>Dy>>Dz>>k1>>k2;
        x1=(Ax-k1*k1*Bx)/(1-k1*k1);
        y11=(Ay-k1*k1*By)/(1-k1*k1);
        z1=(Az-k1*k1*Bz)/(1-k1*k1);
        r1=-sqrt((Ax-Bx)*(Ax-Bx)+(Ay-By)*(Ay-By)+(Az-Bz)*(Az-Bz))*k1/(1-k1*k1);
        x2=(Cx-k2*k2*Dx)/(1-k2*k2);
        y2=(Cy-k2*k2*Dy)/(1-k2*k2);
        z2=(Cz-k2*k2*Dz)/(1-k2*k2);
        r2=-sqrt((Cx-Dx)*(Cx-Dx)+(Cy-Dy)*(Cy-Dy)+(Cz-Dz)*(Cz-Dz))*k2/(1-k2*k2);
        // scanf("%lf%lf%lf%lf",&x1,&y11,&z1,&r1);
        // scanf("%lf%lf%lf%lf",&x2,&y2,&z2,&r2);
        double dis=sqrt((x1-x2)*(x1-x2)+(y11-y2)*(y11-y2)+(z1-z2)*(z1-z2));
        double s;
        if(dis>=r1+r2)
        {
            s=0;
        }
        else if(dis<=fabs(r1-r2))
        {
            double maxn=min(r1,r2);
            s=4.0/3.0*PI*(maxn*maxn*maxn);
        }
        else
        {
            s=0;
            double h1=r1-(r1*r1-r2*r2+dis*dis)/(2*dis);
            s+=(PI*h1*h1*(3*r1-h1)/3.0);
            double h2=r2-(r2*r2-r1*r1+dis*dis)/(2.0*dis);
            s+=(PI*h2*h2*(3*r2-h2)/3.0);
        }
        cout<<s<<"\n";

    }
	
}
