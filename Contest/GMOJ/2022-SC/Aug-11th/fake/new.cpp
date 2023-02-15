#include <cstdio>

/* Constant */
const int MAXN = 3e5 + 5;
const int MAXM = 3e5 + 5;

/* namespace */
namespace Heap
{
    struct dui
    {
        public:
            int dist;
            int key;
            int lson;
            int rson;
            int bh;
    };
    dui t[MAXN];
    int size;
    int Merge(int, int);
    int DeleteRoot(int);
};

/* Class */
class Graph
{
    public:
        int head[MAXN];
        int to[MAXN * 2];
        int nxt[MAXN * 2];
        int tot;
        void Add(int u, int v);
};
class Plan
{
    public:
        int st;
        int ed;
};

/* Definition */
void Dfs(int);
void Init(int);
int main();
template <typename T> void Swap(T&, T&);
void FileIO();

/* Variable */
int ans;
int top[MAXN];
int dep[MAXN];
int fa[MAXN];
Graph g;
int c[MAXN];
Plan p[MAXM];
int cnt[MAXN];
int now_num[MAXN];

/* Definition */
int main()
{
    FileIO();
    int n, m;
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &c[i]);
    }
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d", &u, &v);
        g.Add(u, v);
        g.Add(v, u);
    }
    Init(1);
    Heap::size = 0;
    ans = m;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &p[i].st, &p[i].ed);
        if (dep[p[i].st] > dep[p[i].ed])
        {
            Swap(p[i].st, p[i].ed);
        }
        --cnt[fa[p[i].st]];
        ++cnt[p[i].ed];
        Heap::t[++Heap::size].dist = 0;
        Heap::t[Heap::size].key = dep[p[i].st];
        Heap::t[Heap::size].lson = 0;
        Heap::t[Heap::size].rson = 0;
        Heap::t[Heap::size].bh = p[i].st;
        top[p[i].ed] = Heap::Merge(Heap::size, top[p[i].ed]);
    }
    Dfs(1);
    printf("%d", ans);
    return 0;
}
void Init(int x_)
{
    dep[x_] = dep[fa[x_]] + 1;
    for (int i = g.head[x_]; i; i = g.nxt[i])
    {
        if (g.to[i] != fa[x_])
        {
            fa[g.to[i]] = x_;
            Init(g.to[i]);
        }
    }
    return;
}
void Dfs(int x_)
{
    for (int i = g.head[x_]; i; i = g.nxt[i])
    {
        if (g.to[i] == fa[x_])
            continue;
        Dfs(g.to[i]);
        now_num[x_] += now_num[g.to[i]];
        top[x_] = Heap::Merge(top[x_], top[g.to[i]]);
    }
    now_num[x_] += cnt[x_];
    for (; now_num[x_] > c[x_]; --now_num[x_])
    {
        --ans;
        ++cnt[fa[Heap::t[top[x_]].bh]];
        top[x_] = Heap::DeleteRoot(top[x_]);
    }
    return;
}
int Heap::Merge(int a_, int b_)
{
    if (!a_ || !b_)
        return a_ | b_;
    if (t[a_].key > t[b_].key)
    {
        Swap(a_, b_);
    }
    t[a_].rson = Heap::Merge(b_, t[a_].rson);
    if (t[t[a_].lson].dist < t[t[a_].rson].dist)
    {
        Swap(t[a_].lson, t[a_].rson);
    }
    t[a_].dist = t[t[a_].rson].dist + 1;
    return a_;
}
int Heap::DeleteRoot(int root_)
{
    return Heap::Merge(t[root_].lson, t[root_].rson);
}
template <typename T> void Swap(T& a_, T& b_)
{
    T tmp = a_;
    a_ = b_;
    b_ = tmp;
    return;
}
void Graph::Add(int u, int v)
{
    ++tot;
    nxt[tot] = head[u];
    to[tot] = v;
    head[u] = tot;
    return;
}
void FileIO()
{
    freopen("fake.in", "r", stdin);
    freopen("fake.out", "w", stdout);
    return;
}
