#include <stdio.h>

const int MAXN = 1e3 + 5;
int a[MAXN][MAXN];
int rk[MAXN * MAXN][2];
int abs(int x);
void Right(int x);
void Down(int x);
void swap(int &a, int &b);
void print();
int n, k;

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            a[i][j] = (i - 1) * n + j;
            rk[(i - 1) * n + j][0] = i;
            rk[(i - 1) * n + j][1] = j;
        }
    }
    int x, y, num;
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d%d%d", &num, &x, &y);
        printf("%d\n", ((x - rk[num][0]) + n) % n + ((y - rk[num][1]) + n) % n);
        while (rk[num][1] != y)
        {
            Right(rk[num][0]);
//            print();
        }
        while (rk[num][0] != x)
        {
            Down(rk[num][1]);
//            print();
        }

    }
}
void print()
{
    printf("\n");
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}
void Right(int x)
{
    int tmp = a[x][n];
    for (int i = n; i >= 2; --i)
    {
        a[x][i] = a[x][i - 1];
        rk[a[x][i]][1] = i;
    }
    a[x][1] = tmp;
    rk[tmp][1] = 1;
    return;
}
void Down(int x)
{
    int tmp = a[n][x];
    for (int i = n; i >= 2; --i)
    {
        a[i][x] = a[i - 1][x];
        rk[a[i][x]][0] = i;
    }
    a[1][x] = tmp;
    rk[tmp][0] = 1;
    return;
}
int abs(int x)
{
    return x < 0 ? -x : x;
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
