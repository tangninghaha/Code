#include <cstdio>

/* Constant */
const int MAXN = 105;

/* Declaration */
int main();
void FileIO();
int Find1(int, int, int);
int Find2(int, int, int);

/* Variable */
char tmp[MAXN];
int map[MAXN][MAXN];

/* Definition */
void FileIO()
{
    freopen("xx.in", "r", stdin);
    freopen("xx.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", tmp);
        for (int j = 1; j <= n; ++j)
        {
            if (tmp[j - 1] == '0')
            {
                map[i][j] = 0;
            }
            else
            {
                map[i][j] = 1;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            ans += Find1(i, j, n);
            if (i != n && j != n)
                ans += Find2(i, j, n);
        }
    }
    printf("%d", ans);
    return 0;
}
int Find1(int _x, int _y, int n)
{
    if (!map[_x][_y])
        return 0;
    int r;
    for (r = 1; ;++r)
    {
        if (_x - r < 1 || _x + r > n || _y - r < 1 || _y + r > n)
            break;
        if (!map[_x - r][_y - r] || !map[_x - r][_y + r]
            || !map[_x + r][_y - r] || !map[_x + r][_y + r])
            break;
    }
    if (r == 1)
        return 0;
    return r - 1;
}
int Find2(int _x, int _y, int n)
{
    int r;
    for (r = 0; ;++r)
    {
        if (_x - r < 1 || _x + r + 1 > n || _y - r < 1 || _y + r + 1 > n)
            break;
        if (!map[_x - r][_y - r] || !map[_x - r][_y + r + 1]
            || !map[_x + r + 1][_y - r] || !map[_x + r + 1][_y + r + 1])
            break;
    }
    return r;
}
