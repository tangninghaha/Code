#include <stdio.h>
const int MAXN = 1e5 + 5;
int sum[MAXN];
int a[MAXN];
int rk[MAXN];
int mid[MAXN];
void Qsort(int l, int r);
int cmp(int i, int j);
void swap(int &a, int &b);
int max(int a, int b);
int min(int a, int b);
int main()
{
    freopen("rotate.in", "r", stdin);
    freopen("rotate.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        sum[i] = sum[i - 1] + (a[i] == i);
        mid[i] = i + a[i];
        rk[a[i]] = i;
    }
    Qsort(1, n);
    int maxn, minn, cnt = 0;
    int ans = sum[n];
    for (int i = 1; i <= n; ++i)
    {
        if (mid[i] != mid[i - 1])
            cnt = 0;
        ++cnt;
        maxn = max(rk[a[i]], a[i]);
        minn = min(rk[a[i]], a[i]);
        ans = max(ans, sum[n] - sum[maxn] + sum[minn - 1] + cnt);
    }
    printf("%d", ans);
    return 0;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
    return;
}
int cmp(int i, int j)
{
    if (mid[i] < mid[j])
        return -1;
    if (mid[i] > mid[j])
        return 1;
	int maxn1 = max(a[i], rk[a[i]]), maxn2 = max(a[j], rk[a[j]]);
    if (maxn1 < maxn2)
        return -1;
    if (maxn1 > maxn2)
        return 1;
    return 0;
}
void Qsort(int l, int r)
{
    int i = l, j = r, mids = (l + r) >> 1;
    while (i <= j)
    {
        while (cmp(i, mids) < 0)
            ++i;
        while (cmp(j, mids) > 0)
            --j;
        if (i <= j)
        {
            swap(a[i], a[j]);
            swap(mid[i], mid[j]);
            if (i == mids)
                mids = j;
            else if(j == mids)
                mids = i;
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
