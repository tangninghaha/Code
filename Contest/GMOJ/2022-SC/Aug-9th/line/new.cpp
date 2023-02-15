#include <cstdio>
#include <cmath>
#include <algorithm>

using std::pair;

/* Constant */
const int MAXN = 5e4 + 1;
const long double EXP = 1e-11;

/* Namespace */
namespace Sort
{
    template <typename T> void Qsort(int l, int r, T *a);
    template <typename T> void Swap(T& a, T& b);
}
namespace Tree
{
    long long c[MAXN];
    long long Query(int x);
    void Update(int x, int num, const int& n);
    void Build(int n, long long *num);
    int lowbit(const int &x);
    void Clear(int n);
}

/* Declaration */
void FileIO();
long double
BinarySearch(long double lbound, long double rbound, int goal, int n);
void GetIntercept(long double theta, int n);
void Discretize(int n);
long double cot(long double x);
int main();
long long Max(long long a, long long b);
long long Min(long long a, long long b);
long long Abs(long long x);

/* Class */
class Point
{
    public:
        long long x;
        long long y;
};

/* Variable */
Point input[MAXN];
pair<long double, int> intercept[MAXN];
int rk[MAXN];
pair<long long, int> tmp[MAXN];

/* Definition */
void FileIO()
{
    freopen("line.in", "r", stdin);
    freopen("line.out", "w", stdout);
    return;
}
template <typename T> void Sort::Qsort(int l, int r, T *a)
{
    int i = l, j = r;
    T mid = a[(l + r) >> 1];
    while (i <= j)
    {
        while (a[i] < mid)
            ++i;
        while (a[j] > mid)
            --j;
        if (i <= j)
        {
            Sort::Swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Sort::Qsort(i, r, a);
    if (l < j)
        Sort::Qsort(l, j, a);
    return;
}
template <typename T> void Sort::Swap(T& a, T&b)
{
    T temp = a;
    a = b;
    b = temp;
    return;
}
long long Tree::Query(int x)
{
    long long ret = 0;
    while (x)
    {
        ret += c[x];
        x -= lowbit(x);
    }
    return ret;
}
void Tree::Update(int x, int num, const int& n)
{
    while (x <= n)
    {
        c[x] += num;
        x += lowbit(x);
    }
    return;
}
void Tree::Build(int n, long long *num)
{
    int nxt;
    for (int i = 1; i <= n; ++i)
    {
        c[i] += num[i];
        nxt = i + lowbit(i);
        if (nxt <= n)
        {
            c[nxt] += c[i];
        }
    }
    return;
}
int Tree::lowbit(const int &x)
{
    return x & -x;
}
void Tree::Clear(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        c[i] = 0;
    }
}
long double 
BinarySearch(long double lbound, long double rbound, int goal, int n)
{
    long long cnt = 0;
    long double mid;
    long double ret = 0;
    while (rbound - lbound >= EXP)
    {
        mid = (lbound + rbound) / 2.0;
        cnt = 0;
        GetIntercept(mid, n);
        Sort::Qsort(1, n, intercept);
        Tree::Clear(n);
        for (int i = n; i >= 1; --i)
        {
            cnt += Tree::Query(n) - Tree::Query(intercept[i].second - 1);
            Tree::Update(intercept[i].second, 1, n);
        }
        if (cnt > goal)
        {
            rbound = mid;
        }
        else if (cnt < goal)
        {
            lbound = mid;
        }
        else
        {
            ret = mid;
            rbound = mid;
        }
    }
    return ret;
}
void GetIntercept(long double theta, int n)
{
    long double ct;
    if (theta >= M_PI_2)
    {
        ct = cot(M_PI - theta);
        for (int i = 1; i <= n; ++i)
        {
            intercept[i] = std::make_pair(input[i].x + ct * input[i].y, rk[i]);
        }
    }
    else
    {
        ct = cot(theta);
        for (int i = 1; i <= n; ++i)
        {
            intercept[i] = std::make_pair(input[i].x - ct * input[i].y, rk[i]);
        }
    }
    return;
}
void Discretize(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        tmp[i] = std::make_pair(input[i].y, i);
    }
    Sort::Qsort(1, n, tmp);
    long long last = -1;
    int k = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (tmp[i].first != last)
        {
            ++k;
            last = tmp[i].first;
        }
        rk[tmp[i].second] = k;
    }
    return;
}
long double cot(long double x)
{
    if (x == M_PI_2)
    {
        return 0.0;
    }
    long double ret = (long double)tan(x);
//    while (ret < 0)
//    {
//        ret += M_PI;
//    }
//    while (ret >= M_PI)
//    {
//        ret -= M_PI;
//    }
    return 1.0 / ret;
}
int main()
{
    FileIO();
    int n;
    scanf("%d", &n);
    long long max_x = 1e9 + 1;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld%lld", &input[i].x, &input[i].y);
        max_x = Min(max_x, Min(input[i].x, input[i].y));
    }
    max_x = Abs(max_x);
    ++max_x;
    for (int i = 1; i <= n; ++i)
    {
        input[i].x += max_x;
        input[i].y += max_x;
    }
    Discretize(n);
    long long m = (long long)n * (n - 1) / 2;
    if (m & 1)
    {
        printf("%.15Lf", BinarySearch(0, M_PI, (m + 1) / 2, n));
    }
    else
    {
        long double ans1 = BinarySearch(0, M_PI, m / 2, n);
        long double ans2 = BinarySearch(0, M_PI, m / 2 + 1, n);
        printf("%.15Lf", (ans1 + ans2) / 2.0);
    }
    return 0;
}
long long Max(long long a, long long b)
{
    return a > b ? a : b; 
}
long long Min(long long a, long long b)
{
    return a < b ? a : b;
}
long long Abs(long long x)
{
    return x > 0 ? x : -x;
}
