#include <bits/stdc++.h>
#define rep(i, x, y) for (int i = (x); i <= (y); i++)
#define down(i, x, y) for (int i = (x); i >= (y); i--)
#define mid ((l + r) / 2)
#define lc (o << 1)
#define rc (o << 1 | 1)
#define pb push_back
#define mp make_pair
#define PII pair<int, int>
#define F first
#define S second
#define B begin()
#define E end()
using namespace std;
typedef long long LL;
//head

const int N = 4000010;
const int INF = 2147483647;
int n, m, tot, ans, MX;
int a[N], sz[N], cnt[N], ch[N][2], fa[N], dat[N], rt[N];

//=====================================================================
//平衡树

inline void splayClear(int x)
{
    fa[x] = ch[x][0] = ch[x][1] = sz[x] = cnt[x] = dat[x] = 0;
}

inline void pushup(int x)
{
    sz[x] = (ch[x][0] ? sz[ch[x][0]] : 0) + (ch[x][1] ? sz[ch[x][1]] : 0) + cnt[x];
}

inline void rot(int x)
{
    int y = fa[x], z = fa[y];
    bool f = ch[y][1] == x;
    ch[y][f] = ch[x][f ^ 1];
    if (ch[x][f ^ 1])
        fa[ch[x][f ^ 1]] = y;
    fa[x] = z;
    if (z)
        ch[z][ch[z][1] == y] = x;
    fa[y] = x;
    ch[x][f ^ 1] = y;
    pushup(y);
    pushup(x);
}

inline void splay(int i, int x, int top)
{
    while (fa[x] != top)
    {
        int y = fa[x], z = fa[y];
        if (z != top)
            rot((ch[z][0] == y) == (ch[y][0] == x) ? y : x);
        rot(x);
    }
    if (!top)
        rt[i] = x;
}

inline void splayInsert(int i, int v)
{
    int x = rt[i];
    if (!rt[i])
    {
        rt[i] = x = ++tot;
        dat[x] = v;
        sz[x] = cnt[x] = 1;
        fa[x] = ch[x][0] = ch[x][1] = 0;
        return;
    }
    int last = 0;
    while (1)
    {
        if (dat[x] == v)
        {
            cnt[x]++;
            pushup(last);
            break;
        }
        last = x;
        x = ch[x][v > dat[x]];
        if (!x)
        {
            x = ++tot;
            dat[x] = v;
            sz[x] = cnt[x] = 1;
            ch[last][v > dat[last]] = x;
            fa[x] = last;
            ch[x][0] = ch[x][1] = 0;
            pushup(last);
            break;
        }
    }
    splay(i, x, 0);
}

inline int splayRank(int i, int v) //在第i棵splay中求比v小的数的个数
{
    int x = rt[i], ret = 0;
    while (x)
    {
        if (dat[x] == v)
            return ret + ((ch[x][0]) ? sz[ch[x][0]] : 0);
        if (dat[x] < v)
        {
            ret += ((ch[x][0]) ? sz[ch[x][0]] : 0) + cnt[x];
            x = ch[x][1];
        }
        else
            x = ch[x][0];
    }
    return ret;
}

inline int splayFind(int i, int v) //在第i棵splay中找到值为v的节点并将它提升到根
{
    int x = rt[i];
    while (x)
    {
        if (dat[x] == v)
        {
            splay(i, x, 0);
            return x;
        }
        x = ch[x][v > dat[x]];
    }
}

inline int splayPre(int i)
{
    int x = ch[rt[i]][0];
    while (ch[x][1])
        x = ch[x][1];
    return x;
}
inline int splaySuc(int i)
{
    int x = ch[rt[i]][1];
    while (ch[x][0])
        x = ch[x][0];
    return x;
}

inline void splayDelete(int i, int key) //将第i棵splay的值为key的元素删掉
{
    int x = splayFind(i, key);
    if (cnt[x] > 1)
    {
        cnt[x]--;
        pushup(x);
        return;
    }
    if (!ch[x][0] && !ch[x][1])
    {
        splayClear(rt[i]);
        rt[i] = 0;
        return;
    }
    if (!ch[x][0])
    {
        int y = ch[x][1];
        rt[i] = y;
        fa[y] = 0;
        return;
    }
    if (!ch[x][1])
    {
        int y = ch[x][0];
        rt[i] = y;
        fa[y] = 0;
        return;
    }
    int p = splayPre(i);
    int oldrt = rt[i];
    splay(i, p, 0);
    ch[rt[i]][1] = ch[oldrt][1];
    fa[ch[oldrt][1]] = rt[i];
    splayClear(oldrt);
    pushup(rt[i]);
}

