#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;

/* Declaration */
int main();
bool Pd(int, int);
bool Bh(int, int, int);
void Swap(int&, int&);

/* Variable */
int set[MAXN][2];

/* Definitino */
int main()
{
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &set[i][0], &set[i][1]);
        if (set[i][0] > set[i][1])
        {
            Swap(set[i][0], set[i][1]);
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            for (int k = j + 1; k <= n; ++k)
            {
                if (!Pd(i, j) && !Pd(j, k) && !Pd(i, k))
                {
                    ++ans;
                }
                else if (Bh(i, j, k) || Bh(j, i, k) || Bh(k, i, j))
                {
                    ++ans;
                }
            }
        }
    }
    printf("%lld", ans);
    return 0;
}
bool Pd(int _x, int _y)
{
    if (set[_x][0] > set[_y][0] && set[_x][0] < set[_y][1])
        return true;
    if (set[_y][0] > set[_x][0] && set[_y][0] < set[_x][1])
        return true;
    if (set[_x][1] > set[_y][0] && set[_x][1] < set[_y][1])
        return true;
    if (set[_y][1] > set[_x][0] && set[_y][1] < set[_x][1])
        return true;
    return false;
}
void Swap(int& _a, int& _b)
{
    int t = _a;
    _a = _b;
    _b = t;
    return;
}
bool Bh(int _i, int _j, int _k)
{
    if (set[_i][0] < set[_j][0] && set[_j][1] < set[_i][1] && set[_i][0] < set[_k][0] && set[_k][1] < set[_i][1])
        return true;
    return false;
}
