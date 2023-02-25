/* Ditch: SAP*/
#include <cstdio>

/* Constant */
const int MAXN = 20005;
const int MAXM = 20005;
const int INF = 1e8 + 5;

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

/* Variable */
Graph G;
int dis[MAXN];
int queue[MAXN];
int cur[MAXN];
int n, m;
bool pd;
int num[MAXN];

/* Definition */
int main()
{
    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    scanf("%d%d", &m, &n);
    int u, v, w;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        G.Add(u, v, w);
        G.Add(v, u, 0);
    }

    printf("%d", GetMaxFlow(1, n));
    return 0;
}
int GetMaxFlow(int s, int t)
{
    int max_flow = 0;
    Bfs(1, n);
    while (dis[s] < n)
    {
        for (int i = 1; i <= n; ++i)
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
    for (int i = 1; i <= n; ++i)
    {
        dis[i] = n;
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
//            if (!f)
//                continue;
            cur[now] = i;
            G.f[i] -= f;
            G.f[i ^ 1] += f;
            flow -= f;
            ret += f;
            if (flow == 0)
            {
//                Upload(now, s);
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
        dis[s] = n;
    }
    dis[now] = minn;
    ++num[minn];
}
