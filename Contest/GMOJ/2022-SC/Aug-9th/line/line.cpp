#include <cstdio>
#include <math.h>
const int MAXN = 2005;
const int MAXM = 2e6 + 5;
const double EXP = 1e-15;

class Point
{
    public:
        int x;
        int y;
};
Point a[MAXN];
double dg[MAXM];
int Cmp(const double& aa, const double& bb);

void FileIO();
int main();
void Qsort(int l, int r);
void Swap(double &aa, double &bb);

int Cmp(const double& aa, const double& bb)
{
    if (aa < bb)
    {
        if (bb - aa <= EXP)
            return 0;
        else
            return -1;
    }
    if (aa > bb)
    {
        if (aa - bb <= EXP)
            return 0;
        else
            return 1;
    }
    return 0;
}
void FileIO()
{
    freopen("line.in", "r", stdin);
    freopen("line.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &a[i].x, &a[i].y);
    }
    int tot = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            ++tot;
            dg[tot] = atan2(a[j].y - a[i].y, a[j].x - a[i].x);
            while (Cmp(dg[tot], 0) < 0)
            {
                dg[tot] += M_PI;
            }
            while (Cmp(dg[tot], M_PI) >= 0)
            {
                dg[tot] -= M_PI;
            }
        }
    }
    Qsort(1, tot);
    if (tot & 1)
        printf("%.13lf", dg[(tot + 1) / 2]);
    else
        printf("%.13lf", (dg[tot / 2] + dg[tot / 2 + 1]) / 2.0);
    return 0;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    double mid = dg[(l + r) >> 1];
    while (i <= j)
    {
        while (Cmp(dg[i], mid) < 0)
            ++i;
        while (Cmp(dg[j], mid) > 0)
            --j;
        if (i <= j)
        {
            Swap(dg[i], dg[j]);
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
void Swap(double &aa, double &bb)
{
    double tmp = aa;
    aa = bb;
    bb = tmp;
    return;
}
