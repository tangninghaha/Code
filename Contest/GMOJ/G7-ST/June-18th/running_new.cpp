#include <stdio.h>

const int MAXM = 60, MAXX = 1e6;
int a[MAXM], k[MAXM];
int bs[MAXM], tem[MAXM];
bool vis[MAXX];

int Gcd(int x, int y);
void swap(int &a, int &b);
void Qsort(int l, int r);
int n;

int main()
{
    freopen("running.in", "r", stdin);
    freopen("running.out", "w", stdout);
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &a[i]);
        if (!(n % a[i]))
        {
            k[i] = 0;
        }
        else
        {
            k[i] = (n / a[i]) * a[i] + a[i] - n;
        }
    }
    int sum = 0, g = 0;
    for (int i = 1; i <= m; i++)
    {
        g = Gcd(n, a[i]);
        sum++;
        bs[sum] = g;
    }
    Qsort(1, sum);
    int last = -1;
    for (int i = 1; i <= sum; i++)
    {
        if (bs[i] == last)
        {
            bs[i] = -1;
        }
        else
        {
            last = bs[i];
        }
    }
    for (int i = 1; i <= sum; i++)
    {
        tem[i] = bs[i];
    }
    int osum = sum;
    sum = 0;
    for (int i = 1; i <= osum; i++)
    {
        if (tem[i] != -1)
        {
            sum++;
            bs[sum] = tem[i];
        }
    }
    int ans = 0;
    vis[0] = 1;
    for (int i = 1; i <= sum; i++)
    {
        for (int j = 1; bs[i] * j < n; j++)
        {
            vis[bs[i] * j] = 1;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if(!vis[i])
        {
            ans++;
        }
    }
    printf("%lld", ans);
}

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
void Qsort(int l, int r)
{
    int i = l, j = r, mid = bs[(l + r) / 2];
    while(i < j)
    {
        while (bs[i] < mid) i++;
        while (bs[j] > mid) j--;
        if (i <= j)
        {
            swap(bs[i], bs[j]);
            i++;
            j--;
        }
    }
    if (i < r) Qsort(i, r);
    if (l < j) Qsort(l, j);
}

int Gcd(int x, int y)
{
    if (y == 0)
    {
        return x;
    }
    return Gcd(y, x % y);
}
