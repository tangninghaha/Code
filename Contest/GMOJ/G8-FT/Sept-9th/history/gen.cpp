#include <cstdio>
#include <cstdlib>
#include <ctime>

bool vis[4005][4005];

int Min(int a, int b)
{
    return a < b ? a : b;
}
int main()
{
    srand((unsigned)time(0));
    int n = rand() % 4000 + 1;
    int m = rand() % 4000 + 1;
    int k = rand() % 100000 + 1;
    k = Min(k, n * m);
    printf("%d %d %d\n", n, m, k);
    int x, y, c;
    for (int i = 1; i <= k; ++i)
    {
        x = rand() % n + 1;
        y = rand() % m + 1;
        c = rand() % 300 + 1;
        while (vis[x][y])
        {
            x = rand() % n + 1;
            y = rand() % m + 1;
        }
        vis[x][y] = true;
        printf("%d %d %d\n", x, y, c);
    }
}
