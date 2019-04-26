#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <cmath>

using namespace std;
FILE *fin, *fout, *fstd;

#define rep(i,a,b) for(int i=(a),i##_end_=(b);i<=i##_end_;i++)
#define dwn(i,a,b) for(int i=(a),i##_end_=(b);i>=i##_end_;i--)
const int maxn = 1600;
int n, m;

void WA(int type) {
	puts("0");
	fprintf(stderr, "Wrong Answer[%d]", type);
	exit(0);
}

double val[maxn],all;
int ch[maxn][26],cnt,valy[maxn],cntt[maxn];
void insert(char* s,double v) {
	int j=0,c;
	for(int i=0;s[i];i++) {
		c=s[i]-'0';
		if(!ch[j][c]) ch[j][c]=++cnt;
		j=ch[j][c];
	}
	val[j]+=v;valy[j]++;cntt[j]++;
	all+=v;
}
queue<int> Q;
int fa[maxn];
void getfail() {
	rep(c,0,25) if(ch[0][c]) Q.push(ch[0][c]);
	while(Q.size()) {
		int u=Q.front();Q.pop();
		rep(c,0,25) {
			if(!ch[u][c]) {ch[u][c]=ch[fa[u]][c];continue;}
			int v=ch[u][c],j=fa[u];
			while(j&&!ch[j][c]) j=fa[j];
			fa[v]=ch[j][c];Q.push(v);
			val[v]+=val[fa[v]];
			valy[v]+=valy[fa[v]];
		}
	}
}

char P[maxn],s[maxn],S[maxn];
int Cnt[maxn];

double test(FILE *fin) {
	if(fscanf(fin, "%s", S+1)!=1) WA(1);
	if(strlen(S+1)!=n) WA(1);
	rep(i,1,n) if(P[i]!='.'&&S[i]!=P[i]) WA(2);
	double v=0;int y=0;
	int j=0;
	rep(i,1,n) {
		j=ch[j][S[i]-'0'];
		v+=val[j];y+=valy[j];
		if(cntt[j]) Cnt[j]++;
	}
	if(!y) WA(3);
	int s=0;
	rep(i,0,cnt) if(Cnt[i]) s++;
	return v/y;
}

int main(int argc, char **argv)
{
	fin = fopen("13.in", "r");
	fout = fopen("dat.out", "r");
	fstd = fopen("13.out", "r");
	
	fscanf(fin, "%d %d", &n, &m);
	fscanf(fin, "%s", P+1);
	int v;
	for (int i = 1; i <= m; i++) 
		fscanf(fin, "%s%d", s,&v), insert(s, log(v));
	
	getfail();
	
	double x = test(fstd);
	double y = test(fout);
	
	printf("%.6lf %.6lf\n",x,y);
	
	if(fabs(x-y)>1e-8) WA(3);
	
	puts("100");
	fprintf(stderr, "Congratulations!");
}
