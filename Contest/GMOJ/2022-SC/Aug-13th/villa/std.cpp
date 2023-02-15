#include <cstdio>
#include <cmath>

/* Constant */
const int MAXN = 5e6 + 5;
const int MAXM = 1e5 + 5;

/* Declaration */
int main();
void FileIO();
void Reverse(int*, int);
int Abs(int);
void Swap(int&, int&);

/* Variable */
int a[MAXN];
int sum[MAXN];
int ans[MAXM];

/* Definition */
int main()
{
    FileIO();
    int n, m;
    scanf("%d%d", &n, &m);
    int cnt_nan = 0, cnt_nv = 0;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%1d", &a[i]);
        if (a[i] == 0)
        {
            a[i] = -1;
            ++cnt_nan;
        }
        else
        {
            ++cnt_nv;
        }
        sum[i] = sum[i - 1] + a[i];
    }
    int goal = ceil(1.0 * Abs(cnt_nan - cnt_nv) / m);
    if (sum[n] == 0)
    {
        int num = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (sum[i] == 0)
            {
                ++num;
            }
        }
        goal = num < m;
    }
    int last = 0;
    int tot = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (tot == m - 1)
        {
            ++tot;
            ans[tot] = n - last;
            break;
        }
        if (sum[i] - sum[last] <= goal
            && ceil(1.0 * Abs(sum[n] - sum[i]) / (m - tot - 1)) <= goal)
        {
            ans[++tot] = i - last;
            last = i;
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        printf("%d ", ans[i]);
    }
    printf("\n");
    Reverse(a, n);
    for (int i = 1; i <= n; ++i)
    {
        sum[i] = sum[i - 1] + a[i];
    }
    last = 0;
    tot = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (tot == m - 1)
        {
            ++tot;
            ans[tot] = n - last;
            break;
        }
        if (sum[i] - sum[last] <= goal
            && ceil(1.0 * Abs(sum[n] - sum[i]) / (m - tot - 1)) <= goal)
        {
            ans[++tot] = i - last;
            last = i;
        }
    }
    for (int i = m; i >= 1; --i)
    {
        printf("%d ", ans[i]);
    }
    return 0;
}
void Reverse(int *a_, int n)
{
    for (int i = 1; i <= n / 2; ++i)
    {
        Swap(a_[i], a_[n - i + 1]);
    }
}
int Abs(int x_)
{
    return x_ > 0 ? x_ : -x_;
}
void Swap(int& a_, int& b_)
{
    int tmp = a_;
    a_ = b_;
    b_ = tmp;
    return;
}
void FileIO()
{
    freopen("villa.in", "r", stdin);
    freopen("villa.out", "w", stdout);
    return;
}
