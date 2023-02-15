#include <cstdio>

/* Constant */
const int MAXN = 3e3 + 5;
const int MAXM = 3e3 + 5;
const int INF = 1e8 + 5;

/* Class */
class Segment
{
    public: 
        int l;
        int r;
        int w;
        bool operator<(const Segment&);
};

/* Declaration */
int main();
void FileIO();
void Qsort(int, int);
void Swap(Segment&, Segment&);
int Max(int, int);
int Min(int, int);

/* Variable */
int f[MAXN][MAXN];
Segment a[MAXN];
int min_num[MAXN][MAXN];
int stk[MAXN];

/* Definition */
bool Segment::operator<(const Segment& x_)
{
    return r == x_.r ? l < x_.l : r < x_.r;
}
int main()
{
    FileIO();
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].w);
        }
        Qsort(1, n);
        for (int i = 1; i <= n; ++i)
        {
            if (a[i].l == 1)
            {
                f[i][0] = a[i].w;
            }
            for (int j = 1; j <= n; ++j)
            {
                f[i][j] = INF;
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            stk[i] = 0;
            for (int j = 1; j <= i; ++j)
            {
                if (a[j].r + 1 < a[i].l)
                {
                    stk[i] = j;
                }
            }
        }
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                min_num[i][j] = INF;
            }
            if (a[i].l == 1)
                min_num[i][0] = a[i].w;
        }
        int ans = INF;
        for (int i = 1; i <= n; ++i)
        {
            if (a[i].r == m && a[i].l == 1)
            {
                ans = Min(ans, a[i].w);
            }
            for (int j = 1; j <= n; ++j)
            {
                if (a[j].r >= a[i].r)
                {
                    min_num[i][j] = min_num[i][j - 1];
                    continue;
                }
                if (a[i].l <= a[j].l && a[j].r <= a[i].r)
                {
                    min_num[i][j] = min_num[i][j - 1];
                    continue;
                }
                if (a[j].r + 1 == a[i].l)
                    f[i][j] = Min(f[i][j], Max(min_num[j][stk[i]], a[i].w));
                else if (a[i].l <= a[j].r && a[i].l >= a[j].l)
                    f[i][j] = Min(f[i][j], 
                                  Max(min_num[j][stk[i]], a[i].w + a[j].w));
                min_num[i][j] = Min(f[i][j], min_num[i][j - 1]);
                if (a[i].r == m)
                {
                    ans = Min(ans, f[i][j]);
                }
            }
        }
        printf("%d\n", ans == INF ? -1 : ans);
    }
}
int Max(int a_, int b_)
{
    return a_ > b_ ? a_ : b_;
}
int Min(int a_, int b_)
{
    return a_ < b_ ? a_ : b_;
}
void Qsort(int l, int r)
{
    if (l >= r)
        return;
    int i = l, j = l, k = r + 1;
    Segment mid = a[(l + r) >> 1];
    while (i < k)
    {
        if (a[i] < mid)
        {
            Swap(a[i], a[j]);
            ++i;
            ++j;
        }
        else if (mid < a[i])
        {
            --k;
            Swap(a[i], a[k]);
        }
        else
        {
            ++i;
        }
    }
    Qsort(l, j - 1);
    Qsort(k, r);
    return;
}
void Swap(Segment& a_, Segment& b_)
{
    Segment tmp = a_;
    a_ = b_;
    b_ = tmp;
    return;
}
void FileIO()
{
    freopen("intervals.in", "r", stdin);
    freopen("intervals.out", "w", stdout);
    return;
}
