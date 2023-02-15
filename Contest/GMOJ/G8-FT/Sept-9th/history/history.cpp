#include <cstdio>

/* Constant */
const int MAXK = 1e5 + 5;

/* Class */
class Node
{
    public:
        int x;
        int y;
        int c;
        int yx;
        int yy;
};

/* Namespace */
namespace Tree
{
    long long tr[MAXK * 4];
    int lowbit(int x);
    long long GetAns(int x);
    void Update(int x, int c, int n);
}

/* Definition */
void FileIO();
int main();
int LSH(int);
void Qsort_x(int, int);
void Qsort_y(int, int);
bool Cmp_x(const Node&, const Node&);
bool Cmp_y(const Node&, const Node&);
void Swap(Node&, Node&);
long long Max(long long a_, long long b_);

/* Variable */
Node node[MAXK];
long long f[MAXK];

/* Declaration */
int Tree::lowbit(int x)
{
    return x & -x;
}
long long Tree::GetAns(int x)
{
    long long ret = 0;
    while (x > 0)
    {
        ret = Max(ret, tr[x]);
        x -= lowbit(x);
    }
    return ret;
}
void Tree::Update(int x, int c, int n)
{
    while (x <= n)
    {
        tr[x] = Max(c, tr[x]);
        x += lowbit(x);
    }
    return;
}

long long Max(long long a_, long long b_)
{
    return a_ > b_ ? a_ : b_;
}
void FileIO()
{
    freopen("history.in", "r", stdin);
    freopen("history.out", "w", stdout);
    return;
}
int main()
{
    // FileIO();
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d%d%d", &node[i].x, &node[i].y, &node[i].c);
        node[i].yx = node[i].x;
        node[i].yy = node[i].y;
    }
    int tot_y = LSH(k);
    long long ans = 0;
    long long sum = 0;
    for (int i = k; i >= 1; --i)
    {
        f[i] = Tree::GetAns(tot_y - node[i].y + 1) + node[i].c;
        Tree::Update(tot_y - node[i].y + 1, f[i], tot_y);
        sum += node[i].c;
        ans = Max(ans, f[i]);
    }
    // for (int i = 1; i <= k; ++i)
    // {
        // printf("%lld ", f[i]);
    // }
    printf("%lld", ans);
    return 0;
}
int LSH(int k)
{
    Qsort_y(1, k);
    int last = -1, tot = 0, ret;
    for (int i = 1; i <= k; ++i)
    {
        if (node[i].yy != last)
        {
            ++tot;
            last = node[i].yy;
        }
        node[i].y = tot;
    }
    ret = tot;
    Qsort_x(1, k);
    last = -1, tot = 0;
    for (int i = 1; i <= k; ++i)
    {
        if (node[i].x != last)
        {
            ++tot;
            last = node[i].yx;
        }
        node[i].x = tot;
    }
    return ret;
}
void Swap(Node& a_, Node& b_)
{
    const Node tmp = a_;
    a_ = b_;
    b_ = tmp;
    return;
}
bool Cmp_x(const Node& a_, const Node& b_)
{
    if (a_.x != b_.x)
        return a_.x < b_.x;
    return a_.y < b_.y;
}
void Qsort_x(int l, int r)
{
    int i = l, j = r;
    const Node mid = node[(l + r) >> 1];
    while (i <= j)
    {
        while (Cmp_x(node[i], mid))
            ++i;
        while (Cmp_x(mid, node[j]))
            --j;
        if (i <= j)
        {
            Swap(node[i], node[j]);
            ++i;
            --j;
        }
    }
    if (i <= r)
        Qsort_x(i, r);
    if (l <= j)
        Qsort_x(l, j);
    return;
}
bool Cmp_y(const Node& a_, const Node& b_)
{
    if (a_.y != b_.y)
        return a_.y < b_.y;
    return a_.x < b_.x;
}
void Qsort_y(int l, int r)
{
    int i = l, j = r;
    const Node mid = node[(l + r) >> 1];
    while (i <= j)
    {
        while (Cmp_y(node[i], mid))
            ++i;
        while (Cmp_y(mid, node[j]))
            --j;
        if (i <= j)
        {
            Swap(node[i], node[j]);
            ++i;
            --j;
        }
    }
    if (i <= r)
        Qsort_y(i, r);
    if (l <= j)
        Qsort_y(l, j);
    return;
}
