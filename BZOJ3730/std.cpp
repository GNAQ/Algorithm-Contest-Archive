#include <iostream>
#include <cstdio>
#include <cstring>
#define re register
#define il inline
 
using namespace std;
const int MAXN = 2e5 + 5;

il int gc() {
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2)) ? EOF : *p1++;
    //return getchar();
}

il int geti() {
    re char ch = gc();
    re int f = 1, x = 0;
    while (ch < '0' || ch > '9') f = (ch == '-' ? -1 : 1), ch = gc();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = gc();
    return f * x;
}
 
int n, m;
int a[MAXN];
int to[MAXN], nxt[MAXN], head[MAXN], ecnt;
 
il void Add(re int u, re int v) {
    to[++ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt;
    to[++ecnt] = u; nxt[ecnt] = head[v]; head[v] = ecnt;
}
 
int dep[MAXN];
int stt[20][MAXN], lg2[MAXN], id1[MAXN], tot;
 
void DFS1(int u, int last, int depth) {
    dep[u] = depth;
    stt[0][++tot] = u;
    id1[u] = tot;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == last) continue;
        DFS1(v, u, depth + 1);
        stt[0][++tot] = u;
    }
}
 
il int Lower(re int x, re int y) {
    return dep[x] < dep[y] ? x : y;
}
 
void GetST() {
    for (re int i = 2; i <= tot; i++) lg2[i] = lg2[i >> 1] + 1;
    for (re int i = 1; (1 << i) <= tot; i++) {
        re int w = (1 << i);
        for (re int j = 1; j + w - 1 <= tot; j++) {
            stt[i][j] = Lower(stt[i - 1][j], stt[i - 1][j + w / 2]);
        }
    }
}
 
il int LCA(re int x, re int y) {
    x = id1[x]; y = id1[y];
    if (x > y) swap(x, y);
    int i = lg2[y - x + 1], w = (1 << i);
    return Lower(stt[i][x], stt[i][y - w + 1]);
} 
 
il int Dis(re int x, re int y) {
    return dep[x] + dep[y] - 2 * dep[LCA(x, y)];
}
 
int size[MAXN], maxs[MAXN];
int dfa[MAXN];
int vis[MAXN];
int dsiz[MAXN];
 
int DFS2(int u, int last, int tots) {
    size[u] = 1;
    maxs[u] = 0;
    int cen = 0;
    for (re int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (vis[v] || v == last) continue;
        int vcen = DFS2(v, u, tots);
        if (!cen || maxs[vcen] < maxs[cen]) cen = vcen;
        size[u] += size[v];
        maxs[u] = max(maxs[u], size[v]);
    }
    maxs[u] = max(maxs[u], tots - size[u]);
    if (!cen || maxs[u] < maxs[cen]) cen = u;
    return cen;
}
 
void Divide(int cen, int tots) {
    vis[cen] = 1;
    dsiz[cen] = tots;
    for (re int i = head[cen]; i; i = nxt[i]) {
        int v = to[i];
        if (vis[v]) continue;
        int vsize = (size[v] < size[cen]) ? size[v] : (tots - size[cen]);
        int vcen = DFS2(v, cen, vsize);
        dfa[vcen] = cen;
        Divide(vcen, vsize);
    }
}

struct Node{
    int sum;
    Node *ch[2];
};
 
Node npool[10000000];
int ncnt;
 
struct SegTree{
    Node *rt;
    SegTree() {rt = NULL;}
    Node *New() {return &npool[ncnt++];}
     
    void Modify(Node *&now, int pos, int k, int l, int r) {
        if (!now) now = New();
        now->sum += k;
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (pos <= mid) Modify(now->ch[0], pos, k, l, mid);
        else Modify(now->ch[1], pos, k, mid + 1, r);
    }
     
    int Query(Node *now, int l, int r, int nl, int nr) {
        if (!now) return 0;
        if (l == nl && r == nr) return now->sum;
        int mid = (nl + nr) >> 1;
        if (r <= mid) return Query(now->ch[0], l, r, nl, mid);
        else if (l > mid) return Query(now->ch[1], l, r, mid + 1, nr);
        return Query(now->ch[0], l, mid, nl, mid) + Query(now->ch[1], mid + 1, r, mid + 1, nr);
    }
};

SegTree T1[MAXN], T2[MAXN];
 
il void Modify(int idx, int val) {
    re int now = idx;
    while (now) {
        int fa = dfa[now];
        T1[now].Modify(T1[now].rt, Dis(now, idx), val, 0, dsiz[now]);
        if (fa) T2[now].Modify(T2[now].rt, Dis(fa, idx), val, 0, dsiz[fa]);
        now = fa;
    }
}
 
il int Query(int idx, int k) {
    re int res = 0;
    re int now = idx, last = 0;
    while (now) {
        int d = Dis(idx, now);
		cout << "!!" << d << endl;
        
        if (d > k) {
            last = now;
            now = dfa[now];
            continue;
        }
        res += T1[now].Query(T1[now].rt, 0, k - d, 0, dsiz[now]);
			cout << "#" << res << " " << k-d << endl;

        
        if (last) res -= T2[last].Query(T2[last].rt, 0, k - d, 0, dsiz[now]);
        last = now;
        now = dfa[now];
    }
    return res;
}
 
void Prework() {
    DFS1(1, 0, 0);
    GetST();
    int cen = DFS2(1, 0, n);
    Divide(cen, n);
	
    for (int i = 1; i <= n; i++) Modify(i, a[i]);
}
 
int main() {
    n = geti(); m = geti();
    for (re int i = 1; i <= n; i++) a[i] = geti();
    for (re int i = 1; i <= n - 1; i++) {
        int x = geti(), y = geti();
        Add(x, y);
    }
    Prework();
    int ans = 0;
    for (re int i = 1; i <= m; i++) {
        int op = geti(), x = geti(), y = geti();
        x ^= ans; y ^= ans;
        if (op == 0) {
            ans = Query(x, y);
            printf("%d\n", ans);
        } else {
            Modify(x, y - a[x]);
            a[x] = y;
        }
    }
    return 0;
}