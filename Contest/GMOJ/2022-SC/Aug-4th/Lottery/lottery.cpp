#include <stdio.h>

const int MAXN = 2005;
int a[MAXN];
int ans[MAXN][MAXN];

int Max(int a, int b);
void FileIO();
int main();
void Sovle(int n, int l);

int Max(int a, int b)
{
	return a > b ? a : b;
}
void FileIO()
{
    freopen("lottery.in", "r", stdin);
    freopen("lottery.out", "w", stdout);
    return;
}
int main()
{
	FileIO();
    int n, l;
    scanf("%d%d", &n, &l);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    Sovle(n, l);
}
void Sovle(int n, int l)
{
    int ed = n - l + 1;
    int st, edd;
    for (int i = 1; i <= n - l; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            if (a[j] != a[j - i])
            {
            	st = j - l + 1;
				if (st - i <= 0)
				{
					st = i + 1;
				}
				edd = j;
				if (edd > ed)
				{
					edd = ed;
				}
                for (int k = st; k <= edd; ++k)
                {
                    ++ans[k][k - i];
                    ++ans[k - i][k];
                }
            }
        }
    }
    int q;
    scanf("%d", &q);
    int x;
    int cnt;
    for (int i = 1; i <= q; ++i)
    {
        scanf("%d", &x);
        for (int j = 1; j <= ed; ++j)
        {
            cnt = 0;
            for (int k = 1; k <= ed; ++k)
            {
                if (ans[j][k] <= x)
                {
                    ++cnt;
                }
            }
            printf("%d ", cnt - 1);
        }
        printf("\n");
    }
    return;
}
