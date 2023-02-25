#include <stdio.h>
#include <cstring>
#define INF 1000000009

const int MAXN = 205, MAXM = 205;

int min(int a, int b);

struct Edge
{
    int head[MAXN];
    int nxt[MAXM * 2];
    int to[MAXM * 2];
    int dis[MAXM * 2];
    void Add(int x, int y, int c);
    int tot;
};

struct Dinic
{
    Dinic();
    Edge G;
    int queue[MAXN];
    bool vis[MAXN];
    int deep[MAXN];
    void AddEdge(int u, int v, int c);
    void InitGetDeep();
    void GetDeep(int st);
    int GetMaxFlow(int s, int t, int s_f);
    int Dfs(int x, int f, int ed);
};

Dinic Flow;

int main()
{
    int n, m;
    scanf("%d%d", &m, &n);
    int u, v, w;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        Flow.AddEdge(u, v, w);
    }
    int ans = 0;
    ans = Flow.GetMaxFlow(1, n, INF);
    printf("%d", ans);
}

void Edge::Add(int x, int y, int c)
{
    tot++;
    nxt[tot] = head[x];
    to[tot] = y;
    dis[tot] = c;
    head[x] = tot;
    return;
}

Dinic::Dinic()
{
    G.tot = 1;
    return;
}

void Dinic::AddEdge(int u, int v, int c)
{
    G.Add(u, v, c);
    G.Add(v, u, 0);
    return;
}
void Dinic::InitGetDeep()
{
    memset(vis, 0, sizeof(vis));
    memset(deep, 0, sizeof(deep));
    return;
}
void Dinic::GetDeep(int st)
{
    InitGetDeep();
    int head = 0, tail = 1, now;
    vis[st] = 0;
    queue[1] = 1;
    deep[st] = 0;
    while (head < tail)
    {
        head++;
        now = queue[head];
        for (int i = G.head[now]; i; i = G.nxt[i])
        {
            if (!vis[G.to[i]] && G.dis[i] > 0)
            {
                vis[G.to[i]] = true;
                tail++;
                queue[tail] = G.to[i];
                deep[G.to[i]] = deep[now] + 1;
            }
        }
    }
    return;
}
int Dinic::Dfs(int x, int f, int ed)
{
    if (x == ed || f == 0) return f;
    int ret = 0, flow;
    for (int i = G.head[x]; i; i = G.nxt[i])
    {
        if (deep[G.to[i]] == deep[x] + 1 && G.dis[i] > 0 && (flow = Dfs(G.to[i], min(f, G.dis[i]), ed)))
        {
            ;
            G.dis[i] -= flow;
            G.dis[i ^ 1] += flow;
            ret += flow;
            f -= flow;
            if (!f) break;
        }
    }
    return ret;
}
int Dinic::GetMaxFlow(int s, int t, int s_f)
{
    int max_flow = 0;
    GetDeep(s);
    while (deep[t])
    {
        max_flow += Dfs(1, s_f, t);
        GetDeep(s);
    }
    return max_flow;
}

int min(int a, int b)
{
    return a < b ? a : b;
}
