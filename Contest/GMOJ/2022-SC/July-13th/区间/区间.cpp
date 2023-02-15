#include <stdio.h>
/* ȫ�ֱ��� */
const int MAXN = 1e5 + 5;
int rigt[MAXN];
int f[MAXN];
/* �߶��� */
struct LineTree
{
    int tr[MAXN * 4];
    int GetAns(int l, int r, int s, int t, int k); /* l,r ��ǰ s,tĿ��*/
    void Update(int l, int r, int x, int sum, int k);
};
LineTree t;
/* ���� */
template <typename Type> void Qsort(int l, int r, Type *a);
/* ���� */
int max(int a, int b);
template <typename Type> void swap(Type &a, Type &b);
/* ���� */
struct QuJian
{
    int l;
    int r;
};
QuJian a[MAXN];
bool operator<(const QuJian &a, const QuJian &b);
bool operator>(const QuJian &a, const QuJian &b);
/* ��ɢ�� */
struct LiSan
{
    int x;
    int bh;
};
LiSan tmp[MAXN];
bool operator<(const LiSan &a, const LiSan &b);
bool operator>(const LiSan &a, const LiSan &b);

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &a[i].l, &a[i].r);
    }
    Qsort(1, n, a);
    for (int i = 1; i <= n; ++i)
    {
        tmp[i].x = a[i].r;
        tmp[i].bh = i;
    }
    Qsort(1, n, tmp);
    int last = -1, last_bh = -1;
    for (int i = 1; i <= n; ++i)
    {
        if (tmp[i].x == last)
        {
            rigt[tmp[i].bh] = last_bh;
        }
        else
        {
            rigt[tmp[i].bh] = i;
            last = tmp[i].x;
            last_bh = i;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        f[i] = max(1, t.GetAns(1, n, rigt[i], n, 1) + 1);
        t.Update(1, n, rigt[i], f[i], 1);
        ans = max(ans, f[i]);
    }
    printf("%d", ans);
}

/* ���� */
bool operator<(const QuJian &a, const QuJian &b)
{
    return a.l == b.l ? a.r > b.r : a.l < b.l;
}
bool operator>(const QuJian &a, const QuJian &b)
{
    return a.l == b.l ? a.r < b.r : a.l > b.l;
}
/* �߶��� */
int LineTree::GetAns(int l, int r, int s, int t, int k)
{
    if (s <= l && r <= t)
    {
        return tr[k];
    }
    int mid = (l + r) >> 1;
    int ret = 0;
    if (s <= mid)
        ret = max(ret, GetAns(l, mid, s, t, k * 2));
    if (t > mid)
        ret = max(ret, GetAns(mid + 1, r, s, t, k * 2 + 1));
    return ret;
}
void LineTree::Update(int l, int r, int x, int sum, int k)
{
    if (l == x && x == r)
    {
        tr[k] = max(tr[k], sum);
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        Update(l, mid, x, sum, k * 2);
    if (x > mid)
        Update(mid + 1, r, x, sum, k * 2 + 1);
    tr[k] = max(tr[k * 2], tr[k * 2 + 1]);
    return;
}
/* ���� */
template <typename Type> void Qsort(int l, int r, Type *a)
{
    int i = l, j = r;
    Type mid = a[(l + r) >> 1];
    while (i <= j)
    {
        while (a[i] < mid)
            ++i;
        while (a[j] > mid)
            --j;
        if (i <= j)
        {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort<Type>(i, r, a);
    if (l < j)
        Qsort<Type>(l, j, a);
    return;
}
/* ���� */
int max(int a, int b)
{
    return a > b ? a : b;
}
template <typename Type> void swap(Type &a, Type &b)
{
    Type tmp = a;
    a = b;
    b = tmp;
    return;
}
/* ��ɢ�� */
bool operator<(const LiSan &a, const LiSan &b)
{
    return a.x < b.x;
}
bool operator>(const LiSan &a, const LiSan &b)
{
    return a.x > b.x;
}
