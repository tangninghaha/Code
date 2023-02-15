#include <stdio.h>

const int MAXN = 5e5 + 5;
int a[MAXN], b[MAXN];

void FileIO();
int main();
int Sovle(int l1, int r1, int l2, int r2, int k);

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
    int type;
    int x, y, z;
    int l1, r1, l2, r2;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &type);
        if (type == 1)
        {
            scanf("%d%d%d", &x, &y, &z);
            if (!x)
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
            printf("%d\n", Sovle(l1, r1, l2, r2, (r2 - l2 + r1 - l1 + 3) / 2));
        }
    }
    return 0;
}
int Sovle(int l1, int r1, int l2, int r2, int k)
{
    if (l1 == r1)
    {
        if (a[l1] >= b[r2])
            return b[k + l2 - 1];
        int lbound = l2, rbound = r2;
        int rk = 0;
        while (lbound <= rbound)
        {
            int mid = (lbound + rbound) >> 1;
            if (a[l1] < b[mid])
            {
                rbound = mid - 1;
            }
            else if (a[l1] >= b[mid])
            {
                rk = mid;
                lbound = mid + 1;
            }
        }
        if (rk == k + l2 - 1)
        {
            return a[l1];
        }
        else
        {
            if (rk < k + l2 - 1)
            {
                return b[k + l2];
            }
            else
            {
                return b[k + l2 - 1];
            }
        }
        return -1;
    }
    if (l2 == r2)
    {
        if (b[l2] >= a[r1])
            return a[k + l1 - 1];
        int lbound = l1, rbound = r1;
        int rk = 0;
        while (lbound <= rbound)
        {
            int mid = (lbound + rbound) >> 1;
            if (b[l2] < a[mid])
            {
                rbound = mid - 1;
            }
            else if (b[l2] >= a[mid])
            {
                rk = mid;
                rbound = mid + 1;
            }
        }
        if (rk == k + l1 - 1)
        {
            return b[l2];
        }
        else
        {
            if (rk < k + l1 - 1)
            {
                return a[k + l1];
            }
            else
            {
                return a[k + l1 - 1];
            }
        }
        return -1;
    }
    int amid = (l1 + r1) / 2;
    int bmid = (l2 + r2) / 2;
    if (a[amid] < b[bmid])
    {
        return Sovle(l1, r1, l2, bmid, k);
    }
    else
    {
        return Sovle(l1, amid, l2, r2, k);
    }
    return -1;
}
