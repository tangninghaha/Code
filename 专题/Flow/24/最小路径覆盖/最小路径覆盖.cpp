#include <cstdio>

/* Constant */
const int MAXN = 405;
const int MAXM = 6405;
const int INF = 1 << 30;

/* Graph */
struct Graph
{
    int head[MAXN];
    int nxt[MAXM * 2];
    int to[MAXM * 2];
    int f[MAXM * 2];
    int tot;
    void Add(int, int, int);

    Graph();
};
Graph::Graph()
{
    tot = 1;
}
void Graph::Add(int _u, int _v, int _f)
{
    ++tot;
    to[tot] = _v;
    nxt[tot] = head[_u];
    f[tot] = _f;
    head[_u] = tot;
    return;
}

/* Declaration */
int main();
int GetMaxFlow(int, int);
void Bfs(int, int);
int Dfs(int, int, int, int);
int Min(int, int);
void Upload(int, int);

void Dfs2(int);

/* Variable */
Graph G;
int dis[MAXN];
int queue[MAXN];
int cur[MAXN];
int n, m;
bool pd;
int num[MAXN];

bool pdd[MAXN];

/* Definition */
int main()
{
    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &u, &v);
        G.Add(u, v + n, 1);
        G.Add(v + n, u, 0);
    }
    int ed = 2 * n + 1;
    for (int i = 1; i <= n; ++i)
    {
        G.Add(0, i, 1);
        G.Add(i, 0, 0);
        G.Add(i + n, ed, 1);
        G.Add(ed, i + n, 0);
    }
    int ans = n - GetMaxFlow(0, ed);
    for (int i = G.head[0]; i; i = G.nxt[i])
    {
        if (!G.f[i])
        {
            pdd[G.to[i]] = true;
        }
    }
    for (int i = G.head[ed]; i; i = G.nxt[i])
        if (G.f[i])
            pdd[G.to[i]] = true;
    for (int i = 1; i <= n; ++i)
    {
        if (pdd[i] && !pdd[i + n])
        {
            Dfs2(i);
            printf("\n");
        }
    }
    printf("%d", ans);
    return 0;
}
int GetMaxFlow(int s, int t)
{
    int max_flow = 0;
    Bfs(s, t);
    while (dis[s] < n * 2 + 1)
    {
        for (int i = s; i <= t; ++i)
        {
            cur[i] = G.head[i];
        }
        max_flow += Dfs(s, s, t, INF);
    }
    return max_flow;
}
void Bfs(int s, int t)
{
    queue[1] = t;
    int head = 0, tail = 1;
    int now;
    for (int i = s; i <= t; ++i)
    {
        dis[i] = n * 2 + 2;
    }
    dis[t] = 0;

    while (head < tail)
    {
        ++head;
        now = queue[head];
        for (int i = G.head[now]; i; i = G.nxt[i])
        {
            if (!(i & 1))
                continue;
            if (dis[G.to[i]] > dis[now] + 1)
            {
                dis[G.to[i]] = dis[now] + 1;
                ++tail;
                queue[tail] = G.to[i];
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        ++num[dis[i]];
    }
    return;
}
int Dfs(int s, int now, int t, int flow)
{
    if (now == t)
    {
        return flow;
    }
    int f;
    int ret = 0;
    bool ok = false;
    for (int i = cur[now]; i; i = G.nxt[i])
    {
        if (G.f[i] > 0 && dis[G.to[i]] == dis[now] - 1)
        {
            ok = true;
            f = Dfs(s, G.to[i], t, Min(flow, G.f[i]));
            cur[now] = i;
            G.f[i] -= f;
            G.f[i ^ 1] += f;
            flow -= f;
            ret += f;
            if (flow == 0)
            {
                return ret;
            }
        }
    }
    if (!ok)
        Upload(now, s);

    return ret;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
void Upload(int now, int s)
{
    int minn = n;
    for (int i = G.head[now]; i; i = G.nxt[i])
    {
        if (G.f[i] > 0)
        {
            minn = Min(minn, dis[G.to[i]] + 1);
        }
    }
    --num[dis[now]];
    if (!num[dis[now]])
    {
        dis[s] = n * 2 + 2;
    }
    dis[now] = minn;
    ++num[minn];
}
void Dfs2(int _x)
{
    printf("%d ", _x);
    if (!pdd[_x] && pdd[_x + n])
        return;
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.f[i])
            continue;
        Dfs2(G.to[i] - n);
        break;
    }
    return;
}
