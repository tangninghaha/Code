#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;

/* LineTree */
namespace LineTree
{
    int tr[MAXN * 4];
    int GetMax(int, int, int, int, int);
    void Update(int, int, int, int, int);
    void Clear();
};

/* Declaration */
int main();
void LSH(int);
void Qsort(int, int);
void Swap(int&, int&);
int Max(int, int);

/* Variable */
int a[MAXN];
int f[MAXN];
int tmp[MAXN];
int rk[MAXN];

/* Definition */
void LineTree::Clear()
{
    for (int i = 0; i < MAXN * 4; ++i)
    {
        tr[i] = 0;
    }
    return;
}
int LineTree::GetMax(int s, int t, int l, int r, int k)
{
    if (l <= s && t <= r)
    {
        return tr[k];
    }
    int mid = (s + t) >> 1;
    int ret = 0;
    if (mid >= l)
        ret = Max(ret, GetMax(s, mid, l, r, k * 2));
    if (mid + 1 <= r)
        ret = Max(ret, GetMax(mid + 1, t, l, r, k * 2 + 1));
    return ret;
}
void LineTree::Update(int s, int t, int x, int num, int k)
{
    if (s == x && t == x)
    {
        tr[k] = Max(tr[k], num);
        return;
    }
    int mid = (s + t) >> 1;
    if (x <= mid)
        Update(s, mid, x, num, k * 2);
    if (x > mid)
        Update(mid + 1, t, x, num, k * 2 + 1);
    tr[k] = Max(tr[k * 2], tr[k * 2 + 1]);
    return;
}
int main()
{
//    freopen("tribe.in", "r", stdin);
//    freopen("tribe.out", "w", stdout);
    int n;
    int pos;
    scanf("%d%d", &n, &pos);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        tmp[i] = a[i];
    }
    int ans = 0;
//    for (int i = 1; i <= n; ++i)
//    {
//        if (a[i] > a[pos])
//        {
//            ++ans;
//            break;
//        }
//    }
    LSH(n);
    int max_f = 0;
    for (int i = 1; i <= pos; ++i)
    {
        f[i] = LineTree::GetMax(1, n, 1, a[i], 1) + 1;
        LineTree::Update(1, n, a[i], f[i], 1);
        if (max_f < f[i] && i == pos)
        {
            if (a[pos] < a[pos + 1])
            {
                ++ans;
            }
        }
        max_f = Max(max_f, f[i]);
    }
    ans += pos - max_f;
    LineTree::Clear();
    max_f = 0;
    for (int i = n; i > pos; --i)
    {
        f[i] = LineTree::GetMax(1, n, 1, a[i], 1) + 1;
        LineTree::Update(1, n, a[i], f[i], 1);
        max_f = Max(max_f, f[i]);
    }
    ans += n - pos - max_f;
    printf("%d", ans);
    return 0;
}
void LSH(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        rk[i] = i;
    }
    Qsort(1, n);
    int last = -1;
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (tmp[i] != last)
        {
            ++cnt;
            last = tmp[i];
        }
        a[rk[i]] = cnt;
    }
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    int mid = tmp[(l + r) >> 1];
    while (i <= j)
    {
        while (tmp[i] < mid)
            ++i;
        while (tmp[j] > mid)
            --j;
        if (i <= j)
        {
            Swap(tmp[i], tmp[j]);
            Swap(rk[i], rk[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r);
    if (l < j)
        Qsort(l, j);
}
void Swap(int& _a, int& _b)
{
    int temp = _a;
    _a = _b;
    _b = temp;
    return;
}
int Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
