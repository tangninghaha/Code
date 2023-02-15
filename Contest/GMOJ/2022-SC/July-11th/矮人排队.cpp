#include <stdio.h>
#define INF 1000000010

const int MAXN = 2e5 + 1;

int min(int a, int b);
void swap(int &a, int &b);

struct LineTree1
{
    unsigned long long tr[MAXN * 4];
    void Build(int l, int r, int k, int a[]);
    void Update(int l, int r, int x, int sum, int k); /* 将点 x 的值修改为 sum */
    unsigned long long GetSum(int l, int r, int s, int t, int k); /* l,r:当前 s,t: 目标*/
};
struct LineTree2
{
    int tr[MAXN * 4];
    void Build(int l, int r, int k, int a[]);
    void Update(int l, int r, int x, int sum, int k); /* 将点 x 的值修改为 sum */
    int GetSum(int l, int r, int s, int t, int k); /* l,r:当前 s,t: 目标*/
};
LineTree1 t1;
LineTree2 t2;
int a[MAXN], rk[MAXN];
unsigned long long s[MAXN];
int main()
{
    for (unsigned long long i = 1; i <= 200000; ++i)
    {
        s[i] = s[i - 1] + i * i;
    }
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        rk[a[i]] = i;
    }
    t2.Build(1, n, 1, rk);
    t1.Build(1, n, 1, a);
    int t, x, y, minx;
    unsigned long long ret;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &t, &x, &y);
        if (t == 1)
        {
            t2.Update(1, n, a[x], y, 1);
            t2.Update(1, n, a[y], x, 1);
            t1.Update(1, n, x, a[y], 1);
            t1.Update(1, n, y, a[x], 1);
            swap(a[x], a[y]);
        }
        if (t == 2)
        {
            minx = t2.GetSum(1, n, x, y, 1);
            ret = t1.GetSum(1, n, minx, y - x + minx, 1);
            if (ret == s[y] - s[x - 1])
            {
                printf("YES\n");
            }
            else
            {
                printf("NO\n");
            }
        }
    }
    return 0;
}

void LineTree1::Build(int l, int r, int k, int a[])
{
    if (l == r)
    {
        tr[k] = (unsigned long long) a[l] * a[l];
        return;
    }
    int mid = (l + r) >> 1;
    Build(l, mid, k * 2, a);
    Build(mid + 1, r, k * 2 + 1, a);
    tr[k] = tr[k * 2] + tr[k * 2 + 1];
    return;
}
void LineTree1::Update(int l, int r, int x, int sum, int k)
{
    if (l == x && r == x)
    {
        tr[k] = (unsigned long long) sum * sum;
        return;
    }
    int mid = (l + r) >> 1;
    if (x >= l && x <= mid)
    {
        Update(l, mid, x, sum, k * 2);
    }
    if (x > mid && x <= r)
    {
        Update(mid + 1, r, x, sum, k * 2 + 1);
    }
    tr[k] = tr[k * 2] + tr[k * 2 + 1];
    return;
}
unsigned long long LineTree1::GetSum(int l, int r, int s, int t, int k)
{
    if (s <= l && r <= t)
    {
        return tr[k];
    }
    int mid = (l + r) >> 1;
    unsigned long long ret = 0;
    if (s <= mid) ret += GetSum(l, mid, s, t, k * 2);
    if (t > mid) ret += GetSum(mid + 1, r, s, t, k * 2 + 1);
    return ret;
}
void LineTree2::Build(int l, int r, int k, int a[])
{
    if (l == r)
    {
        tr[k] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    Build(l, mid, k * 2, a);
    Build(mid + 1, r, k * 2 + 1, a);
    tr[k] = min(tr[k * 2], tr[k * 2 + 1]);
    return;
}
void LineTree2::Update(int l, int r, int x, int sum, int k)
{
    if (l == x && r == x)
    {
        tr[k] = sum;
        return;
    }
    int mid = (l + r) >> 1;
    if (x >= l && x <= mid)
    {
        Update(l, mid, x, sum, k * 2);
    }
    if (x > mid && x <= r)
    {
        Update(mid + 1, r, x, sum, k * 2 + 1);
    }
    tr[k] = min(tr[k * 2], tr[k * 2 + 1]);
    return;
}
int LineTree2::GetSum(int l, int r, int s, int t, int k)
{
    if (s <= l && r <= t)
    {
        return tr[k];
    }
    int mid = (l + r) >> 1;
    int ret = INF;
    if (s <= mid) ret = min(ret, GetSum(l, mid, s, t, k * 2));
    if (t > mid) ret = min(ret, GetSum(mid + 1, r, s, t, k * 2 + 1));
    return ret;
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
}
