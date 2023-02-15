#include <stdio.h>

const int MAXN = 1e6 + 5;
int head[MAXN], nxt[2 * MAXN], to[2 * MAXN], tot, dis[2 * MAXN];
int n;
int ans = 2147483647;

void Add(int a, int b);
void Dfs(int x);
int min(int a, int b);

int main()
{
    int m;
    scanf("%d%d", &n, &m);
    int u, v, w;
    for (int i = 0; i < n; i++)
    {
        scanf ("%d%d%d", &u, &v, &w);
        Add(u, v, w);
        Add(v, u, w);
    }
    
    Dfs(2);
}

void Add(int a, int b, int diss)
{
    tot++;
    nxt[tot] = head[a];
    to[tot] = b;
    dis[tot] = diss;
    head[a] = tot;
}

void Dfs(int x, int w)
{
    if (x > n)
    {
        ans = min(ans, w);
    }
    Dfs(to[i], )
}

int min(int a, int b)
{
    return a < b ? a : b;
}
