#include <stdio.h>

const int MAXM = 3010, MAXN = 3010;
int head[MAXN], to[MAXM * 2], nxt[MAXM * 2], tot;
int v[MAXN];
int bag_v[MAXN], bag_w[MAXN]; //Weight: bag_w Value: bag_v
int f[MAXN];

void Add(int x, int y);
void Dfs(int fa, int x);
int max(int a, int b);
int min(int a, int b);

int main()
{
    freopen("tree.in", "r", stdin);
//    freopen("tree.out", "w", stdout);
    int n, lim;
    scanf("%d%d", &n, &lim);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &v[i]);
    }
    int u, v;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &u, &v);
        Add(u, v);
        Add(v, u);
    }
    Dfs(0, 1);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = lim; j >= 0; j--)
        {
            if (j >= bag_w[i])
            {
                f[j] = max(f[j], f[j - bag_w[i]] + bag_v[i]);
                ans = max(ans, f[j]);
            }
        }
    }
    printf("%d", ans);
}

void Add(int x, int y)
{
    tot++;
    nxt[tot] = head[x];
    to[tot] = y;
    head[x] = tot;
}

void Dfs(int fa, int x)
{
    bag_w[x] = bag_w[fa] + 1;
    bag_v[x] = bag_v[fa] + v[x];
    for (int i = head[x]; i; i = nxt[i])
    {
        if (to[i] == fa) continue;
        Dfs(x, to[i]);
    }
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}
