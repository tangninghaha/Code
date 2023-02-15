#include <stdio.h>
#include <math.h>

const int MAXN = 1e3 + 5;
int a[MAXN], rk[MAXN];
void swap(int &a, int &b);
int min(int a, int b);
int main()
{
    freopen("data2.txt", "w", stdout);
    for (int n = 1; n <= 1000; ++n)
    {
        printf("%-5d", n);
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
//        int k = 0;
        for (int i = 1; i <= n; ++i)
        {
            printf("%-3d ", a[i]);
//            for (int j = 1; j <= n; ++j)
//            {
//                if (a[i] == j)
//                {
//                    rk[j] = i;
//                }
//            }
        }
//        printf("\n");
//        printf("%d\n", k);
//        for (int i = 1; i <= n; ++i)
//        {
//            printf("(%-3d)%-3d ", i, rk[i]);
//        }
        printf("\n");
    }
    return 0;
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
    return;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
