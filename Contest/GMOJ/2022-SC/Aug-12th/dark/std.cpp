#include <cstdio>
#include <cstring>

/* Constant */
const int MAXN = 4e5 + 5;

/* Declaration */
int main();
void FileIO();
void Dfs(int);
int Max(int, int);
void Qsort(int, int);
void Swap(int&, int&);

/* Variable */
int tr[MAXN * 2];
int lson[MAXN * 2];
int rson[MAXN * 2];
int stack[MAXN * 2];
char str[MAXN * 2];
int a[MAXN];
int ans[MAXN];

/* Definition */
int main()
{
    FileIO();
    int len, n = 0;
    scanf("%s", str + 1);
    str[0] = '$';
    len = strlen(str) - 1;
    int s = 0;
    int top = 0;
    for (int i = len; i >= 1; --i)
    {
        if (str[i] == 'X')
        {
            ++n;
            ++top;
            ++s;
            tr[s] = 1;
            stack[top] = s;
        }
        else
        {
            if (str[i] == 'A')
            {
                ++s;
                tr[s] = 2;
                lson[s] = stack[top];
                --top;
                rson[s] = stack[top];
                --top;
                ++top;
                stack[top] = s;
            }
            else
            {
                ++s;
                tr[s] = 3;
                lson[s] = stack[top];
                --top;
                rson[s] = stack[top];
                --top;
                ++top;
                stack[top] = s;
            }
        }
    }
    Dfs(s);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    Qsort(1, n);
    long long anss = 0;
    for (int i = 1; i <= ans[s]; ++i)
    {
        anss += a[i];
    }
    printf("%lld", anss);
}
void Dfs(int x)
{
    if (lson[x] != 0)
    {
        Dfs(lson[x]);
    }
    if (rson[x] != 0)
    {
        Dfs(rson[x]);
    }
    if (tr[x] == 2)
        ans[x] = ans[lson[x]] + ans[rson[x]];
    else if (tr[x] == 3)
        ans[x] = Max(ans[lson[x]], ans[rson[x]]);
    else 
        ans[x] = 1;
    return;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    int mid = a[(l + r) >> 1];
    while (i <= j)
    {
        while (a[i] > mid)
        {
            ++i;
        }
        while (a[j] < mid)
        {
            --j;
        }
        if (i <= j)
        {
            Swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
    {
        Qsort(i, r);
    }
    if (l < j)
    {
        Qsort(l, j);
    }
}
void Swap(int& a_, int& b_)
{
    int tmp = a_;
    a_ = b_;
    b_ = tmp;
    return;
}
int Max(int a_, int b_)
{
    return a_ > b_ ? a_ : b_;
}
void FileIO()
{
    freopen("dark.in", "r", stdin);
    freopen("dark.out", "w", stdout);
    return;
}
