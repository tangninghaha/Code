#include <stdio.h>

void FileIO();
int main();
const int MAXN = 1e5 + 5;
int a[MAXN], b[MAXN];
int tmp[MAXN];

void FileIO()
{
    freopen("median.in", "r", stdin);
    freopen("median.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &b[i]);
    }
    int t, l1, l2, r1, r2, x, y, z;
    int k1, k2, k3;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &t);
        if (t == 1)
        {
            scanf("%d%d%d", &x, &y, &z);
            if (x == 0)
            {
                a[y] = z;
            }
            else
            {
                b[y] = z;
            }
        }
        else
        {
            scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
            k1 = l1;
            k2 = l2;
            k3 = 0;
            while (k1 <= r1 && k2 <= r2)
            {
                if (a[k1] < b[k2])
                {
                    ++k3;
                    tmp[k3] = a[k1];
                    ++k1;
                }
                else
                {
                    ++k3;
                    tmp[k3] = b[k2];
                    ++k2;
                }
            }
            while (k1 <= r1)
            {
                ++k3;
                tmp[k3] = a[k1];
                ++k1;
            }
            while (k2 <= r2)
            {
                ++k3;
                tmp[k3] = b[k2];
                ++k2;
            }
            printf("%d\n", tmp[k3 / 2 + 1]);
        }
    }
    return 0;
}
