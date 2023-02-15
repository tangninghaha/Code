#include <stdio.h>

/* 声明 */
/* 全局变量 */
const int MAXN = 1e5 + 1;
//int input_x[MAXN], input_y[MAXN], intput_z[MAXN];
int dis[MAXN]; /* 当前的救济粮为 x 的有 dis[x] 个 */
int tmp[MAXN];
int tmp_tot;
int ans[MAXN];
int bh[MAXN];

/* 离散化 */
struct Z
{
    int u;
    int v;
    int w;
};
Z input[MAXN];
bool operator<(const Z &a, const Z &b);
bool operator>(const Z &a, const Z &b);
/* 堆 */
struct tNum /* 一个堆元素 */
{
    int v;
    int z;
};
bool operator<(const tNum &a, const tNum &b);
bool operator>(const tNum &a, const tNum &b);
const int MAXTEAP = 1.7e6 + 5;
struct tTeap
{
    tNum a[MAXTEAP];
    void up(int x);
    void down(int x);
    tNum top();
    void pop();
    void insert(tNum x);
    void check();
    int size;
};
tTeap t;
/* 排序 */
template<typename T> void Qsort(int l, int r, T *a);
/* 树 */
struct Tree
{
    int head[MAXN];
    int nxt[MAXN * 2];
    int to[MAXN * 2];
    int tot;
    void Add(int x, int y);
};
Tree G;
/* 树链剖分 */
int dep[MAXN];
int fa[MAXN];
int top[MAXN];
int heavy_son[MAXN];
int dfn[MAXN];
int rk[MAXN];
int size[MAXN];
void Dfs1(int x);
void Dfs2(int x, int t);
int cnt_dfn;
/* 杂项 */
template<typename T> void swap(T &a, T &b);
/* 树上路径拆分 */
const int MAXWAY = 1700000;
int way_tot;
struct tWay
{
    int st;
    int ed;
    int w;
};
tWay way[MAXWAY];
void CutWay(int u, int v, int w);
/* 答案修改/查询 */
int change_tot;
struct tChange
{
    int st;
    bool type; /* 0加1减 */
    int w;
};
tChange change[MAXWAY * 2];
void GetChange();
bool operator<(const tChange &a, const tChange &b);
bool operator>(const tChange &a, const tChange &b);
void GetAns();

/* 主函数 */
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d", &u, &v);
        G.Add(u, v);
        G.Add(v, u);
    }
    Dfs1(1);
    Dfs2(1, 1);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &input[i].u, &input[i].v, &input[i].w);
    }
    Qsort<Z>(1, m, input);
    int last = -1;
    for (int i = 1; i <= m; ++i)
    {
        if (input[i].w != last)
        {
            ++tmp_tot;
            tmp[i] = tmp_tot;
            last = input[i].w;
            bh[tmp_tot] = input[i].w;
        }
        else
        {
            tmp[i] = tmp_tot;
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        input[i].w = tmp[i];
    }
    for (int i = 1; i <= m; ++i)
    {
        CutWay(input[i].u, input[i].v, input[i].w);
    }
    GetChange();
    Qsort<tChange> (1, change_tot, change);
    GetAns();
    for (int i = 1; i <= n; ++i)
    {
        printf("%d\n", bh[ans[i]]);
    }
    return 0;
}

