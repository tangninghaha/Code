#include <stdio.h>

const int MAXM = 3010, MAXN = 3010;
int head[MAXN], to[MAXM * 2], nxt[MAXM * 2], tot;
int v[MAXN];
int f[MAXN][MAXN];
int size[MAXN];
int lim;
int ans;

void Add(int x, int y);
void Dfs(int fa, int x);
int max(int a, int b);

int main()
{
    freopen("tree.in", "r", stdin);
//    freopen("tree.out", "w", stdout);
    int n;
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
    for (int i = 1; i <= lim; i++)
    {
        ans = max(ans, f[1][i]);
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
    size[x] = 1;
    f[x][1] = v[x];
    for (int i = head[x]; i; i = nxt[i])
    {
        if (to[i] == fa) continue;
        Dfs(x, to[i]);
        size[x] += size[to[i]];
        for (int j = 1; j <= size[x]; j++)
        {
            for (int k = 1; k <= j; k++)
            {
                f[x][j] = max(f[x][j], f[to[i]][j - k] + f[x][k]);
            }
        }
    }
}

int max(int a, int b)
{
    return a > b ? a : b;
}