inline int splayGetpre(int i, int v)
{
    int x = rt[i];
    while (x)
    {
        if (dat[x] < v)
        {
            if (ans < dat[x])
                ans = dat[x];
            x = ch[x][1];
        }
        else
            x = ch[x][0];
    }
    return ans;
}

inline int splayGetsuc(int i, int v)
{
    int x = rt[i];
    while (x)
    {
        if (dat[x] > v)
        {
            if (ans > dat[x])
                ans = dat[x];
            x = ch[x][0];
        }
        else
            x = ch[x][1];
    }
    return ans;
}

//=====================================================================
//线段树

inline void segInsert(int o, int l, int r, int x, int w)
{
    splayInsert(o, w);
    if (l == r)
        return;
    if (x <= mid)
        segInsert(lc, l, mid, x, w);
    else
        segInsert(rc, mid + 1, r, x, w);
}

inline void segRank(int o, int l, int r, int x, int y, int v)
{
    if (l == x && r == y)
    {
        ans += splayRank(o, v);
        return;
    }
    if (y <= mid)
        segRank(lc, l, mid, x, y, v);
    else if (x > mid)
        segRank(rc, mid + 1, r, x, y, v);
    else
        segRank(lc, l, mid, x, mid, v), segRank(rc, mid + 1, r, mid + 1, y, v);
}

inline void segChange(int o, int l, int r, int x, int v)
{
    splayDelete(o, a[x]);
    splayInsert(o, v);
    if (l == r)
    {
        a[x] = v;
        return;
    }
    if (x <= mid)
        segChange(lc, l, mid, x, v);
    else
        segChange(rc, mid + 1, r, x, v);
}

inline void segPre(int o, int l, int r, int x, int y, int v)
{
    if (l == x && r == y)
    {
        ans = max(ans, splayGetpre(o, v));
        return;
    }
    if (y <= mid)
        segPre(lc, l, mid, x, y, v);
    else if (x > mid)
        segPre(rc, mid + 1, r, x, y, v);
    else
        segPre(lc, l, mid, x, mid, v), segPre(rc, mid + 1, r, mid + 1, y, v);
}

inline void segSuc(int o, int l, int r, int x, int y, int v)
{
    if (l == x && r == y)
    {
        ans = min(ans, splayGetsuc(o, v));
        return;
    }
    if (y <= mid)
        segSuc(lc, l, mid, x, y, v);
    else if (x > mid)
        segSuc(rc, mid + 1, r, x, y, v);
    else
        segSuc(lc, l, mid, x, mid, v), segSuc(rc, mid + 1, r, mid + 1, y, v);
}

//=====================================================================
//第二问

inline int getKth(int x, int y, int k)
{
    int ll = 0, rr = MX + 1, mm;
    while (ll < rr)
    {
        mm = (ll + rr) / 2;
        ans = 0;
        segRank(1, 1, n, x, y, mm);

        // cout<<"Val = "<<mm<<" Rank = "<<ans<<endl;

        if (ans < k)
            ll = mm + 1;
        else
            rr = mm;
    }
    return ll - 1;
}

//=====================================================================
//main

int main()
{
    freopen("dat.in", "r", stdin);
    freopen("2.out", "w", stdout);

    scanf("%d%d", &n, &m);
    rep(i, 1, n)
    {
        scanf("%d", &a[i]);
        segInsert(1, 1, n, i, a[i]);
        MX = max(MX, a[i]);
    }
    while (m--)
    {
        int opt, x, y, z;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
        {
            scanf("%d", &z), ans = 0, segRank(1, 1, n, x, y, z), printf("%d\n", ans + 1);
        }
        else if (opt == 2)
        {
            scanf("%d", &z), printf("%d\n", getKth(x, y, z));
        }
        else if (opt == 3)
        {
            segChange(1, 1, n, x, y);
        }
        else if (opt == 4)
        {
            scanf("%d", &z), ans = -INF, segPre(1, 1, n, x, y, z), printf("%d\n", ans);
        }
        else
        {
            scanf("%d", &z), ans = INF, segSuc(1, 1, n, x, y, z), printf("%d\n", ans);
        }
    }
    return 0;
}
