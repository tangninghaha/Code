#include <stdio.h>
#include <cmath>
const int MAXN = 2e6 + 5;
int a[MAXN];
int st;
void swap(int &a, int &b);
int min(int a, int b);
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        a[i] = i;
    }
    for (int i = 2; i <= n; ++i)
    {
        if (n % i)
        {
            a[st + n + 1] = a[st + n / i * i + 1];
        }
        for (int j = n / i; j >= 1; --j)
        {
            a[st + j * i + 1] = a[st + (j - 1) * i + 1];
        }
        ++st;
    }
    for (int i = st + 1; i <= n + st; ++i)
    {
        printf("%d ", a[i]);
    }
    return 0;
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
