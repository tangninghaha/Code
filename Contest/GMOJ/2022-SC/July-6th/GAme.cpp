#include <stdio.h>
#define INF 1000000010

const int MAXN = 2005;
int f[MAXN][MAXN];
int a[MAXN], b[MAXN];

int min(int a, int b);

int main()
{
    int l1, l2;
    scanf("%d%d", &l1, &l2);
    for (int i = l1; i >= 1; --i)
    {
        scanf("%d", &a[i]);
        --a[i];
    }
    for (int i = l2; i >= 1; --i)
    {
        scanf("%d", &b[i]);
        --b[i];
    }
    for (int i = 1; i <= l1; ++i)
    {
        for (int j = 1; j <= l2; ++j)
        {
            f[i][j] = INF;
            if (i == 1 && j == 1) f[i][j] = a[i] * b[j];
            if (i > 1 && j > 1) f[i][j] = min(f[i][j], f[i - 1][j - 1] + a[i] * b[j]);
            if (i > 1) f[i][j] = min(f[i][j], f[i - 1][j] + a[i] * b[j]);
            if (j > 1) f[i][j] = min(f[i][j], f[i][j - 1] + a[i] * b[j]);
            // printf("%d ", f[i][j]);
        }
        // printf("\n");
    }
    printf("%d", f[l1][l2]);
    return 0;
}

int min(int a, int b)
{
    return a < b ? a : b;
}
