#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;
const int MAXM = 2e5 + 5;
const long long mod = 1e9 + 7;

/* Class */
struct Graph
{
    int head[MAXN];
    int nxt[MAXM * 2];
    int to[MAXM * 2];
    int tot;
    void Add(int, int);
};

/* Definition */
int main();
void Dfs(int);
void Qsort(int, int);
void Swap(int&, int&);
void Update1(int);
void Update2(int);

/* Variable */
long long mov1[MAXN];
long long mov2[MAXN];
long long value[MAXN];

int ydep[MAXN];
int rk[MAXN];
int dep[MAXN];
int fa[MAXN];
Graph Tree;
Graph G;

/* Declaration */
int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &value[i]);
        value[i] %= mod;
    }
    int x, y;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d", &x, &y);
        Tree.Add(x, y);
        Tree.Add(y, x);
    }
    Dfs(1);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &x, &y);
        G.Add(x, y);
        G.Add(y, x);
    }
    long long k;
    int type, u;
    for (int i = 1; i <= q; ++i)
    {
        scanf("%d%d%lld", &type, &u, &k);
        if (type == 1)
        {
            mov1[u] += k;
            mov1[u] %= mod;
        }
        else
        {
            mov2[u] += k;
            mov2[u] %= mod;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        ydep[i] = dep[i];
        rk[i] = i;
    }
    Qsort(1, n);
    for (int i = n; i >= 1; --i)
    {
        Update1(rk[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        Update2(rk[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        printf("%lld ", value[i]);
    }
    return 0;
}
void Dfs(int _x)
{
    dep[_x] = dep[fa[_x]] + 1;
    for (int i = Tree.head[_x]; i; i = Tree.nxt[i])
    {
        if (Tree.to[i] != fa[_x])
        {
            fa[Tree.to[i]] = _x;
            Dfs(Tree.to[i]);
        }
    }
    return;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    const int mid = dep[(l + r) >> 1];
    while (i <= j)
    {
        while (dep[i] < mid)
            ++i;
        while (mid < dep[j])
            --j;
        if (i <= j)
        {
            Swap(dep[i], dep[j]);
            Swap(rk[i], rk[j]);
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
void Swap(int& _a, int& _b)
{
    int tmp = _a;
    _a = _b;
    _b = tmp;
    return;
}
void Update1(int _x)
{
    mov1[_x] %= mod;
    value[_x] += mov1[_x];
    value[_x] %= mod;
    mov1[fa[_x]] += mov1[_x];
    mov1[fa[_x]] %= mod;
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (ydep[G.to[i]] < ydep[_x])
        {
            mov1[G.to[i]] += mov1[_x];
            mov1[G.to[i]] %= mod;
        }
    }
}
void Update2(int _x)
{
    mov2[_x] %= mod;
    value[_x] += mov2[_x];
    value[_x] %= mod;
    for (int i = Tree.head[_x]; i; i = Tree.nxt[i])
    {
        if (ydep[Tree.to[i]] > ydep[_x])
        {
            mov2[Tree.to[i]] += mov2[_x];
            mov2[Tree.to[i]] %= mod;
        }
    }
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (ydep[G.to[i]] > ydep[_x])
        {
            mov2[G.to[i]] += mov2[_x];
            mov2[G.to[i]] %= mod;
        }
    }
}
void Graph::Add(int _u, int _v)
{
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    head[_u] = tot;
    return;
}
