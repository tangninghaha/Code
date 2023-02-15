#include <stdio.h>
#include <math.h>

const int MAXN = 1e3 + 5;
int a[MAXN];
int min(int a, int b);
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        a[i] = i;
    }
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 1; j <= ceil(1.0 * n / i); ++j)
        {
            int tmp = a[(j - 1) * i + 1];
            for (int k = (j - 1) * i + 2; k <= min(j * i, n); ++k)
            {
                a[k - 1] = a[k];
            }
            a[min(j * i, n)] = tmp;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        printf("%d ", a[i]);
    }
    return 0;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
