#include <stdio.h>

const int MAXN = 200001, MAXK = 6;
int a[MAXN];
int l[MAXK], r[MAXK];
int tmp[MAXN], tot;
void swap(int &a, int &b);
void Qsort(int a[], int l, int r);

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    int k, p;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &k, &p);
        tot = 0;
        for (int j = 1; j <= k; ++j)
        {
            scanf("%d%d", &l[j], &r[j]);
            for (int ki = l[j]; ki <= r[j]; ++ki)
            {
                ++tot;
                tmp[tot] = a[ki];
            }
        }
        Qsort(tmp, 1, tot);
        printf("%d\n", tmp[p]);
    }
}
void Qsort(int a[], int l, int r)
{
    int i = l, j = r, mid = a[(l + r) >> 1];
    while (i < j)
    {
        while (a[i] < mid) i++;
        while (a[j] > mid) j--;
        if (i <= j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    if (i < r) Qsort(a, i, r);
    if (l < j) Qsort(a, l, j);
    return;
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
