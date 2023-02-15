#include <stdio.h>

const int MAXN = 1e5 + 5;
int a[MAXN];
int tmp[MAXN];
int ba[MAXN], ba_tot = 0;
int bd[MAXN], bd_tot = 0;
bool vis[MAXN];
char cha[5];
void Qsort(int l, int r, int *aa);
void swap(int &a, int &b);
int min(int a, int b);
long long max(long long a, long long b);
int Find(int x);
int n, m;

int main()
{
//    freopen("card.in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", cha);
        if (cha[0] == 'A')
        {
            ++ba_tot;
            scanf("%d", &ba[ba_tot]);
        }
        if (cha[0] == 'D')
        {
            ++bd_tot;
            scanf("%d", &bd[bd_tot]);
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &a[i]);
    }
    Qsort(1, m, a);
    Qsort(1, ba_tot, ba);
    Qsort(1, bd_tot, bd);
    int ed = min(ba_tot, m);
    long long ans = 0;
    long long maxa = 0, minb = 0;
    int nxta = m, nxtb = 1;
    for (int i = 1; i <= ed; ++i)
    {
        if ((a[nxta] < ba[1] || a[m] < ba[nxtb]) && m - nxta < ba_tot)
            break;
        maxa += a[nxta];
        minb += ba[nxtb];
        ans = max(ans, maxa - minb);
        --nxta;
        ++nxtb;
    }
    if (m > n)
    {
        long long x = 0;
        int ns = 1;
        bool pd = false;
        for (int i = 1; i <= bd_tot; ++i)
        {
            while ((vis[ns] || a[ns] <= bd[i]) &&  ns <= m)
            {
                ++ns;
            }
            if (ns > m)
            {
                pd = true;
                break;
            }
            vis[ns] = true;
            x += a[ns];
        }
        if (!pd)
        {
            int newm = 0;
            long long suma = 0;
            for (int i = 1; i <= m; ++i)
            {
                if (!vis[i])
                {
                    ++newm;
                    a[newm] = a[i];
                    suma += a[newm];
                }
            }
            m = newm;
            nxta = 1;
            maxa = 0;
            minb = 0;
            bool pd = false;
            for (int i = 1; i <= ba_tot; ++i)
            {
                while (a[nxta] < ba[i] && nxta <= m)
                {
                    ++nxta;
                }
                if (nxta > m)
                {
                    pd = true;
                    break;
                }
                maxa += a[nxta];
                minb += ba[i];
                ans = max(ans, maxa - minb);
                ++nxta;
            }
            if (!pd)
            {
                ans = max(ans, suma - minb);
            }
        }
    }
    printf("%lld", ans);
}
void Qsort(int l, int r, int *aa)
{
    int i = l, j = r, mid = aa[(l + r) >> 1];
    while (i < j)
    {
        while (aa[i] < mid)
            ++i;
        while (aa[j] > mid)
            --j;
        if (i <= j)
        {
            swap(aa[i], aa[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r, aa);
    if (l < j)
        Qsort(l, j, aa);
    return;
}
void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
long long max(long long a, long long b)
{
    return a > b ? a : b;
}
