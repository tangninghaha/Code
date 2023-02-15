#include <stdio.h>
const int MAXN = 1e4 + 1;
int f[MAXN];
int a[MAXN];
int max(int a, int b);
template <typename T> void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
    return;
}
struct S
{
    int num;
    int bh;
};
S x[MAXN];
bool operator<(const S &a, const S &b)
{
    return a.num == b.num ? a.bh < b.bh : a.num < b.num;
}
bool operator>(const S &a, const S &b)
{
    return a.num == b.num ? a.bh > b.bh : a.num > b.num;
}
template <typename Type> void Qsort(int l, int r, Type *a)
{
    int i = l, j = r;
    Type mid = a[(l + r) >> 1];
    while (i <= j)
    {
        while (a[i] < mid)
            ++i;
        while (a[j] > mid)
            --j;
        if (i <= j)
        {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort<Type>(i, r, a);
    if (l < j)
        Qsort<Type>(l, j, a);
    return;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        x[i].num = a[i];
        x[i].bh= i;
    }
    Qsort(1, n, x);
    for (int i = 1; i <= n; ++i)
    {
        a[x[i].bh] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        f[i] = 1;
        for (int j = 1; j < i; ++j)
        {
            if (a[j] >= a[i])
            {
                f[i] = max(f[i], f[j] + 1);
            }
        }
        printf("%d ", f[i]);
    }
    return 0;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
