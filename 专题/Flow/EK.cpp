#include <stdio.h>
#include <cstring>

const int MAXN = , MAXM = , MAXQ = ;

int min(int a, int b);

struct NetWork
{
    int tot;
    int head[MAXN];
    int nxt[2 * MAXM];
    int to[2 * MAXM];
    int dis[2 * MAXM];

    void Add(int u, int v, int c);
};

struct EK
{
    NetWork G;
    int queue[MAXQ];
    bool vis[MAXN];
    int pre[MAXN];
    int pre_edge[MAXN];

    void AddEdge(int u, int v, int c);
    EK();
    int GetMaxFlow(int s, int t);
    void Init();
};

void NetWork::Add(int u, int v, int c)
{
    ++tot;
    nxt[tot] = head[u];
    to[tot] = v;
    dis[tot] = c;
    head[u] = tot;
    return;
}

void EK::AddEdge(int u, int v, int c)
{
    G.Add(u, v, c);
    G.Add(v, u, 0);
    return;
}
EK::EK()
{
    G.tot = 1;
}
int EK::GetMaxFlow(int s, int t)
{
    Init();

    int head = 0, tail = 1;
    bool GetFlow = false;
    int MaxFlow = 2147483647;
    queue[1] = s;
    pre[s] = 0;
    vis[s] = 1;

    while(head < tail)
    {
        ++head;
        int now = queue[head];

        for (int i = G.head[now]; i; i = G.nxt[i])
        {
            if (G.dis[i] > 0 && !vis[G.to[i]])
            {
                vis[G.to[i]] = 1;
                pre[G.to[i]] = now;
                pre_edge[G.to[i]] = i;
                if (G.to[i] == t)
                {
                    GetFlow = true;
                    break;
                }
                else
                {
                    ++tail;
                    queue[tail] = G.to[i];
                }
            }
        }
        if (GetFlow)
            break;
    }
    if (!GetFlow)
        return 0;

    int x = t;
    while(pre[x])
    {
        MaxFlow = min(MaxFlow, G.dis[pre_edge[x]]);
        x = pre[x];
    }
    x = t;
    while(pre[x])
    {
        G.dis[pre_edge[x]] -= MaxFlow;
        G.dis[pre_edge[x] ^ 1] += MaxFlow;
        x = pre[x];
    }
    return MaxFlow;
}

void EK::Init()
{
    memset(vis, 0, sizeof(vis));
    return;
}

int min(int a, int b)
{
    return a < b ? a : b;
}
