#include <cstdio>
#include <cstring>

/* Constant */
const int MAXN = 1e6 + 5;
const int INF = 1 << 30;
const int SZ = 2;

/* Class */
class Graph
{
    public:
        int head[MAXN];
        int nxt[MAXN * 2];
        int to[MAXN * 2];
        int tot;
        void Add(int, int);
};
void Graph::Add(int _u, int _v)
{
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    head[_u] = tot;
    return;
}

class Matrix
{
    public:
        int a[SZ][SZ];
        int n;
        int m;

        Matrix(int, int);
        Matrix(); 
};
Matrix::Matrix(int _n, int _m)
{
    n = _n;
    m = _m;
    memset(a, 0, sizeof(a));
}
Matrix::Matrix()
{
    memset(a, 0, sizeof(a));
}

class LineTree
{
    public:
        Matrix tr[MAXN << 2];

        void Init(int, int, int);
//        void Update(int, int, int, int, int);
//        void Update2(int, int, int, int, int);
        void UpdateAdd(int, int, int, int, int);
        void Update2Add(int, int, int, int, int);
        Matrix GetSum(int, int, int, int, int);
};

/* Declaration */
int main();

Matrix operator*(const Matrix& _a, const Matrix& _b);

int Max(int, int);

void Dfs1(int);
int Dfs2(int, int);
void Update(int, int, int);
void Init(int);

/* Variable */
int fa[MAXN];
int dep[MAXN];
int top[MAXN];
int dfn[MAXN];
int bh[MAXN];
int heavy_son[MAXN];
int size[MAXN];
int dfn_tot;
int end[MAXN];

int f[MAXN][2];
int g[MAXN][2];

int a[MAXN];

LineTree T;

Graph G;

/* Definition */
Matrix operator*(const Matrix& _a, const Matrix& _b)
{
    Matrix ret(_a.n, _b.m);

    for (int i = 0; i < ret.n; ++i)
    {
        for (int j = 0; j < ret.m; ++j)
        {
//            ret.a[i][j] = -INF;
            for (int k = 0; k < ret.m; ++k)
            {
                ret.a[i][j] = Max(ret.a[i][j], _a.a[i][k] + _b.a[k][j]);
            }
        }
    }
    return ret;
}
int Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
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
            Dfs1(G.to[i]);
            size[_x] += size[G.to[i]];
            if (size[G.to[i]] > size[heavy_son[_x]])
            {
                heavy_son[_x] = G.to[i];
            }
        }
    }
}
int Dfs2(int _x, int _top)
{
    dfn[_x] = ++dfn_tot;
    bh[dfn[_x]] = _x;
    top[_x] = _top;
    if (heavy_son[_x])
        end[_x] = Dfs2(heavy_son[_x], _top);
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa[_x] && G.to[i] != heavy_son[_x])
        {
            Dfs2(G.to[i], G.to[i]);
        }
    }
    if (!heavy_son[_x])
        return end[_x] = _x;
    return end[_x];
}
void LineTree::Init(int l, int r, int k)
{
    if (l == r)
    {
        tr[k].n = tr[k].m = 2;
        tr[k].a[1][0] = g[bh[l]][1];
        tr[k].a[0][0] = tr[k].a[0][1] = g[bh[l]][0];
        tr[k].a[1][1] = -INF;
        return;
    }
    int mid = l + r >> 1;
    Init(l, mid, k * 2);
    Init(mid + 1, r, k * 2 + 1);
    tr[k] = tr[k * 2] * tr[k * 2 + 1];
    return;
}
void LineTree::UpdateAdd(int l, int r, int x, int k, int num)
{
    if (l == x && r == x)
    {
        tr[k].a[1][0] += num;
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid)
        UpdateAdd(l, mid, x, k * 2, num);
    else
        UpdateAdd(mid + 1, r, x, k * 2 + 1, num);
    tr[k] = tr[k * 2] * tr[k * 2 + 1];
    return;
}
void LineTree::Update2Add(int l, int r, int x, int k, int num)
{
    if (l == x && r == x)
    {
        tr[k].a[0][0] += num;
        tr[k].a[0][1] += num;
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid)
        Update2Add(l, mid, x, k * 2, num);
    else
        Update2Add(mid + 1, r, x, k * 2 + 1, num);
    tr[k] = tr[k * 2] * tr[k * 2 + 1];
    return;
}
Matrix LineTree::GetSum(int l, int r, int x, int y, int k)
{
    if (x <= l && r <= y)
    {
        return tr[k];
    }
    int mid = l + r >> 1;
    Matrix ret(2, 2);
    ret.a[0][0] = ret.a[1][1] = 1;
    if (y <= mid)
        return GetSum(l, mid, x, y, k * 2);
    if (x > mid)
        return GetSum(mid + 1, r, x, y, k * 2 + 1);
    return GetSum(l, mid, x, y, k * 2) * GetSum(mid + 1, r, x, y, k * 2 + 1);
}

int main()
{
    freopen("in.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    int _u, _v;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d", &_u, &_v);
        G.Add(_u, _v);
        G.Add(_v, _u);
    }
    Dfs1(1);
    Dfs2(1, 1);
    Init(1);
    T.Init(1, n, 1);
    int x, y;
    Matrix ret;
    Matrix tmp(2, 1);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &x, &y);
        Update(x, y, n);
        ret = T.GetSum(1, n, dfn[1], dfn[end[1]], 1);
        ret = ret * tmp;
        printf("%d\n", Max(ret.a[0][0], ret.a[1][0]));
    }
    return 0;
}
void Update(int x, int y, int n)
{
    T.UpdateAdd(1, n, dfn[x], 1, y - a[x]);
    a[x] = y;
    g[x][1] = y;
    Matrix tmp(2, 2);
    Matrix fz(2, 1);
    while (x)
    {
        x = top[x];
        tmp = T.GetSum(1, n, dfn[x], dfn[end[x]], 1);
        g[x][0] = tmp.a[0][0];
        g[x][1] = tmp.a[1][0];
        tmp = tmp * fz;
        if (fa[x])
        {
            if (f[x][0] > f[x][1])
                T.Update2Add(1, n, dfn[fa[x]], 1, Max(tmp.a[0][0], tmp.a[1][0]) - f[x][0]);
            else
                T.Update2Add(1, n, dfn[fa[x]], 1, Max(tmp.a[0][0], tmp.a[1][0]) - f[x][1]);
            T.UpdateAdd(1, n, dfn[fa[x]], 1, tmp.a[0][0] - f[x][0]);
        }
        f[x][0] = tmp.a[0][0];
        f[x][1] = tmp.a[1][0];
        x = fa[x];
    }
    return;
}
void Init(int _x)
{
    g[_x][0] = 0;
    g[_x][1] = a[_x];
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] == fa[_x])
            continue;
        if (G.to[i] == heavy_son[_x])
            continue;
        Init(G.to[i]);
        g[_x][0] += Max(f[G.to[i]][0], f[G.to[i]][1]);
        g[_x][1] += f[G.to[i]][0];
    }
    if (heavy_son[_x])
        Init(heavy_son[_x]);
    f[_x][0] = g[_x][0] + Max(f[heavy_son[_x]][0], f[heavy_son[_x]][1]);
    f[_x][1] = Max(f[_x][1], g[_x][1] + f[heavy_son[_x]][0]);
    return;
}
