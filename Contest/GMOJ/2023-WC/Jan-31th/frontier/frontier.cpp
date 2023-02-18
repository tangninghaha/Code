#include <cstdio>

/* Constant */
const int N = 50;

/* Declaration */
int main();

/* Variable */
int a[N + 1][N + 1];

/* Definition */
int main()
{
    freopen("frontier.in", "r", stdin);
    freopen("frontier.out", "w", stdout);
    int n, q;
    scanf("%d", &n);
    scanf("%d%d", &n, &q);
    int type, x, y, z;
    int opt;
    for (int i = 1; i <= q; ++i)
    {
        scanf("%d", &opt);
        if (opt == 1)
        {
            scanf("%d%d%d%d", &type, &x, &y, &z);
            if (type == 1)
            {
                for (int j = x; j <= x + z; ++j)
                {
                    for (int k = y; k <= y + z - j + x; ++k)
                    {
                        ++a[j][k];
                    }
                }
            }
            if (type == 2)
            {
                for (int j = x; j <= x + z; ++j)
                {
                    for (int k = y; k >= y - z + j - x; --k)
                    {
                        ++a[j][k];
                    }
                }
            }
            if (type == 3)
            {
                for (int j = x; j >= x - z; --j)
                {
                    for (int k = y; k <= y + z - x + j; ++k)
                    {
                        ++a[j][k];
                    }
                }
            }
            if (type == 4)
            {
                for (int j = x; j >= x - z; --j)
                {
                    for (int k = y; k >= y - z + x - j; --k)
                    {
                        ++a[j][k];
                    }
                }
            }
        }
        else
        {
            scanf("%d%d", &x, &y);
            printf("%d\n", a[x][y]);
        }
        return 0;
    }
    return 0;
}
