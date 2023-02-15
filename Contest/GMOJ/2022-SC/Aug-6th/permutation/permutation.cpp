#include <stdio.h>

void FileIO();
int main();

const int MAXN = 300005;
int a[MAXN];
int rk[MAXN];

void FileIO()
{
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i)
    {
        int n;
        scanf("%d", &n);
        for (int j = 1; j <= n; ++j)
        {
            scanf("%d", &a[j]);
        }
        for (int j = 1; j <= n; ++j)
        {
            rk[a[j]] = j;
        }
        int x;
        bool pd = false;
        for (int j = 1; j <= n; ++j)
        {
            for (int k = j + 1; k <= n; ++k)
            {
                if (!((j + k) % 2))
                {
                    x = (j + k) / 2;
                    if (rk[x] > rk[j] && rk[x] < rk[k])
                    {
                        pd = true;
                        break;
                    }
                }
            }
            if (pd)
                break;
        }
        if (pd)
            printf("YES\n");
        else
            printf("NO\n");
    }
}
