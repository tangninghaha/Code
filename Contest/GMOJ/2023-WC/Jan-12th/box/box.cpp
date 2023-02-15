#include <cstdio>

/* constant */
const int MAXN = 2e5 + 5;
const int INF = 2e9 + 5;

/* Class */
class LineTree
{
    public:
        int tr_min[MAXN * 4];
        int tr_max[MAXN * 4];
        void Init(int, int, int);
        void Update(int, int, int, int);
        int GetMax(int, int, int, int, int);
        int GetMin(int, int, int, int, int);

        int Max(int, int);
        int Min(int, int);
};
int LineTree::Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
int LineTree::Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
void LineTree::Init(int l, int r, int k)
{
    if (l == r)
    {
        tr_min[k] = INF;
        tr_max[k] = 0;
        return;
    }
    int mid = l + r >> 1;
    Init(l, mid, k * 2);
    Init(mid + 1, r, k * 2 + 1);
    tr_max[k] = Max(tr_max[k * 2], tr_max[k * 2 + 1]);
    tr_min[k] = Max(tr_min[k * 2], tr_min[k * 2 + 1]);
    return;
}
void LineTree::Update(int l, int r, int sum, int k)
{
    if (l == sum && r == sum)
    {
        tr_max[k] = sum;
        tr_min[k] = sum;
        return;
    }
    int mid = l + r >> 1;
    if (sum <= mid)
        Update(l, mid, sum, k * 2);
    if (sum > mid)
        Update(mid + 1, r, sum, k * 2 + 1);
    tr_max[k] = Max(tr_max[k * 2], tr_max[k * 2 + 1]);
    tr_min[k] = Min(tr_min[k * 2], tr_min[k * 2 + 1]);
    return;
}
int LineTree::GetMax(int l, int r, int x, int y, int k)
{
    if (x <= l && r <= y)
    {
        return tr_max[k];
    }
    int mid = l + r >> 1;
    int ret = 0;
    if (x <= mid)
        ret = Max(ret, GetMax(l, mid, x, y, k * 2));
    if (y > mid)
        ret = Max(ret, GetMax(mid + 1, r, x, y, k * 2 + 1));
    return ret;
}
int LineTree::GetMin(int l, int r, int x, int y, int k)
{
    if (x <= l && r <= y)
    {
        return tr_min[k];
    }
    int mid = l + r >> 1;
    int ret = INF;
    if (x <= mid)
        ret = Min(ret, GetMin(l, mid, x, y, k * 2));
    if (y > mid)
        ret = Min(ret, GetMin(mid + 1, r, x, y, k * 2 + 1));
    return ret;
}

class Data
{
    public:
        int num;
        int bh;
        int rk;
};

/* Declaration */
int main();

void Qsort1(int, int);
void Qsort2(int, int);
template <typename T>void Swap(T&, T&);

void UpdatePre(int, int&);
void UpdateNxt(int, int&);


/* Variable */
Data a[MAXN];
int bh[MAXN];

LineTree T;

int q[MAXN];

int n;
/* Definition */
void Qsort1(int l, int r)
{
    int mid = a[l + r >> 1].num;
    int i = l, j = r;
    while (i <= j)
    {
        while (a[i].num < mid)
            ++i;
        while (mid < a[j].num)
            --j;
        if (i <= j)
        {
            Swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort1(i, r);
    if (l < j)
        Qsort1(l, j);
}
void Qsort2(int l, int r)
{
    int mid = a[l + r >> 1].bh;
    int i = l, j = r;
    while (i <= j)
    {
        while (a[i].bh < mid)
            ++i;
        while (mid < a[j].bh)
            --j;
        if (i <= j)
        {
            Swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort2(i, r);
    if (l < j)
        Qsort2(l, j);
}
template <typename T>void Swap(T& _a, T& _b)
{
    T tmp = _a;
    _a = _b;
    _b = tmp;
    return;
}
void UpdatePre(int num_rk, int& pre)
{
    if (num_rk != 1)
        pre = T.GetMax(1, n, 1, num_rk - 1, 1);
    else
        pre = 0;
}
void UpdateNxt(int num_rk, int& nxt)
{
    if (num_rk != n)
        nxt = T.GetMin(1, n, num_rk + 1, n, 1);
    else
        nxt = INF;
}

int main()
{
    freopen("box.in", "r", stdin);
    freopen("box.out", "w", stdout);
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i].num);
        a[i].bh = i;
    }
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &q[i]);
    }
    Qsort1(1, n);
    for (int i = 1; i <= n; ++i)
    {
        a[i].rk = i;
        bh[i] = a[i].bh;
    }
    Qsort2(1, n);
    T.Init(1, n, 1);
    int pre = 0, nxt = INF;
    int k = 1;
    int num_rk = 0;
    for (int i = 1; i <= n + 1; ++i)
    {
        while (i > q[k] && k <= m)
        {
            UpdateNxt(num_rk, nxt);
            num_rk = nxt;
            printf("%d\n", a[bh[num_rk]].num);
            ++k;
        }
        if (i == n + 1)
            break;
        T.Update(1, n, a[i].rk, 1);
        if (a[i].rk < num_rk)
        {
            UpdatePre(num_rk, pre);
            num_rk = pre;
        }
    }
    return 0;
}
