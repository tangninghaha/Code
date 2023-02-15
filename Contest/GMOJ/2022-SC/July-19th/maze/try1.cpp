#include <stdio.h>
#include <cstring>
int map[5][5005];
int Bfs(int stx, int sty, int edx, int edy);
int queue[15005][3];
bool vis[5][5005];
const int dx[3] = {-1, 1, 0}, dy[3] = {0, 0, 1};
int n, m;
int main()
{
    freopen("maze.in", "r", stdin);
    freopen("maze.out", "w", stdout);
    int q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &map[i][j]);
        }
    }
    int opt, num1, num2, num3, num4;
    for (int i = 1; i <= q; ++i)
    {
        scanf("%d", &opt);
        if (opt == 1)
        {
            scanf("%d%d", &num1, &num2);
            map[num1][num2] = !map[num1][num2];
        }
        if (opt == 2)
        {
            scanf("%d%d%d%d", &num1, &num2, &num3, &num4);
            printf("%d\n", Bfs(num1, num2, num3, num4));
        }
    }
    return 0;
}
int Bfs(int stx, int sty, int edx, int edy)
{
    if (stx == edx && sty == edy)
        return 0;
    memset(vis, 0, sizeof(vis));
    int head = 0, tail = 1;
    queue[1][0] = stx;
    queue[1][1] = sty;
    queue[1][2] = 0;
    vis[stx][sty] = true;
    int x, y;
    while (head < tail)
    {
        ++head;
        x = queue[head][0];
        y = queue[head][1];
        for (int t = 0; t < 3; ++t)
        {
            int nx = x + dx[t], ny = y + dy[t];
            if (nx > 0 && nx <= n && ny > 0 && ny <= m && map[nx][ny] 
                && !vis[nx][ny])
            {
                ++tail;
                queue[tail][0] = nx;
                queue[tail][1] = ny;
                queue[tail][2] = queue[head][2] + 1;
                if (nx == edx && ny == edy)
                {
                    return queue[tail][2];
                }
            }
        }
    }
    return -1;
}
