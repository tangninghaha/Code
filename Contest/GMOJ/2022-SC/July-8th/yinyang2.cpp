#include <stdio.h>
#include <cstring>

/* 声明 */
const int MAXN = 1e5 + 5, N = 1e5;
/* 全局变量 */
int n;
int tr_size;

/* 树的重心 */
int size[MAXN];
int weight[MAXN]; /* 以 x 为根的最大子树大小 */
int heavy_point;
void GetHeavyPoint(int x, int fa);
int TreeSz(int x, int fa); /* 树的大小 */
int t_tree_size;

/* 统计答案 */
int s[MAXN];
long long ans;
void GetAns(int root);
void Pre(int x, int fa); /* 预处理出 s 和 t_all */
void Dfs(int x, int fa);
int t_all[MAXN * 2]; /* 统计 s 的个数的桶 (所有节点) */
int t_tree[MAXN * 2]; /* 统计 s 子树中的个数的桶 */
int t[MAXN * 2]; /* 统计 s 的个数的桶 */
int cnt[MAXN * 2]; /* 统计当前子树上方有点 v 的点 */
int tot_cnt;
int ans1[MAXN * 2]; /* 当前遍历过的点中满足点 u 上方有点 v 的点个数 */
void GetTtree(int x, int fa); /* 处理出 t_tree */
int r; /* 父亲 */
int max_num, min_num; /* 统计的 s 中的个数的最大最小值*/
//int max_ttree, min_ttree; /* 统计t_tree最大最小值 */

/* 图 */
struct Graph
{
    Graph();
    bool vis[MAXN];
    int head[MAXN];
    int nxt[MAXN * 2];
    int to[MAXN * 2];
    int dis[MAXN * 2];
    int tot;
    void Add(int x, int y, int z);
};
Graph G;

/* 杂项 */
int max(int a, int b);
int min(int a, int b);

/* 清空数组 */
void CleanWeight(int x, int fa);

/* 主函数 */
int main()
{
    freopen("yinyang.in", "r", stdin);
    int n;
    scanf("%d", &n);
    int u, v, w;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        G.Add(u, v, w == 0 ? -1 : 1);
        G.Add(v, u, w == 0 ? -1 : 1);
    }
    tr_size = n;
    t_tree_size = n;
    GetHeavyPoint(1, 0);
    GetAns(heavy_point);
    printf("%lld", ans);
    return 0;
}

/* 定义 */
void CleanWeight(int x, int fa)
{
    weight[x] = 0;
    for (int i = G.head[x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa && !G.vis[G.to[i]])
        {
            CleanWeight(G.to[i], x);
        }
    }
    return;
}
void GetHeavyPoint(int x, int fa) /* 计算树的重心 */
{
    size[x] = 1;
    for (int i = G.head[x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa && !G.vis[G.to[i]])
        {
            GetHeavyPoint(G.to[i], x);
            size[x] += size[G.to[i]];
            weight[x] = max(size[G.to[i]], weight[x]);
        }
    }
    weight[x] = max(weight[x], t_tree_size - size[x]);
    if (weight[x] <= t_tree_size / 2)
    {
        heavy_point = x;
        return;
    }
    return;
}
int TreeSz(int x, int fa)
{
    int ret = 1;
    for (int i = G.head[x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa && !G.vis[G.to[i]])
        {
            ret += TreeSz(G.to[i], x);
        }
    }
    return ret;
}
void GetAns(int root)
{
//    memset(t_all, 0, sizeof(t_all));
//    memset(ans1, 0, sizeof(ans1));
    for(int i = min_num; i <= max_num; ++i)
    {
        ans1[i + N] = 0;
        t_all[i + N] = 0;
    }
    max_num = -N - 1, min_num = N + 1;
//    memset(weight, 0, sizeof(weight));
    CleanWeight(root, 0);
//    memset(size, 0, sizeof(size));
    heavy_point = 0;
//    memset(cnt, 0, sizeof(cnt));
//    memset(s, 0, sizeof(s));
    s[root] = 0;
    r = root;
    Pre(root, 0);
    Dfs(root, 0);
    G.vis[root] = true;
    --tr_size;
    for (int i = G.head[root]; i; i = G.nxt[i])
    {
        if (!G.vis[G.to[i]])
        {
            t_tree_size = TreeSz(G.to[i], 0);
//            t_tree_size = size[G.to[i]];
            GetHeavyPoint(G.to[i], 0);
//            if (G.vis[heavy_point]) printf("!");
            GetAns(heavy_point);
        }
    }
    return;
}
void Pre(int x, int fa)
{
//    if (t[s[x] + N])
//    {
//        ++cnt[s[x] + N];
//    }
//    ++t[s[x] + N];
    ++t_all[s[x] + N];
    max_num = max(max_num, s[x]);
    min_num = min(min_num, s[x]);
    for (int i = G.head[x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa && !G.vis[G.to[i]])
        {
            s[G.to[i]] = s[x] + G.dis[i];
            Pre(G.to[i], x);
        }
    }
//    --t[s[x] + N];
    return;
}
void GetTtree(int x, int fa)
{
    ++t_tree[s[x] + N];
//    max_ttree = max(max_ttree, s[x]);
//    min_ttree = min(min_ttree, s[x]);
    for (int i = G.head[x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa && !G.vis[G.to[i]])
        {
            GetTtree(G.to[i], x);
        }
    }
    return;
}
void Dfs(int x, int fa)
{
//    bool pd = false;
    if (fa == r)
    {
        GetTtree(x, fa);
        ++t_tree[N];
    }
    if (t[s[x] + N])
    {
        if (t[s[x] + N] > 1 && s[x] == 0)
        {
            ans++;
        }
//        pd = true;
//        ++ans1;
        ++tot_cnt;
        cnt[tot_cnt] = s[x] + N;
        ans += t_all[N - s[x]] - t_tree[N - s[x]];
        ans -= ans1[N - s[x]];
    }
    ++t[s[x] + N];
    for (int i = G.head[x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa && !G.vis[G.to[i]])
        {
            Dfs(G.to[i], x);
        }
    }
    if (fa == r)
    {
        for (int i = 1; i <= tot_cnt; ++i)
        {
            ++ans1[cnt[i]];
        }
        tot_cnt = 0;
//        memset(t_tree, 0, sizeof(t_tree));
        for (int i = min_num; i <= max_num; ++i)
        {
            t_tree[i + N] = 0;
        }
//        memset(ans1, 0, sizeof(ans1));
    }
    --t[s[x] + N];
    return;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
int min(int a, int b)
{
    return a < b ? a : b;
}

void Graph::Add(int x, int y, int z)
{
    ++tot;
    nxt[tot] = head[x];
    to[tot] = y;
    dis[tot] = z;
    head[x] = tot;
    return;
}
Graph::Graph()
{
    tot = 0;
}
