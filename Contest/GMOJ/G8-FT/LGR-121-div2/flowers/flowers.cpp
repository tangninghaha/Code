#include <cstdio>

int a[6];

int main();
void Dfs(int, int);
int Abs(int);

bool pd;
int n;
int x;

int main()
{
    int t;
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        pd = false;
        scanf("%d%d", &n, &x);
        if (!x)
        {
            printf("No\n");
            continue;
        }
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a[i]);
        }
        Dfs(1, 0);
        if (pd)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
int chos = 0;
void Dfs(int i, int t)
{
    if (i > n)
    {
        if (!chos)
            return;
        if (!t)
        {
            pd = true;
            return;
        }
        if (t < 0 && x < 0)
        {
            pd = true;
            return;
        }
        if (t > 0 && x > 0)
        {
            pd = true;
            return;
        }
        if (x < 0)
        {
            int nxt = t - x % t;
            for (int j = 1; j <= n; ++j)
            {
                if (a[j] > nxt)
                {
                    pd = true;
                    return;
                }
            }
        }
        if (x > 0)
        {
            int nxt = (x - 1) % t + 1;
            for (int j = 1; j <= n; ++j)
            {
                if (Abs(a[j]) > nxt)
                {
                    pd = true;
                    return;
                }
            }
        }
        return;
    }
    for (int j = 1; j <= n; ++j)
    {
        if (!chos)
            chos = i;
        Dfs(i + 1, t + j * a[i]);
        if (chos == i)
        {
            chos = 0;
        }
    }
    if (pd)
        return;
    Dfs(i + 1, t);
    if (pd)
        return;
}
int Abs(int _x)
{
    return _x < 0 ? -_x : _x;
}
