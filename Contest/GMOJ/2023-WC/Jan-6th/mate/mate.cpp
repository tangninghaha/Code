#include <cstdio>

/* Constant */
const int MAXN = 11;
const int mod = 1e9 + 7;

/* Declaration */
int main();
void Dfs(int);

/* Variable */
int n, m1, m2;
int p[MAXN];
bool pd[MAXN];
int mate[MAXN][2];
int ans;

/* Definition */
int main()
{
    freopen("mate.in", "r", stdin);
    freopen("mate.out", "w", stdout);
    scanf("%d%d%d", &n, &m1, &m2);
    if (n == 1)
    {
        printf("1");
        return 0;
    }
    int x, y;
    for (int i = 1; i <= m1; ++i)
    {
        scanf("%d%d", &x, &y);
        mate[x][0] = y;
        mate[y][0] = x;
    }
    for (int i = 1; i <= m2; ++i)
    {
        scanf("%d%d", &x, &y);
        mate[x][1] = y;
        mate[y][1] = x;
    }
    Dfs(1);
    printf("%d", ans);
    return 0;
}
void Dfs(int _x)
{
    if (_x > n)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (mate[i][0])
            {
                if (mate[p[mate[i][0]]][0] != p[i])
                {
                    return;
                }
            }
            if (mate[i][1])
            {
                if (mate[p[mate[i][1]]][1] != p[i])
                {
                    return;
                }
            }
        }
        ++ans;
        ans %= mod;
        return;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!pd[i])
        {
            p[_x] = i;
            pd[i] = true;
            Dfs(_x + 1);
            pd[i] = false;
        }
    }
    return;
}
