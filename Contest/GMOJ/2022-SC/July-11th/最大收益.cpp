#include <stdio.h>
struct Task
{
    int s;
    int t;
    int v;
    bool operator<(const Task &a);
    bool operator>(const Task &a);
};
const int MAXN = 5005, MAXX = 1e8 + 1;
Task T[MAXN];
bool vis[MAXX];
int point[MAXN];
int point_task[MAXN];
template <typename Type> void swap(Type &a, Type &b)
{
    Type t = a;
    a = b;
    b = t;
    return;
}
template <typename Type> void Qsort(int l, int r, Type *a);
int max(int a, int b);
bool Find(int t, int i);
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d%d", &T[i].s, &T[i].t, &T[i].v);
    }
    Qsort<Task>(1, n, T);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = T[i].s; j <= 100000000; ++j)
        {
            if (!vis[j])
            {
                point[i] = j;
                vis[j] = true;
                break;
            }
        }
    }
    Qsort<int>(1, n, point);
    long long value = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (Find(1, i))
        {
            value += T[i].v;
        }
    }
    printf("%lld", value);
    return 0;
}
bool Find(int t, int i)
{
    if (point[t] > T[i].t)
        return false;
    while (point[t] < T[i].s)
    {
        ++t;
    }
    if (point_task[t])
    {
        if (T[point_task[t]].t > T[i].t)
        {
            if (Find(t + 1, point_task[t]))
            {
                point_task[t] = i;
                return true;
            }
            return false;
        }
        else
        {
            return Find(t + 1, i);
        }
    }
    else
    {
        point_task[t] = i;
        return true;
    }
    return false;
}
bool Task::operator<(const Task &a)
{
    if (a.v < v) return true;
    if (a.v > v) return false;
    if (a.t > t) return true;
    if (a.t < t) return false;
    if (a.s > s) return true;
    if (a.s < s) return false;
    return false;
}
bool Task::operator>(const Task &a)
{
    if (a.v > v) return true;
    if (a.v < v) return false;
    if (a.t < t) return true;
    if (a.t > t) return false;
    if (a.s < s) return true;
    if (a.s > s) return false;
    return false;
}
//void swap(Type &a, Type &b)
int max(int a, int b)
{
    return a > b ? a : b;
}
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
