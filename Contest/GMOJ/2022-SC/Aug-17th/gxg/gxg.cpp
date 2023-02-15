#include <cstdio>
#include <stdlib.h>
#include <ctime>

const int MAXN = 1005;
int a[MAXN];
int pre(int x);
int nxt(int x);
int n;

int main()
{
    freopen("gxg.in", "r", stdin);
    freopen("gxg.out", "w", stdout);
    srand(time(0));
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    bool pd = false;
    int ans = 0;
    while (true)
    {
        pd = false;
        for (int i = 1; i <= n; ++i)
        {
            if (a[i] > 1)
            {
                ans += a[i] - 1;
                if (rand() & 1)
                {
                    a[nxt(i)] += a[i] - 1;
                    a[i] = 1;
                }
                else
                {
                    a[pre(i)] += a[i] - 1;
                    a[i] = 1;
                }
                pd = true;
            }
        }
        if (!pd)
        {
            break;
        }
    }
    printf("%d", ans);
    return 0;
}

int pre(int x)
{
    return x == 1 ? n : x - 1;
}
int nxt(int x)
{
    return x == n ? 1 : x + 1;
}
