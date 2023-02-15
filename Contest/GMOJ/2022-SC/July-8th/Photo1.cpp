#include <stdio.h>

const int MAXM = 1e5 + 5, MAXN = 2e5 + 5;
int l[MAXM], r[MAXM];
int f[MAXN], max1[MAXN], max2[MAXN];

int max(int a, int b);
void Qsort(int l, int r);
bool cmp(int l1, int r1, int l2, int r2);
void swap(int &a, int &b);

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &l[i], &r[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        max1[i] = n;
    }
    Qsort(1, m);
    for (int i = 1; i <= m; ++i)
    {
        for (int j = r[i]; j >= 1; --j)
        {
            if (max1[j] == n)
            {
                max1[j] = l[i];
            }
            else break;
        }
    }
    for (int i = m; i >= 1; --i)
    {
        for (int j = r[i] + 1; j <= n; ++j)
        {
            if (max2[j] == n)
            {
                max2[j] = l[i];
            }
            else break;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j < max1[i]; ++j)
        {
            f[i] = max(f[i], f[j] + 1);
        }
        printf("%d\n", f[i]);
    }
    printf("%d", f[n]);
}

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
    return;
}
bool cmp(int i, int j)
{
    return l[i] == l[j] ? (r[i] < r[j]) : (l[i] < l[j]);
}
void Qsort(int ll, int rr)
{
    int i = ll, j = rr, mid = (ll + rr) >> 1;
    while (i < j)
    {
        while (cmp(i, mid)) ++i;
        while (cmp(mid, j)) --j;
        if (i <= j)
        {
            swap(l[i], l[j]);
            swap(r[i], r[j]);
            if (i == mid)
                mid = j;
            else if(j == mid)
                mid = i;
            ++i;
            --j;
        }
    }
    if (i < rr) Qsort(i, rr);
    if (ll < j) Qsort(ll, j);
}

int max(int a, int b)
{
    return a > b ? a : b;
}
