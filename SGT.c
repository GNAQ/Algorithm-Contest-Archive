#include<stdio.h>
#include<math.h>
typedef struct  { int l,r,mid,val,sum,lmax,rmax,tmax; }Seg_Tree;
Seg_Tree SGT[400010]={0};
struct _Node { int sum,lmax,rmax,tmax; };

int seq[100010]={0},lx,rx,n;

void readx(int* x)
{
	(*x)=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { (*x)=(*x)*10+ch-'0'; ch=getchar(); }
	(*x)*=k;
}

int max6(int a1,int a2,int a3,int a4,int a5,int a6)
{
	if (a1>a2) a2=a1;
	if (a2>a3) a3=a2;
	if (a3>a4) a4=a3;
	if (a4>a5) a5=a4;
	if (a5>a6) a6=a5;
	return a6;
}
int min(int a,int b)
{
	if (a<b) b=a;
	return b;
}
int max(int a,int b)
{
	if (a>b) b=a;
	return b;
}

Seg_Tree Update_Info(Seg_Tree a,Seg_Tree b,Seg_Tree sgin)
{
	sgin.sum=a.sum+b.sum;
	sgin.lmax=max(a.sum+b.lmax,a.lmax);
	sgin.rmax=max(a.rmax+b.sum,b.rmax);
	sgin.tmax=max6(a.sum+b.lmax,b.sum+a.rmax
					 ,sgin.sum,a.rmax+b.lmax,a.tmax,b.tmax);
    return sgin;
}

void BuildTree(int inx,int lxx,int rxx)
{
	SGT[inx].l=lxx; SGT[inx].r=rxx;
	if (lxx==rxx)
	{
		SGT[inx].val=seq[lxx];
		SGT[inx].lmax=SGT[inx].rmax=SGT[inx].tmax=seq[lxx];
		return;
	}
	SGT[inx].mid=(lxx+rxx)>>1;
	BuildTree(inx<<1,lxx,SGT[inx].mid);
	BuildTree(inx<<1|1,SGT[inx].mid+1,rxx);
	Update_Info(SGT[inx<<1],SGT[inx<<1|1],SGT[inx]);
}

Seg_Tree qry(int inx)
{
	if (lx<=SGT[inx].l && rx>=SGT[inx].r) return SGT[inx];
	if (lx>SGT[inx].mid) return qry(inx<<1|1);
	if (rx<=SGT[inx].mid) return qry(inx<<1);
	else
	{
		Seg_Tree tmpT;
		return Update_Info(qry(inx<<1),qry(inx<<1|1),tmpT);
	}
}

int main()
{
	int q;
	readx(&n); readx(&q); int i;
	for (i=1;i<=n;i++) readx(&seq[i]);
	BuildTree(1,1,n);
	
	for (i=1;i<=q;i++)
	{
		readx(&lx); readx(&rx);
		Seg_Tree tmpT=qry(1);
		printf("%d\n",max(max(tmpT.lmax,tmpT.rmax),tmpT.tmax));
	}
}
