#include <stdio.h>

const int INF = 2147483647;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
const int MAXX = 1e5 + 5;
int ans[11][MAXX][3];
int sum[11];
int t[51];
int c[51];
int p;
int now;

void Dfs(int x, int y, int k, int d, int fx);
void FileIO();
void GetAns(int x, int d, int xx, int yy);
int main();
int R;
int anss = INF;
int ans_x = INF;
int ans_y = INF;

void Dfs(int x, int y, int k, int d, int fx)
{
    if (k > p)
    {
        ++sum[now];
        ans[now][sum[now]][0] = x;
        ans[now][sum[now]][1] = y;
        ans[now][sum[now]][2] = d;
        return;
    }
    if (t[k] == 1)
    {
        Dfs(x, y, k + 1, d, c[k]);
        Dfs(x, y, k + 1, d + 1, fx);
    }
    else
    {
        Dfs(x + dx[fx], y + dy[fx], k + 1, d, fx);
        Dfs(x, y, k + 1, d + 1, fx);
    }
    return;
}
void FileIO()
{
    freopen("robot.in", "r",stdin);
    freopen("robot.out", "w", stdout);
    return;
}
void GetAns(int x, int d, int xx, int yy)
{
    if (d > anss)
        return;
    if (x > R)
    {
        if (xx <= ans_x)
        {
            if (yy <= ans_y)
            {
                anss = d;
                ans_x = xx;
                ans_y = yy;
            }
        }
        return;
    }
    for (int i = 1; i <= sum[x]; ++i)
    {
        if ((ans[x][i][0] == xx && ans[x][i][1] == yy) || x == 1)
        {
            GetAns(x + 1, d + ans[x][i][2], ans[x][i][0], ans[x][i][1]);
        }
    }
}
int main()
{
    FileIO();
    scanf("%d", &R);
    int x, y, q;
    char type;
    for (int i = 1; i <= R; ++i)
    {
        now = i;
        scanf("%d%d%d%d", &x, &y, &q, &p);
        q /= 90;
        for (int j = 1; j <= p; ++j)
        {
            type = getchar();
            while (type != 'T' && type != 'S')
            {
                type = getchar();
            }
            if (type == 'T')
            {
                t[j] = 1;
                scanf("%d", &c[j]);
                c[j] /= 90;
            }
            else
            {
                t[j] = 2;
            }
        }
        Dfs(x, y, 1, 0, q);
    }
    GetAns(1, 0, 0, 0);
    if (anss == INF)
        printf("-1");
    else
        printf("%d\n%d %d", anss, ans_x, ans_y);
    return 0;
}
