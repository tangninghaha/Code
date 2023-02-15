#include <stdio.h>
const int MAXN = 701;
long long f[2][MAXN][MAXN];
struct Point
{
    int x;
    int y;
};
bool operator<(Point &a, Point &b);
bool operator>(Point &a, Point &b);
Point input[MAXN];
void Qsort(int l, int r);
void swap(Point &a, Point &b);
int main()
{
    int n;
    long long q;
    scanf("%d%lld", &n, &q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &input[i].x, &input[i].y);
    }
    if (n == 1)
    {
        printf("%d", n);
        return 0;
    }
    Qsort(1, n);
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        f[1][i][0] = 1;
        ans += f[1][i][0];
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j < i; ++j)
        {
            f[0][i][j] = 1;
            ans += f[0][i][j];
        }
    }
    for (int len = 3; len <= n; ++len)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j < i; ++j)
            {
                f[len % 2][i][j] = 0;
                for (int k = 1; k < j; ++k)
                {
                    if ((input[k].x < input[i].x && input[i].x < input[j].x)
                        || (input[j].x < input[i].x && input[i].x < input[k].x))
                    {
                        f[len % 2][i][j] += f[(len - 1) % 2][j][k];
                        f[len % 2][i][j] %= q;
                    }
                }
                ans += f[len % 2][i][j];
                ans %= q;
            }
        }
    }
    printf("%lld", ans % q);
    return 0;
}
void swap(Point &a, Point &b)
{
    Point tmp = a;
    a = b;
    b = tmp;
}
bool operator<(Point &a, Point &b)
{
    return a.y > b.y;
}
bool operator>(Point &a, Point &b)
{
    return a.y < b.y;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    Point mid = input[(l + r) >> 1];
    while (i <= j)
    {
        while (input[i] < mid)
            ++i;
        while (input[j] > mid)
            --j;
        if (i <= j)
        {
            swap(input[i], input[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r);
    if (l < j)
        Qsort(l, j);
    return;
}
