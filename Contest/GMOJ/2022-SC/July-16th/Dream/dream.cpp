#include <stdio.h>
const int MAXN = 2e5 + 5;
struct S
{
    long long l;
    long long r;
};
S a[MAXN];
bool operator<(const S &a, const S &b);
bool operator>(const S &a, const S &b);
long long b[MAXN];
template <typename Type> void Qsort(int l, int r, Type *a);
template <typename Type> void swap(Type &a, Type &b);
void FileIO();
const int MAXQ = 2e5 + 5;
struct priority_queue
{
    int size;
    S num[MAXQ];
    S front();
    void pop();
    void insert(S a);
    void up(int x);
    void down(int x);
};
priority_queue q;
int main()
{
    FileIO();
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld%lld", &a[i].l, &a[i].r);
    }
    for (int i = 1; i <= m; ++i)
    {
        scanf("%lld", &b[i]);
    }
    Qsort<S>(1, n, a);
    Qsort<long long>(1, m, b);
    S tmp;
    int ans = 0;
    int k = 1;
    for (int i = 1; i <= m; ++i)
    {
        for (int j = k; j <= n; ++j)
        {
            if (a[j].l <= b[i])
            {
                q.insert(a[j]);
                k = j + 1;
            }
            else
            {
                break;
            }
        }
        tmp = q.front();
        while (tmp.r < b[i] && q.size)
        {
            q.pop();
            tmp = q.front();
        }
        if (tmp.l <= b[i] && b[i] <= tmp.r)
        {
            q.pop();
            ++ans;
        }
    }
    printf("%d", ans);
    return 0;
}

void priority_queue::insert(S a)
{
    ++size;
    num[size] = a;
    up(size);
    return;
}
void priority_queue::up(int x)
{
    int nxt = x / 2;
    while (nxt >= 1 && num[nxt].r > num[x].r)
    {
        swap(num[nxt], num[x]);
        x = nxt;
        nxt = x / 2;
    }
    return;
}
void priority_queue::down(int x)
{
    int nxt = x * 2;
    while ((nxt <= size && num[nxt].r < num[x].r)
            || (nxt + 1 <= size && num[nxt + 1].r < num[x].r))
    {
        if (num[nxt + 1].r < num[nxt].r && nxt + 1 <= size)
            ++nxt;
        swap(num[nxt], num[x]);
        x = nxt;
        nxt = x * 2;
    }
    return;
}
void priority_queue::pop()
{
    if (size == 0)
        return;
    swap(num[1], num[size]);
    --size;
    down(1);
    return;
}
S priority_queue::front()
{
    if (size == 0)
        return (S){0, 0};
    return num[1];
}
void FileIO()
{
    freopen("dream.in", "r", stdin);
    freopen("dream.out", "w", stdout);
    return;
}
bool operator<(const S &a, const S &b)
{
    return a.l == b.l ? a.r < b.r : a.l < b.l;
}
bool operator>(const S &a, const S &b)
{
    return a.l == b.l ? a.r > b.r : a.l > b.l;
}
template<typename T> void Qsort(int l, int r, T *a)
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
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r, a);
    if (l < j)
        Qsort(l, j, a);
    return;
}
template<typename T> void swap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
    return;
}
