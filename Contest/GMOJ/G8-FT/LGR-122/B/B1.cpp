#include <cstdio>

/* Constant */
const int MAXN = 5005;

/* Class */
class Graph
{
    public:
        int head[MAXN];
        int nxt[MAXN];
        int to[MAXN];
        int tot;
        void Add(int _u, int _v);
};

/* Declaration */
long long Dfs(int sz);
void Init(int _x);
int main();
void Bj(int _x);
void Rbj(int _x);
void Qsort(int l, int r);
void Swap(int& _a, int& _b);

/* Variable */
int f[MAXN];
long long g[MAXN];
int size[MAXN];
int fa[MAXN];
bool vis[MAXN];
int fsize[MAXN];
Graph G;
int n;

/* Definition */
void Init(int _x)
{
    size[_x] = 1;
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] == fa[_x])
            continue;
        fa[G.to[i]] = _x;
        Dfs(G.to[i]);
        size[_x] += size[G.to[i]];
    }
    return;
}
long long Dfs(int sz)
{
    if (g[sz])
        return g[sz];
    for (int i = 1; i < rk[sz]; ++i)
    {
        if (f[i] + f[size[1] - fsize[i] + 1] < f[sz])
        {
            if (Find(fsize[i]))
            {
                if (Find(size[1] - fsize[i] + 1))
                {
                }
            }
        }
    }
}
