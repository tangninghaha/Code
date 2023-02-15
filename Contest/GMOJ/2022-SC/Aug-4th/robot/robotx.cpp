#include <stdio.h>

const int MAXN = 11;
const int MAXQ = 1e5 + 5;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int p[MAXN], q[MAXN];
int x[MAXN], y[MAXN];
int t[MAXN][55];
int c[MAXN][55];
int dis[MAXN][125][125][4];
int queue[MAXQ][4];

void Bfs(int i);
void FileIO();
int main();
void Sovle(int n);

void Bfs(int i)
{
    int head = 0, tail = 1;
    queue[1][0] = x[i];
    queue[1][1] = y[i];
    queue[1][2] = q[i];
    queeu[1][3] = 0;
    dis[x[i]][y[i]][q[i]][0] = 0;
    int nx, ny, fx, k;
    while (head < tail)
    {
        ++head;
        nx = queue[head][0];
        ny = queue[head][1];
        fx = queue[head][2];
        k = queue[head][3];
    }
}
void FileIO()
{
    freopen("robot.in", "r", stdin);
    freopen("robot.out", "w", stdout);
    return;
}
int main()
{
    int n;
    scanf("%d", &n);
    char cha;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d%d%d", &x[i], &y[i], &q[i], &p[i]);
        q[i] /= 90;
        for (int j = 1; j <= p[i]; ++j)
        {
            cha = getchar();
            while (cha != 'T' && cha != 'S')
                cha = getchar();
            if (cha == 'T')
            {
                scanf("%d", c[i][j]);
                c[i][j] /= 90;
                t[i][j] = 1;
            }
            else
            {
                t[i][j] = 2;
            }
        }
    }
    Sovle(n);
}

