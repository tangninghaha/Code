#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;

/* Declaration */
int main();
void Dfs(int);
void Msort1(int, int);
void Msort2(int, int);
void Swap(int&, int&);
long long Min(long long, long long);
int Max(int, int);

/* Variable */
int n;
int mid_bh;
int a[MAXN];
int tmp[MAXN];
int c1[MAXN];
int c2[MAXN];
bool lft[MAXN];
long long ans;
long long anss = 1e18;

/* Definition */
void Msort1(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    Msort1(l, mid);
    Msort1(mid + 1, r);
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r)
    {
        if (c1[i] <= c1[j])
        {
            tmp[k] = c1[i];
            ++k;
            ++i;
        }
        else
        {
            ans += mid - i + 1;
            tmp[k] = c1[j];
            ++k;
            ++j;
        }
    }
    while (i <= mid)
    {
        tmp[k] = c1[i];
        ++k;
        ++i;
    }
    while (j <= r)
    {
        tmp[k] = c1[j];
        ++k;
        ++j;
    }
    for (int i_ = l; i_ <= r; ++i_)
    {
        c1[i_] = tmp[i_];
    }
    return;
}
void Msort2(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    Msort2(l, mid);
    Msort2(mid + 1, r);
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r)
    {
        if (c2[i] >= c2[j])
        {
            tmp[k] = c2[i];
            ++k;
            ++i;
        }
        else
        {
            ans += mid - i + 1;
            tmp[k] = c2[j];
            ++k;
            ++j;
        }
    }
    while (i <= mid)
    {
        tmp[k] = c2[i];
        ++k;
        ++i;
    }
    while (j <= r)
    {
        tmp[k] = c2[j];
        ++k;
        ++j;
    }
    for (int i_ = l; i_ <= r; ++i_)
    {
        c2[i_] = tmp[i_];
    }
    return;
}
void Dfs(int x_)
{
    if (x_ > n)
    {
        int n_mid_bh = mid_bh;
        for (int i = 1; i <= n; ++i)
        {
            c1[i] = c2[i] = a[i];
        }
        ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (i > n_mid_bh && lft[i])
            {
                for (int j = i; j > n_mid_bh; --j)
                {
                    Swap(c1[j - 1], c1[j]);
                    Swap(c2[j - 1], c2[j]);
                    ++ans;
                }
                ++n_mid_bh;
            }
        }
        if (n_mid_bh != 1)
            Msort1(1, n_mid_bh - 1);
        if (n_mid_bh != n)
            Msort2(n_mid_bh + 1, n);
        anss = Min(ans, anss);
        return;
    }
    lft[x_] = true;
    Dfs(x_ + 1);
    lft[x_] = false;
    Dfs(x_ + 1);
}
void Swap(int& a_, int& b_)
{
    int temp = a_;
    a_ = b_;
    b_ = temp;
    return;
}
long long Min(long long a_, long long b_)
{
    return a_ < b_ ? a_ : b_;
}
int main()
{
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    scanf("%d", &n);
    int mx = 0;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        if (a[i] > mx)
        {
            mx = a[i];
            mid_bh = i;
        }
    }
    Dfs(1);
    printf("%lld", anss);
    return 0;
}
int Max(int a_, int b_)
{
    return a_ > b_ ? a_ : b_;
}