/* 定义 */
/* 离散化 */
bool operator<(const Z &a, const Z &b)
{
    return a.w < b.w;
}
bool operator>(const Z &a, const Z &b)
{
    return a.w > b.w;
}
/* 堆 */
bool operator<(const tNum &a, const tNum &b)
{
    return a.v == b.v ? a.z < b.z : a.v > b.v;
}
bool operator>(const tNum &a, const tNum &b)
{
    return a.v == b.v ? a.z > b.z : a.v < b.v;
}
void tTeap::up(int x)
{
    int nxt = x / 2;
    while (nxt >= 1)
    {
        if (a[x] < a[nxt])
        {
            swap(a[x], a[nxt]);
            x = nxt;
            nxt = x / 2;
        }
        else
            break;
    }
    return;
}
void tTeap::down(int x)
{
    int nxt = x * 2;
    while ((nxt <= size && a[nxt] < a[x])
            || (nxt + 1 <= size && a[nxt + 1] < a[x]))
    {
        if (a[nxt + 1] < a[nxt] && nxt + 1 <= size)
        {
            ++nxt;
        }
        swap(a[nxt], a[x]);
        x = nxt;
        nxt = x * 2;
    }
    return;
}
tNum tTeap::top()
{
    check();
    if (size && a[1].v)
    {
        return a[1];
    }
    return (tNum){0, 0};
}
void tTeap::pop()
{
    swap(a[1], a[size]);
    --size;
    down(1);
    return;
}
void tTeap::insert(tNum x)
{
    ++size;
    a[size] = x;
    up(size);
    return;
}
void tTeap::check()
{
    while (a[1].v > dis[a[1].z] && size)
    {
        pop();
    }
    return;
}
/* 排序 */
template<typename T> void Qsort(int l, int r, T *a)
{
    int i = l, j = r;
    T mid = a[(l + r) >> 1];
    while (i <= j)
    {
        while (a[i] < mid)
            ++i;
        while (a[j] > mid)
            --j;
        if (i <= j)
        {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (i < r) Qsort(i, r, a);
    if (l < j) Qsort(l, j, a);
    return;
}
/* 树 */
void Tree::Add(int x, int y)
{
    ++tot;
    nxt[tot] = head[x];
    to[tot] = y;
    head[x] = tot;
    return;
}
/* 树链剖分 */
void Dfs1(int x)
{
    dep[x] = dep[fa[x]] + 1;
    size[x] = 1;
    for (int i = G.head[x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa[x])
        {
            fa[G.to[i]] = x;
            Dfs1(G.to[i]);
            size[x] += size[G.to[i]];
            if (size[G.to[i]] > size[heavy_son[x]])
            {
                heavy_son[x] = G.to[i];
            }
        }
    }
    return;
}
void Dfs2(int x, int t)
{
    dfn[x] = ++cnt_dfn;
    rk[dfn[x]] = x;
    top[x] = t;
    if (!heavy_son[x]) return;
    Dfs2(heavy_son[x], t);
    for (int i = G.head[x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa[x] && G.to[i] != heavy_son[x])
        {
            Dfs2(G.to[i], G.to[i]);
        }
    }
}
/* 树上路径拆分 */
void CutWay(int u, int v, int w)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] > dep[top[v]])
        {
            ++way_tot;
            way[way_tot].ed = dfn[u];
            way[way_tot].st = dfn[top[u]];
            way[way_tot].w = w;
            u = fa[top[u]];
        }
        else
        {
            ++way_tot;
            way[way_tot].ed = dfn[v];
            way[way_tot].st = dfn[top[v]];
            way[way_tot].w = w;
            v = fa[top[v]];
        }
    }
//    if (u != v || (u == v && top[u] != u))
//    {
    if (dfn[u] < dfn[v])
    {
        swap(u, v);
    }
    ++way_tot;
    way[way_tot].ed = dfn[u];
    way[way_tot].st = dfn[v];
    way[way_tot].w = w;
//    }
    return;
}
/* 答案查询/修改 */
void GetChange()
{
    for (int i = 1; i <= way_tot; ++i)
    {
        ++change_tot;
        change[change_tot].st = way[i].st;
        change[change_tot].w = way[i].w;
        ++change_tot;
        change[change_tot].st = way[i].ed + 1;
        change[change_tot].w = way[i].w;
        change[change_tot].type = true;
    }
    return;
}
bool operator<(const tChange &a, const tChange &b)
{
    return a.st < b.st;
}
bool operator>(const tChange &a, const tChange &b)
{
    return a.st > b.st;
}
void GetAns()
{
    change[0].st = 1;
    for (int i = 1; i <= change_tot; ++i)
    {
        for (int j = change[i - 1].st; j <= change[i].st - 1; ++j)
        {
            ans[rk[j]] = t.top().z;
        }
        dis[change[i].w] += (change[i].type == 1 ? -1 : 1);
        t.insert((tNum){dis[change[i].w], change[i].w});
    }
}
/* 杂项 */
template<typename T> void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
    return;
}
