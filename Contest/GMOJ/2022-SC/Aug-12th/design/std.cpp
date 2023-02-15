#include <cstdio>
#include <cstring>

/* Constant */
const int MAXN = 1e3 + 5;
const int MAXM = 1e6 + 5;
const int MAXQ = 1e6 + 5;

/* Class */
class Graph
{
    public: 
        int head[MAXN];
        int nxt[MAXM];
        int to[MAXM];
        int dis[MAXM];
        int tot;
        void Add(int, int, int);
};

/* Declaration */
int main();
void FileIO();
void BellmanFord(int, int);
void Swap(int&, int&);

/* Variable */
Graph g;
int INF;
int dist[MAXN];
int queue[MAXQ];
int cnt[MAXN];
bool vis[MAXN];
bool viss[MAXN];
bool pd;

/* Definition */
int main()
{
    FileIO();
    int n, ml, md;
    scanf("%d%d%d", &n, &ml, &md);
    int u, v, w;
    for (int i = 1; i <= ml; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        if (u < v)
        {
            Swap(v, u);
        }
        g.Add(v, u, w);
    }
    for (int i = 1; i <= md; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        if (v > u)
        {
            Swap(u, v);
        }
        g.Add(u, v, -w);
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j < i; ++j)
        {
            g.Add(i, j, 0);
        }
    }
    bool pdd = false;
    for (int i = 1; i <= n; ++i)
    {
        if (!viss[i])
        {
            BellmanFord(n, i);
            if (i == 1 && dist[n] == INF)
            {
                pdd = true;
            }
        }
    }
    if (pd)
    {
        printf("-1");
        return 0;
    }
    else if(pdd)
    {
        printf("-2");
        return 0;
    }
    else
    {
        printf("%d", dist[n] - dist[1]);
        return 0;
    }
    return 0;
}
void FileIO()
{
    freopen("design.in", "r", stdin);
    freopen("design.out", "w", stdout);
    return;
}
void BellmanFord(int n, int s)
{
    memset(dist, 127 / 3, sizeof(dist));
    INF = dist[0];
    int head = 0, tail = 1;
    dist[s] = 0;
    queue[1] = s;
    int now;
    cnt[s] = 0;
    while (head < tail)
    {
        ++head;
        now = queue[head];
        viss[now] = true;
        vis[now] = false;
        for (int i = g.head[now]; i; i = g.nxt[i])
        {
            if (dist[now] + g.dis[i] < dist[g.to[i]])
            {
                dist[g.to[i]] = dist[now] + g.dis[i];
                cnt[g.to[i]] = cnt[now] + 1;
                if (cnt[g.to[i]] >= n)
                {
                    pd = true;
                    return;
                }
                if (!vis[g.to[i]])
                {
                    ++tail;
                    queue[tail] = g.to[i];
                    vis[g.to[i]] = true;
                }
            }
        }
    }
    return;
}
void Graph::Add(int u, int v, int w)
{
    ++tot;
    nxt[tot] = head[u];
    to[tot] = v;
    dis[tot] = w;
    head[u] = tot;
    // printf("%d %d %d\n", u, v, w);
    return;
}
void Swap(int& a_, int& b_)
{
    int tmp = a_;
    a_ = b_;
    b_ = tmp;
    return;
}
