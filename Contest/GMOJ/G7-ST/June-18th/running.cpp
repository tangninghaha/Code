#include <stdio.h>
#include <cstring>
#include <cmath>

const int MAXM = 60;
int a[MAXM];
int bs[MAXM], tem[MAXM];

int Gcd(int x, int y);
void swap(int &a, int &b);
void Qsort(int l, int r);
int GetPhi(int x);
int n;

int main()
{
//    freopen("running.in", "r", stdin);
//    freopen("running.out", "w", stdout);
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &a[i]);
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
    memset(bs, 0, sizeof(bs));
    for (int i = 1; i <= osum; i++)
    {
        if (tem[i] != -1)
        {
            sum++;
            bs[sum] = tem[i];
        }
    }
    int ans = 1, ed = sqrt(n);
    for (int i = 1; i <= ed; i++)
    {
        if (!(n % i))
        {
            bool pd = 0;
            for (int j = 1; j <= sum; j++)
            {
                if (!(i % bs[j]))
                {
                    pd = 1;
                    break;
                }
            }
            if (!pd) continue;
            ans += GetPhi(n / i);
            if (i * i != n)
            {
                for (int j = 1; j <= sum; j++)
                {
                    if (!((n / i) % bs[j]))
                    {
                        ans += GetPhi(i);
                        break;
                    }
                }
            }
        }
    }
    
    printf("%lld", n - ans);
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

int GetPhi(int x)
{
    int ed = sqrt(x), ret = x, temx = x;
    for (int i = 2; i <= ed; i++)
    {
        if (!(temx % i))
        {
            ret = ret * (i - 1) / i;
            while(!(temx % i))
            {
                temx /= i;
            }
        }
        if (temx == 1) break;
    }
    if (temx != 1)
    {
        ret = ret * (temx - 1) / temx;
    }
    return ret;
}
