#include <cstdio>

/* Constant */
const double xxx = 1e-10;
const int MAXN = 1025;

/* Declaration */
int main();
void Sovle(int);
int Cmp(double, double);
int Read();
void Dfs(int, int, int);

/* Variable */
double gailv[MAXN][MAXN];
double win_gailv[MAXN];
int winperson[MAXN];
int temp[MAXN];
bool winer[MAXN][11];
int twom[11];

/* Definition */
int Read()
{
    char tem = getchar();
    int ret = 0;
    while (tem < '0' || tem > '9')
    {
        tem = getchar();
    }
    while (tem >= '0' && tem <= '9')
    {
        ret = ret * 10 + tem - '0';
        tem = getchar();
    }
    return ret;
}
int main()
{
    twom[0] = 1;
    for (int i = 1; i <= 10; ++i)
    {
        twom[i] = twom[i - 1] << 1;
    }
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= twom[n]; ++i)
    {
        for (int j = 1; j <= twom[n]; ++j)
        {
            gailv[i][j] = Read();
        }
    }
    Sovle(n);
    return 0;
}
void Sovle(int n)
{
    Dfs(1, n, n);
    double ans = -1;
    int ans_bh = -1;
    for (int i = 1; i <= twom[n]; ++i)
    {
        if (Cmp(win_gailv[i], ans) > 0)
        {
            ans = win_gailv[i];
            ans_bh = i;
        }
    }
    printf("%d", ans_bh);
#ifdef DEBUG
    printf("\n%.2lf\n", ans);
    for (int i = 1; i <= twom[n]; ++i)
    {
        printf("%.2lf ", win_gailv[i]);
    }
#endif
    return;
}
void Dfs(int x, int k, int n)
{
    if (!k)
    {
        double t_gailv = 100;
        for (int j = 1; j <= twom[n]; ++j)
        {
            winperson[j] = j;
        }
        for (int i = n; i >= 1; --i)
        {
            for (int j = 1; j <= twom[i]; ++j)
            {
                temp[j] = winperson[j];
            }
            for (int j = 1; j <= twom[i - 1]; ++j)
            {
                winperson[j] = temp[2 * j - winer[j][i]];
                t_gailv *= 
                   gailv[temp[2 * j - winer[j][i]]][temp[2 * j - !winer[j][i]]];
                t_gailv /= 100.0;
            }
        }
        win_gailv[winperson[1]] += t_gailv;
        return;
    }
    winer[x][k] = 1;
    if (x == twom[k - 1])
        Dfs(1, k - 1, n);
    else
        Dfs(x + 1, k, n);
    winer[x][k] = 0;
    if (x == twom[k - 1])
        Dfs(1, k - 1, n);
    else
        Dfs(x + 1, k, n);
}
int Cmp(double _a, double _b)
{
    if (_a > _b)
    {
        if (_a - _b <= xxx)
            return 0;
        else
            return 1;
    }
    if (_a < _b)
    {
        if (_b - _a <= xxx)
            return 0;
        else
            return -1;
    }
    return 0;
}
