#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;
const int MAXM = 15;
const long long INF = 1e17 + 5;

/* Class */
struct Graph
{
    int head[MAXN];
    int nxt[MAXN * 2];
    int to[MAXN * 2];
    int dis[MAXN * 2];
    int tot;
    void Add(int, int, int);
};

/* Namespace */
namespace Tree
{
    int fa[MAXN];
    int dep[MAXN];
    int sz[MAXN];
    long long s[MAXN];
    int dfn[MAXN];
    int heavy_son[MAXN];
    int link_top[MAXN];
    int dfn_tot;
    int tot;
    void Dfs1(int);
    void Dfs2(int, int);
    void Init();
    long long GetSum(int, int);
}

/* Declaration */
int main();
void Dfs(int);
long long GetAns();
int Read();
int RRead();
void Qsort(int, int);
void Swap(long long&, long long&);
long long Min(long long, long long);

/* Variable */
Graph G;
int n, m;
int w[MAXN];
int dy[MAXM];
int sp[MAXM];
int s[MAXM];
long long min_time = INF;
bool pd[MAXM];
long long dist[MAXM];

/* Definition */
int main()
{
    freopen("skill.in", "r", stdin);
    freopen("skill.out", "w", stdout);
    n = Read();
    m = Read();
    for (int i = 1; i <= m; ++i)
    {
        s[i] = Read();
    }
    for (int i = 1; i <= m; ++i)
    {
        sp[i] = Read();
    }
    int _u, _v, _w;
    for (int i = 1; i < n; ++i)
    {
        _u = Read();
        _v = Read();
        _w = RRead();
        G.Add(_u, _v, _w);
        G.Add(_v, _u, _w);
    }
    Tree::Dfs1(1);
    Tree::Dfs2(1, 1);
    Tree::Init();
    Dfs(1);
    printf("%lld", min_time);
    return 0;
}
void Dfs(int x)
{
    if (x > m)
    {
        min_time = Min(GetAns(), min_time);
        return;
    }
    for (int i = 1; i <= m; ++i)
    {
        if (!pd[i])
        {
            dy[x] = i;
            pd[i] = true;
            Dfs(x + 1);
            pd[i] = false;
        }
    }
    return;
}
long long GetAns()
{
    long long ret = 0;
    for (int i = 1; i <= m; ++i)
    {
        dist[i] = Tree::GetSum(s[i], sp[dy[i]]);
    }
    Qsort(1, m);
    long long wait_time = 0;
    for (int i = 1; i <= m; ++i)
    {
        wait_time = dist[i];
        ret += wait_time;
    }
    return ret;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    long long mid = dist[(l + r) >> 1];
    while (i <= j)
    {
        while (dist[i] < mid)
            ++i;
        while (dist[j] > mid)
            --j;
        if (i <= j)
        {
            Swap(dist[i], dist[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r);
    if (l < j)
        Qsort(l, j);
    return;
}
void Swap(long long& _a, long long& _b)
{
    long long tmp = _a;
    _a = _b;
    _b = tmp;
    return;
}
long long Min(long long _a, long long _b)
{
    return _a < _b ? _a : _b;
}
int Read()
{
    int ret = 0;
    char tmp = getchar();
    while (tmp < '0' || tmp > '9')
        tmp = getchar();
    while (tmp >= '0' && tmp <= '9')
    {
        ret = (ret << 1) + (ret << 3) + tmp - 48;
        tmp = getchar();
    }
    return ret;
}
int RRead()
{
    int ret = 0;
    int rret = 0;
    char tmp = getchar();
    while (tmp < '0' || tmp > '9')
        tmp = getchar();
    int len = 0;
    while (tmp >= '0' && tmp <= '9')
    {
        ++len;
        ret = (ret << 1) + (ret << 3) + tmp - 48;
        tmp = getchar();
    }
    for (int i = 1; i <= len; ++i)
    {
        rret = (rret << 1) + (rret << 3) + ret % 10;
        ret /= 10;
    }
    return rret;
}
void Graph::Add(int _u, int _v, int _w)
{
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    dis[tot] = _w;
    head[_u] = tot;
}
void Tree::Dfs1(int _x)
{
    dep[_x] = dep[fa[_x]] + 1;
    sz[_x] = 1;
    int max_sz = 0;
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa[_x])
        {
            w[G.to[i]] = G.dis[i];
            fa[G.to[i]] = _x;
            Dfs1(G.to[i]);
            sz[_x] += sz[G.to[i]];
            if (sz[G.to[i]] > max_sz)
            {
                max_sz = sz[G.to[i]];
                heavy_son[_x] = G.to[i];
            }
        }
    }
}
void Tree::Dfs2(int _x, int top)
{
    dfn[_x] = ++dfn_tot;
    link_top[_x] = top;
    if (heavy_son[_x])
        Dfs2(heavy_son[_x], top);
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] != heavy_son[_x] && G.to[i] != fa[_x])
        {
            Dfs2(G.to[i], G.to[i]);
        }
    }
    return;
}
void Tree::Init()
{
    for (int i = 1; i <= n; ++i)
    {
        s[dfn[i]] = w[i];
    }
    for (int i = 1; i <= n; ++i)
    {
        s[i] += s[i - 1];
    }
}
long long Tree::GetSum(int _u, int _v)
{
    long long ret = 0;
    while (link_top[_u] != link_top[_v])
    {
        if (dep[_u] < dep[_v])
        {
            ret += s[dfn[_v]] - s[dfn[link_top[_v]] - 1];
            _v = fa[link_top[_v]];
        }
        else
        {
            ret += s[dfn[_u]] - s[dfn[link_top[_u]] - 1];
            _u = fa[link_top[_u]];
        }
    }
    if (_v != _u)
    {
        if (dep[_v] < dep[_u])
        {
            ret += s[dfn[_u]] - s[dfn[_v] - 1];
        }
        if (dep[_v] > dep[_u])
        {
            ret += s[dfn[_v]] - s[dfn[_u] - 1];
        }
    }
    return ret;
}
