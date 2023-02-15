#include <stdio.h>
const int MAXN = 2e5 + 5;
int s[3][MAXN];
int a[3][MAXN];
void Qsort(int l, int r);
void swap(int &a, int &b);
int head[3][MAXN], nxt[3][MAXN], to[3][MAXN], tot[3];
int queue[MAXN];
bool vis[MAXN];
int heads, tails;
void Add(int l, int x, int y);

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            scanf("%d", &a[i][j]);
            ++s[i][a[i][j]];
        }
    }
    Qsort(1, n);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            Add(i, a[i][j], j);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!s[1][i])
        {
            if (!vis[i])
            {
                ++tails;
                queue[tails] = i;
                vis[i] = true;
            }
            for (int j = head[2][i]; j; j = nxt[2][j])
            {
                if (!vis[to[2][j]])
                {
                    ++tails;
                    queue[tails] = to[2][j];
                    vis[to[2][j]] = true;
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!s[2][i])
        {
            if (!vis[i])
            {
                ++tails;
                queue[tails] = i;
                vis[i] = true;
            }
            for (int j = head[1][i]; j; j = nxt[1][j])
            {
                if (!vis[to[1][j]])
                {
                    ++tails;
                    queue[tails] = to[1][j];
                    vis[to[1][j]] = true;
                }
            }
        }
    }
    int ans = 0;
    while (heads < tails)
    {
        ++heads;
        ++ans;
        int col = queue[heads];
        --s[0][a[0][col]];
        --s[1][a[1][col]];
        --s[2][a[2][col]];
        if (!s[0][a[0][col]])
        {
            for (int j = head[1][col]; j; j = nxt[1][j])
            {
                if (!vis[to[1][j]])
                {
                    ++tails;
                    queue[tails] = to[1][j];
                    vis[to[1][j]] = true;
                }
            }
            for (int j = head[2][col]; j; j = nxt[2][j])
            {
                if (!vis[to[2][j]])
                {
                    ++tails;
                    queue[tails] = to[2][j];
                    vis[to[2][j]] = true;
                }
            }
        }
        if (!s[1][a[1][col]])
        {
            for (int j = head[2][a[1][col]]; j; j = nxt[2][j])
            {
                if (!vis[to[2][j]])
                {
                    ++tails;
                    queue[tails] = to[2][j];
                    vis[to[2][j]] = true;
                }
            }
            if (!vis[a[1][col]])
            {
                ++tails;
                queue[tails] = a[1][col];
                vis[a[1][col]] = true;
            }
        }
        if (!s[2][a[2][col]])
        {
            for (int j = head[1][a[2][col]]; j; j = nxt[1][j])
            {
                if (!vis[to[1][j]])
                {
                    ++tails;
                    queue[tails] = to[1][j];
                    vis[to[1][j]] = true;
                }
            }
            if (!vis[a[2][col]])
            {
                ++tails;
                queue[tails] = a[2][col];
                vis[a[2][col]] = true;
            }
        }
    }
    printf("%d", ans);
    return 0;
}
void Add(int l, int x, int y)
{
    ++tot[l];
    nxt[l][tot[l]] = head[l][x];
    to[l][tot[l]] = y;
    head[l][x] = tot[l];
    return;
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
void Qsort(int l, int r)
{
    int i = l, j = r, mid = a[0][(l + r) >> 1];
    while (i <= j)
    {
        while (a[0][i] < mid)
            ++i;
        while (a[0][j] > mid)
            --j;
        if (i <= j)
        {
            swap(a[0][i], a[0][j]);
            swap(a[1][i], a[1][j]);
            swap(a[2][i], a[2][j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r);
    if (l < j)
        Qsort(l, j);
    return;
}
