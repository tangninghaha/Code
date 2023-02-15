#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;

/* Class */
class LineTree
{
    public:
        int tr_max[MAXN * 4];
        int tr_min[MAXN * 4];
        int Min(int, int);
        int Max(int, int);

        void Init(int, int, int);
        void Update(int, int, int, int);
        int GetMax(int, int, int, int, int);
        int GetMin(int, int, int, int, int);
};
void LineTree::Init(int l, int r, int k)
{
    if (l == r)
    {
        tr_min[k] = MAXN;
        return;
    }
    int mid = l + r >> 1;
    Init(l, mid, k * 2);
    Init(mid + 1, r, k * 2 + 1);
    tr_min[k] = Min(tr_min[k * 2], tr_min[k * 2 + 1]);
    return;
}
int LineTree::Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
int LineTree::Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
void LineTree::Update(int l, int r, int sum, int k)
{
    if (l == sum && r == sum)
    {
        if (tr_max[k] == 0)
        {
            tr_min[k] = sum;
            tr_max[k] = sum;
        }
        else
        {
            tr_min[k] = MAXN;
            tr_max[k] = 0;
        }
        return;
    }
    int mid = l + r >> 1;
    if (sum <= mid)
        Update(l, mid, sum, k * 2);
    if (sum > mid)
        Update(mid + 1, r, sum, k * 2 + 1);
    tr_min[k] = Min(tr_min[k * 2], tr_min[k * 2 + 1]);
    tr_max[k] = Max(tr_max[k * 2], tr_max[k * 2 + 1]);
    return;
}
int LineTree::GetMax(int l, int r, int x, int y, int k)
{
    if (x <= l && r <= y)
    {
        return tr_max[k];
    }
    int ret = 0;
    int mid = l + r >> 1;
    if (x <= mid)
        ret = Max(ret, GetMax(l, mid, x, y, k * 2));
    if (y > mid)
        ret = Max(ret, GetMax(mid + 1, r, x, y, k * 2 + 1));
    return ret;
}
int LineTree::GetMin(int l, int r, int x, int y, int k)
{
    if (x <= l && r <= y)
    {
        return tr_min[k];
    }
    int ret = MAXN;
    int mid = l + r >> 1;
    if (x <= mid)
        ret = Min(ret, GetMin(l, mid, x, y, k * 2));
    if (y > mid)
        ret = Min(ret, GetMin(mid + 1, r, x, y, k * 2 + 1));
    return ret;
}


class Graph
{
    public:
        int head[MAXN];
        int nxt[MAXN * 2];
        int to[MAXN * 2];
        int dis[MAXN * 2];
        int tot;
        void Add(int, int, int);
};
void Graph::Add(int _u, int _v, int _dis)
{
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    dis[tot] = _dis;
    head[_u] = tot;
}

/* Declaration */
int main();

void Dfs1(int);
void Dfs2(int, int);
long long GetSum(int, int);

void Swap(int&, int&);

/* Variable */
long long sum[MAXN];

Graph G;
LineTree T;

int fa[MAXN];
int dep[MAXN];
int size[MAXN];
int heavy_son[MAXN];
int dfn[MAXN];
int bh[MAXN];
int top[MAXN];

int dfn_tot;

int w[MAXN];
bool pd[MAXN];

/* Definition */
void Dfs1(int _x)
{
    size[_x] = 1;
    dep[_x] = dep[fa[_x]] + 1;
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa[_x])
        {
            w[G.to[i]] = G.dis[i];
            fa[G.to[i]] = _x;
            Dfs1(G.to[i]);
            size[_x] += size[G.to[i]];
            if (size[G.to[i]] > size[heavy_son[_x]])
            {
                heavy_son[_x] = G.to[i];
            }
        }
    }
    return;
}
void Dfs2(int _x, int _top)
{
    dfn[_x] = ++dfn_tot;
    bh[dfn_tot] = _x;
    top[_x] = _top;
    if (heavy_son[_x])
    {
        Dfs2(heavy_son[_x], _top);
    }
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa[_x] && G.to[i] != heavy_son[_x])
        {
            Dfs2(G.to[i], G.to[i]);
        }
    }
    return;
}
long long GetSum(int _x, int _y)
{
    long long ret = 0;
    while (top[_x] != top[_y])
    {
        if (dep[top[_x]] < dep[top[_y]])
        {
            Swap(_x, _y);
        }
        ret += sum[dfn[_x]] - sum[dfn[top[_x]] - 1];
        _x = fa[top[_x]];
    }
    if (dep[_x] > dep[_y])
    {
        Swap(_x, _y);
    }
    ret += sum[dfn[_y]] - sum[dfn[_x]];
    return ret;
}
int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    int n, t;
    scanf("%d%d", &n, &t);
    int _u, _v, _w;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d%d", &_u, &_v, &_w);
        G.Add(_u, _v, _w);
        G.Add(_v, _u, _w);
    }

    Dfs1(1);
    Dfs2(1, 1);
    for (int i = 1; i <= n; ++i)
    {
        sum[i] = sum[i - 1] + w[bh[i]];
    }

    T.Init(1, n, 1);
    int x;
    long long ans = 0;
    int pre, nxt;
    int st = n + 1, ed = 0;
    bool pdd;
    for (int i = 1; i <= t; ++i)
    {
        pdd = false;
        scanf("%d", &x);
        T.Update(1, n, dfn[x], 1);
        if (dfn[x] > 1)
            pre = T.GetMax(1, n, 1, dfn[x] - 1, 1);
        else
            pre = 0;
        if (dfn[x] < n)
            nxt = T.GetMin(1, n, dfn[x] + 1, n, 1);
        else
            nxt = MAXN;
        if (!pd[x])
        {
            if (pre && nxt != MAXN)
            {
                ans -= GetSum(bh[pre], bh[nxt]);
            }
            if (pre)
            {
                ans += GetSum(bh[pre], x);
            }
            if (nxt != MAXN)
            {
                ans += GetSum(bh[nxt], x);
            }
            if (dfn[x] < st)
            {
                if (st != n + 1 && ed != 0)
                    ans -= GetSum(bh[st], bh[ed]);
                st = dfn[x];
                pdd = true;
            }
            if (dfn[x] > ed)
            {
                if (st != n + 1 && ed != 0)
                    ans -= GetSum(bh[st], bh[ed]);
                ed = dfn[x];
                pdd = true;
            }
            if (pdd)
                ans += GetSum(bh[st], bh[ed]);
        }
        else
        {
            if (pre && nxt != MAXN)
            {
                ans += GetSum(bh[pre], bh[nxt]);
            }
            if (pre)
            {
                ans -= GetSum(bh[pre], x);
            }
            if (nxt != MAXN)
            {
                ans -= GetSum(bh[nxt], x);
            }
            if (dfn[x] == st)
            {
                if (st != n + 1 && ed != 0)
                    ans -= GetSum(bh[st], bh[ed]);
                st = nxt == MAXN ? 0 : nxt;
                pdd = true;
            }
            if (dfn[x] == ed)
            {
                if (st != n + 1 && ed != 0)
                    ans -= GetSum(bh[st], bh[ed]);
                ed = pre == 0 ? n + 1 : pre;
                pdd = true;
            }
            if (pdd)
                ans += GetSum(bh[st], bh[ed]);
        }
        pd[x] = !pd[x];
        printf("%lld\n", ans);
    }
    return 0;
}
void Swap(int& _a, int& _b)
{
    int _t = _a;
    _a = _b;
    _b = _t;
    return;
}
