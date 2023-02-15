#include <cstdio>

/* Constant */
const int MAXN = 5e5 + 5;
const int MAXM = 5e5 + 5;

/* Class */
class Graph
{
    public:
        int head[MAXN];
        int to[MAXM];
        int nxt[MAXM];
        int deg[MAXN];
        int tot;
        void Add(int u, int v);
};
class Queue
{
    public:
        int queue[MAXN * 2][2];
        int head;
        int tail;
};

/* Declaration */
int main();
void Bfs();
int Max(int, int);
int Min(int, int);
void FileIO();

/* Variable */
int f[MAXN][2];
bool vis[MAXN][2];
Graph g;
Queue q;

/* Declaration */
void FileIO()
{
    freopen("idioms.in", "r", stdin);
    freopen("idioms.out", "w", stdout);
    return;
}
int Max(int a_, int b_)
{
    return a_ > b_ ? a_ : b_;
}
int Min(int a_, int b_)
{
    return a_ < b_ ? a_ : b_;
}
int main()
{
    FileIO();
    int m, n;
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &u, &v);
        g.Add(v, u);
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!g.deg[i])
        {
            q.queue[++q.tail][0] = i;
            q.queue[q.tail][1] = 0;
            q.queue[++q.tail][0] = i;
            q.queue[q.tail][1] = 1;
        }
        else
        {
            f[i][0] = -1;
            f[i][1] = -1;
        }
    }
    Bfs();
    for (int i = 1; i <= n; ++i)
    {
        printf("%d\n", f[i][0]);
    }
    return 0;
}
void Bfs()
{
    int now, pl;
    while (q.head < q.tail)
    {
        now = q.queue[++q.head][0];
        pl = q.queue[q.head][1];
        // vis[now][pl] = false;
        for (int i = g.head[now]; i; i = g.nxt[i])
        {
            if (f[g.to[i]][!pl] == -1 && pl)
            {
                f[g.to[i]][!pl] = f[now][pl] + 1;
                ++q.tail;
                q.queue[q.tail][0] = g.to[i];
                q.queue[q.tail][1] = !pl;
            }
            else if (!pl)
            {
                --g.deg[g.to[i]];
                if (!g.deg[g.to[i]])
                {
                    f[g.to[i]][!pl] = f[now][pl] + 1;
                    if (!vis[g.to[i]][!pl])
                    {
                        ++q.tail;
                        q.queue[q.tail][0] = g.to[i];
                        q.queue[q.tail][1] = !pl;
                        vis[g.to[i]][!pl] = true;
                    }
                }

            }
        }
    }
    return;
}
void Graph::Add(int u, int v)
{
    ++tot;
    nxt[tot] = head[u];
    to[tot] = v;
    head[u] = tot;
    ++deg[v];
    return;
}
