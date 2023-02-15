#include <cstdio>
#include <cstring>

/* Constant */
const int MAXN = 2e5 + 5;

/* Declaration */
int main();
void FileIO();
void Qsort(int l, int r);
void Swap(int& a_, int& b_);

/* Variable */
char str[2 * MAXN];
int a[MAXN];


/* Definition */
int main()
{
    FileIO();
    int n = 0;
    scanf("%s", str + 1);
    str[0] = '*';
    int len = strlen(str) - 1;
    int cnt = 0;
    for (int i = 1; i <= len; ++i)
    {
        if (str[i] == 'X')
        {
            ++n;
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        ans += a[i];
    }
    Qsort(1, n);
    for (int i = len; i >= 1; --i)
    {
        if (str[i] == 'B')
        {
            if (str[i - 1] == 'A' && str[i - 2] == 'A')
                
        }
    }
    printf("%lld", ans);
    return 0;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    int mid = a[(l + r) >> 1];
    while (i <= j)
    {
        while (a[i] < mid)
            ++i;
        while (a[j] > mid)
            --j;
        if (i <= j)
        {
            Swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r);
    if (l < j)
        Qsort(l, j);
    return;
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
    freopen("dark.in", "r", stdin);
    freopen("dark.out", "w", stdout);
}
