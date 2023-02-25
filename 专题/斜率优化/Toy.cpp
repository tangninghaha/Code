#include <cstdio>

/* Constant */
const int MAXN = 5e4 + 5;

/* Declaration */
int main();
void FileIO();

/* Variable */
int sta[MAXN];
long long sum[MAXN];
int c[MAXN];

/* Definition */
int main()
{
    int n, l;
    scanf("%d%d", &n, &l);
    for (int i = 1; i <= n; ++i)
    {
        scnaf("%d", &c[i]);
        sum[i] = sum[i - 1] + c[i];
    }
}
