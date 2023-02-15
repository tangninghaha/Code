#include <cstdio>

/* Constant */
const int INF =1e9 + 5;
const int MAXN = 1e7 + 5;

/* Declaration */
int main();
int Min(int, int);
int Max(int, int);
int Read();

/* Variable */
int min_num[MAXN];
int max_num[MAXN];
int a[MAXN];
int b[MAXN];

/* Definition */
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        a[i] = Read();
    }
    for (int i = 1; i <= n; ++i)
    {
        b[i] = Read();
    }
    min_num[n + 1] = INF;
    for (int i = n; i >= 1; --i)
    {
        min_num[i] = Min(min_num[i], a[i]);
    }
    int l, r;
    while (l < n)
    {

    }
}
