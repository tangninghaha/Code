#include <stdio.h>
const int MAXN = 1e5 + 5;
int a[3][MAXN];
int s[3][MAXN];
bool Dfs(int x, int t, int last);
int n;
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            scanf("%d", &a[i][j]);
            ++s[i][a[i][j]];
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if(Dfs(1, i, 0))
        {
            printf("%d", i);
            return 0;
        }
    }
    printf("%d", n);
    return 0;
}
bool Dfs(int x, int t, int last)
{
    if (x > t)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (s[0][i] != s[1][i] || s[1][i] != s[2][i] || s[0][i] != s[2][i])
            {
                return false;
            }
        }
        return true;
    }
    for (int i = last + 1; i <= n; ++i)
    {
        --s[0][a[0][i]];
        --s[1][a[1][i]];
        --s[2][a[2][i]];
        if (Dfs(x + 1, t, i))
        {
            ++s[0][a[0][i]];
            ++s[1][a[1][i]];
            ++s[2][a[2][i]];
            return true;
        }
        ++s[0][a[0][i]];
        ++s[1][a[1][i]];
        ++s[2][a[2][i]];
    }
    return false;
}
