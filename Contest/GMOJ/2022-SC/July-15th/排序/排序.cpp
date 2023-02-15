#include <stdio.h>
const int MAXN = 3e5 + 5, MAXM = 1e5 + 5;
int a[MAXN];
int rk[MAXM];
int lef, rgt, z = 1e5;
int minnum, maxnum;
bool vis[MAXN];
void swap(int &a, int &b);
struct LineTree
{
    int tr[MAXN * 4];
    void Update(int l, int r, int x, bool sum, int k);
    int GetAns(int l, int r, int s, int t, int k);
    void Build(int l, int r, int k);
};
LineTree lt;
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i + z]);
        vis[i + z] = true;
        rk[a[i + z]] = i + z;
    }
    lef = 0;
    rgt = 3e5 + 1;
    minnum = 1;
    maxnum = n;
    lt.Build(1, 300000, 1);
    int ans;
    for (int i = 1; i <= n; ++i)
    {
        if (i % 2)
        {
            ++lef;
            ans = lt.GetAns(1, 300000, 100000, rk[minnum] - 1, 1);
            swap(a[rk[minnum]], a[lef]);
            lt.Update(1, 300000, rk[minnum], 0, 1);
            rk[minnum] = lef;
            ++minnum;
        }
        else
        {
            --rgt;
            ans = lt.GetAns(1, 300000, rk[maxnum] + 1, 200000, 1);
            swap(a[rk[maxnum]], a[rgt]);
            lt.Update(1, 300000, rk[maxnum], 0, 1);
            rk[maxnum] = rgt;
            --maxnum;
        }
        printf("%d\n", ans);
    }
    return 0;
}


void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
    return;
}
void LineTree::Update(int l, int r, int x, bool sum, int k)
{
    if (l == x && r == x)
    {
        tr[k] = sum;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        Update(l, mid, x, sum, k * 2);
    if (x > mid)
        Update(mid + 1, r, x, sum, k * 2 + 1);
    tr[k] = tr[k * 2] + tr[k * 2 + 1];
    return;
}
int LineTree::GetAns(int l, int r, int s, int t, int k)
{
    if (s <= l && r <= t)
        return tr[k];
    int mid = (l + r) >> 1, ret = 0;
    if (s <= mid)
        ret += GetAns(l, mid, s, t, k * 2);
    if (t > mid)
        ret += GetAns(mid + 1, r, s, t, k * 2 + 1);
    return ret;
}
void LineTree::Build(int l, int r, int k)
{
    if (l == r)
    {
        tr[k] = vis[l];
        return;
    }
    int mid = (l + r) >> 1;
    Build(l, mid, k * 2);
    Build(mid + 1, r, k * 2 + 1);
    tr[k] = tr[k * 2] + tr[k * 2 + 1];
    return;
}
