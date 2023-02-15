#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;
const int INF = 1e5 + 5;

/* Class */
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
    return;
}

/* Declaration */
int main();

void Dfs1(int);
void Dfs2(int, int);
int LCA(int, int);
long long GetSum(int, int);

void Update(int, int, int, int, int, int);
int GetMaxLoc(int, int, int, int, int, int);
int GetMax(int, int, int, int, int);
void DownLazy(int);

void UpdateF(int, int, int);

int Max(int, int);
int Min(int, int);

int GetF(int);

/* Variable */
Graph G;

int w[MAXN];

int dep[MAXN];
int fa[MAXN];
int top[MAXN];
int heavy_son[MAXN];
int size[MAXN];
int dfn[MAXN];
int cnt_dfn;
int bh[MAXN];
long long sum[MAXN];

int f[MAXN];

int tr[MAXN];
int lazy[MAXN];

int pd[MAXN];
int sp_tot;
int sp_num[MAXN];

int n;

/* Definition */
int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    int t;
    scanf("%d%d", &n, &t);
    int u, v, _w;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d%d", &u, &v, &_w);
        G.Add(u, v, _w);
    }
    
    Dfs1(1);
    Dfs2(1, 1);
    for (int i = 1; i <= n; ++i)
    {
        sum[i] = sum[i - 1] + w[dfn[i]];
    }
    
    int x;
    int st;
    scanf("%d", &x);
    pd[x] = true;
    long long ans = 0;
    ++sp_tot;
    sp_num[sp_tot] = x;
    st = x;
    UpdateF(1, x, 1);
    int yst;
    printf("0\n");
    for (int i = 2; i <= t; ++i)
    {
        scanf("%d", &x);
        if (!pd[x])
        {
            ++sp_tot;
            sp_num[sp_tot] = x;
            pd[x] = true;
            yst = st;
            st = LCA(x, st);
            ans += GetSum(yst, st);
            ans += GetSum(x, st);
            UpdateF(1, x, 1);
        }
        else
        {
            UpdateF(1, x, -1);
            pd[x] = false;
            yst = st;
            if (GetF(x) == INF)
            {
                ans -= GetSum(st, x);
            }
            for (int j = 1; j <= sp_tot; ++j)
            {
                if (pd[sp_num[j]])
                {
                    st = GetF(j);
                    ans -= GetSum(yst, st);
                    break;
                }
            }
        }
        printf("%lld\n", ans * 2);
    }
    return 0;
}
void Dfs1(int _x)
{
    size[_x] = 1;
    dep[_x] = dep[fa[_x]] + 1;
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa[_x])
        {
            fa[G.to[i]] = _x;
            w[G.to[i]] = G.dis[i];
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
    dfn[_x] = ++cnt_dfn;
    bh[dfn[_x]] = _x;
    top[_x] = _top;
    if (heavy_son[_x])
        Dfs2(heavy_son[_x], _top);
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa[_x] && G.to[i] != heavy_son[_x])
        {
            Dfs2(G.to[i], G.to[i]);
        }
    }
    return;
}
int LCA(int _x, int _y)
{
    int u, v;
    u = top[_x];
    v = top[_y];
    while (u != v)
    {
        if (dep[u] < dep[v])
        {
            _y = fa[v];
        }
        else
        {
            _x = fa[u];
        }
        u = top[_x];
        v = top[_y];
    }
    return dep[_x] < dep[_y] ? _x : _y;
}
long long GetSum(int _x, int _y)
{
    int lca = LCA(_x, _y);
    long long ret = 0;
    while (dep[top[_x]] > dep[lca])
    {
        ret += sum[dfn[_x]] - sum[dfn[top[_x]] - 1];
        _x = fa[top[_x]];
    }
    while (dep[top[_y]] > dep[lca])
    {
        ret += sum[dfn[_y]] - sum[dfn[top[_y]] - 1];
        _y = fa[top[_y]];
    }
    if (_x != lca)
    {
        ret += sum[dfn[_x]] - sum[dfn[lca]];
    }
    if (_y != lca)
    {
        ret += sum[dfn[_y]] - sum[dfn[lca]];
    }
    return ret;
}
void UpdateF(int _x, int _y, int k)
{
    int lca = LCA(_x, _y);
    while (dep[top[_x]] > dep[lca])
    {
        Update(1, n, sum[dfn[top[_x]]], sum[dfn[_x]], 1, k);
        _x = fa[top[_x]];
    }
    while (dep[top[_y]] > dep[lca])
    {
        Update(1, n, sum[dfn[top[_y]]], sum[dfn[_y]], 1, k);
        _y = fa[top[_y]];
    }
    if (_x != lca)
    {
        Update(1, n, sum[dfn[lca]], sum[dfn[_x]], 1, k);
    }
    if (_y != lca)
    {
        Update(1, n, sum[dfn[lca]], sum[dfn[_y]], 1, k);
    }
    return;
}
void Update(int l, int r, int x, int y, int k, int num)
{
    if (x <= l && r <= y)
    {
        tr[k] += num;
        lazy[k] += num;
        return;
    }
    if (lazy[k])
        DownLazy(k);
    int mid = (l + r) >> 1;
    if (x <= mid)
        Update(l, mid, x, y, k * 2, num);
    if (y > mid)
        Update(mid + 1, r, x, y, k * 2 + 1, num);
    tr[k] = Max(tr[k * 2], tr[k * 2 + 1]);
    return;
}
int GetMaxLoc(int l, int r, int x, int y, int k, int num)
{
    if (tr[k] < num)
        return INF;
    if (l == r && x <= l && l <= y)
    {
        if (tr[k] == num)
            return l;
        return INF;
    }
    if (lazy[k])
        DownLazy(k);
    int mid = (l + r) >> 1;
    int ret;
    if (x <= mid)
        ret = GetMaxLoc(l, mid, x, y, k * 2, num);
    if (ret != INF)
        return ret;
    if (y > mid)
        ret = GetMaxLoc(mid + 1, r, x, y, k * 2 + 1, num);
    return ret;
}
int GetMax(int l, int r, int x, int y, int k)
{
    if (x <= l && r <= y)
    {
        return tr[k];
    }
    if (lazy[k])
        DownLazy(k);
    int mid = (l + r) >> 1;
    int ret = 0;
    if (x <= mid)
        ret = Max(ret, GetMax(l, mid, x, y, k * 2));
    if (y > mid)
        ret = Max(ret, GetMax(mid + 1, r, x, y, k * 2 + 1));
    return ret;
}
void DownLazy(int _x)
{
    tr[_x * 2] += lazy[_x];
    tr[_x * 2 + 1] += lazy[_x];
    lazy[_x * 2] += lazy[_x];
    lazy[_x * 2 + 1] += lazy[_x];
    lazy[_x] = 0;
    return;
}
int Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
int GetF(int _x)
{
    int _y = 1;
    int lca = 1;
    int ret = INF;
    while (dep[top[_x]] > dep[lca])
    {
        ret = Min(GetMaxLoc(1, n, dfn[top[_x]], dfn[_x], 1, sp_tot), ret);
        _x = fa[top[_x]];
    }
    while (dep[top[_y]] > dep[lca])
    {
        ret = Min(GetMaxLoc(1, n, dfn[top[_y]], dfn[_y], 1, sp_tot), ret);
        _y = fa[top[_y]];
    }
    if (_x != lca)
    {
        ret = Min(GetMaxLoc(1, n, dfn[lca], dfn[_x], 1, sp_tot), ret);
    }
    if (_y != lca)
    {
        ret = Min(GetMaxLoc(1, n, dfn[lca], dfn[_y], 1, sp_tot), ret);
    }
    return ret == INF ? INF : bh[ret];
}
