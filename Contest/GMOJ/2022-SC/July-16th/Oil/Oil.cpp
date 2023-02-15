#include <stdio.h>
const int MAXN = 26;
const int MAXQ = 1e4;
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int n, m;
char map[MAXN][MAXN];
int vis[MAXN][MAXN];
int queue[MAXQ][3];
void Bfs(int stx, int sty, int type);
int main()
{
    scanf("%d%d", &n, &m);
    int stx, sty;
    int edx, edy;
    char cha;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cha = getchar();
            while (cha != 124 &&cha != '-' && cha != '+' && cha != '1'
                   && cha != '2' && cha != '3' && cha != '4' && cha != '.'
                   && cha != 'M' && cha != 'Z')
            {
                cha = getchar();
            }
            map[i][j] = cha;
            if (map[i][j] == 'M')
            {
                stx = i;
                sty = j;
            }
            if (map[i][j] == 'Z')
            {
                edx = i;
                edy = j;
            }
        }
    }
    vis[stx][sty] = 1;
    vis[edx][edy] = 2;
    Bfs(stx, sty, 1);
    Bfs(edx, edy, 2);
    int tot = 2;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (map[i][j] != '.' && ! vis[i][j])
            {
                vis[i][j] = ++tot;
                Bfs(i, j, tot);
            }
        }
    }
    int nx, ny, k;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (map[i][j] != '!')
                continue;
            k = 0;
            for (int t = 0; t < 4; ++t)
            {
                nx = i + dx[t];
                ny = j + dy[t];
                if (vis[nx][ny])
                {
                    ++k;
                }
            }
            if (k == 4)
            {
                printf("%d %d +", i, j);
            }
            else if (k > 1)
            {
                int x1 = -1, x2 = -1;
                nx = i + dx[0];
                ny = j + dy[0];
                if (vis[nx][ny] && map[nx][ny] != '2' && map[nx][ny] != '3'
                    && map[nx][ny] != '-')
                {
                    x1 = 0;
                }
                nx = i + dx[1];
                ny = j + dy[1];
                if (vis[nx][ny] && map[nx][ny] != '1' && map[nx][ny] != '4'
                    && map[nx][ny] != '-')
                {
                    if (x1 == -1)
                        x1 = 1;
                    else
                        x2 = 1;
                }
                nx = i + dx[2];
                ny = j + dy[2];
                if (vis[nx][ny] && map[nx][ny] != '3' && map[nx][ny] != '4'
                    && map[nx][ny] != '|')
                {
                    if (x1 == -1)
                        x1 = 2;
                    else
                        x2 = 2;
                }
                nx = i + dx[3];
                ny = j + dy[3];
                if (vis[nx][ny] && map[nx][ny] != '1' && map[nx][ny] != '2'
                    && map[nx][ny] != '|')
                {
                    if (x1 == -1)
                        x1 = 3;
                    else
                        x2 = 3;
                }
                printf("%d %d ", i, j);
                if (x1 == 0 && x2 == 1)
                    printf("%c", 124);
                else if (x1 == 0 && x2 == 2)
                    printf("3");
                else if (x1 == 0 && x2 == 3)
                    printf("2");
                else if (x1 == 1 && x2 == 2)
                    printf("4");
                else if (x1 == 1 && x2 == 3)
                    printf("1");
                else if (x1 == 2 && x2 == 3)
                    printf("-");
            }
        }
    }
    return 0;
}
void Bfs(int stx, int sty, int type)
{
    int head = 0, tail = 0;
    for (int i = 0; i < 4; ++i)
    {
        int nx = stx + dx[i], ny = sty + dy[i];
        if (nx > 0 && nx <= n && ny > 0 && ny <= m && map[nx][ny] != '.'
            && !vis[nx][ny])
        {
            ++tail;
            queue[tail][0] = nx;
            queue[tail][1] = ny;
            queue[tail][2] = i;
            vis[nx][ny] = type;
        }
    }
    int x, y, fx;
    while (head < tail)
    {
        ++head;
        x = queue[head][0];
        y = queue[head][1];
        fx = queue[head][2];
        if (map[x][y] == 124)
        {
            if (!vis[x + 1][y] && x + 1 > 0 && x + 1 <= n && fx == 1)
            {
                if (map[x + 1][y] == '.')
                {
                    map[x + 1][y] = '!';
                    continue;
                }
                ++tail;
                vis[x + 1][y] = type;
                queue[tail][0] = x + 1;
                queue[tail][1] = y;
                queue[tail][2] = 1;
            }
            if (!vis[x - 1][y] && x - 1 > 0 && x - 1 <= n && fx == 0)
            {
                if (map[x - 1][y] == '.')
                {
                    map[x - 1][y] = '!';
                    continue;
                }
                ++tail;
                vis[x - 1][y] = type;
                queue[tail][0] = x - 1;
                queue[tail][1] = y;
                queue[tail][2] = 0;
            }
        }
        else if (map[x][y] == '-')
        {
            if (!vis[x][y + 1] && y + 1 > 0 && y + 1 <= m && fx == 3)
            {
                if (map[x][y + 1] == '.')
                {
                    map[x][y + 1] = '!';
                    continue;
                }
                ++tail;
                vis[x][y + 1] = type;
                queue[tail][0] = x;
                queue[tail][1] = y + 1;
                queue[tail][2] = 3;
            }
            if (!vis[x][y - 1] && y - 1 > 0 && y - 1 <= m && fx == 2)
            {
                if (map[x][y - 1] == '.')
                {
                    map[x][y - 1] = '!';
                    continue;
                }
                ++tail;
                vis[x][y - 1] = type;
                queue[tail][0] = x;
                queue[tail][1] = y - 1;
                queue[tail][2] = 2;
            }
        }
        else if (map[x][y] == '+')
        {
            if (!vis[x + 1][y] && x + 1 > 0 && x + 1 <= n && fx != 0)
            {
                if (map[x + 1][y] == '.')
                {
                    map[x + 1][y] = '!';
                    continue;
                }
                ++tail;
                vis[x + 1][y] = type;
                queue[tail][0] = x + 1;
                queue[tail][1] = y;
                queue[tail][2] = 1;
            }
            if (!vis[x - 1][y] && x - 1 > 0 && x - 1 <= n && fx != 1)
            {
                if (map[x - 1][y] == '.')
                {
                    map[x - 1][y] = '!';
                    continue;
                }
                ++tail;
                vis[x - 1][y] = type;
                queue[tail][0] = x - 1;
                queue[tail][1] = y;
                queue[tail][2] = 0;
            }
            if (!vis[x][y + 1] && y + 1 > 0 && y + 1 <= m && fx != 2)
            {
                if (map[x][y + 1] == '.')
                {
                    map[x][y + 1] = '!';
                    continue;
                }
                ++tail;
                vis[x][y + 1] = type;
                queue[tail][0] = x;
                queue[tail][1] = y + 1;
                queue[tail][2] = 3;
            }
            if (!vis[x][y - 1] && y - 1 > 0 && y - 1 <= m && fx != 3)
            {
                if (map[x][y - 1] == '.')
                {
                    map[x][y - 1] = '!';
                    continue;
                }
                ++tail;
                vis[x][y - 1] = type;
                queue[tail][0] = x;
                queue[tail][1] = y - 1;
                queue[tail][2] = 2;
            }
        }
        else if (map[x][y] == '1')
        {
            if (!vis[x + 1][y] && x + 1 > 0 && x + 1 <= n && fx == 2)
            {
                if (map[x + 1][y] == '.')
                {
                    map[x + 1][y] = '!';
                    continue;
                }
                ++tail;
                vis[x + 1][y] = type;
                queue[tail][0] = x + 1;
                queue[tail][1] = y;
                queue[tail][2] = 1;
            }
            if (!vis[x][y + 1] && y + 1 > 0 && y + 1 <= m && fx == 0)
            {
                if (map[x][y + 1] == '.')
                {
                    map[x][y + 1] = '!';
                    continue;
                }
                ++tail;
                vis[x][y + 1] = type;
                queue[tail][0] = x;
                queue[tail][1] = y + 1;
                queue[tail][2] = 3;
            }
        }
        else if (map[x][y] == '2')
        {
            if (!vis[x - 1][y] && x - 1 > 0 && x - 1 <= n && fx == 2)
            {
                if (map[x - 1][y] == '.')
                {
                    map[x - 1][y] = '!';
                    continue;
                }
                ++tail;
                vis[x - 1][y] = type;
                queue[tail][0] = x - 1;
                queue[tail][1] = y;
                queue[tail][2] = 0;
            }
            if (!vis[x][y + 1] && y + 1 > 0 && y + 1 <= m && fx == 1)
            {
                if (map[x][y + 1] == '.')
                {
                    map[x][y + 1] = '!';
                    continue;
                }
                ++tail;
                vis[x][y + 1] = type;
                queue[tail][0] = x;
                queue[tail][1] = y + 1;
                queue[tail][2] = 3;
            }
        }
        else if (map[x][y] == '3')
        {
            if (!vis[x - 1][y] && x - 1 > 0 && x - 1 <= n && fx == 3)
            {
                if (map[x - 1][y] == '.')
                {
                    map[x - 1][y] = '!';
                    continue;
                }
                ++tail;
                vis[x - 1][y] = type;
                queue[tail][0] = x - 1;
                queue[tail][1] = y;
                queue[tail][2] = 0;
            }
            if (!vis[x][y - 1] && y - 1 > 0 && y - 1 <= m && fx == 1)
            {
                if (map[x][y - 1] == '.')
                {
                    map[x][y - 1] = '!';
                    continue;
                }
                ++tail;
                vis[x][y - 1] = type;
                queue[tail][0] = x;
                queue[tail][1] = y - 1;
                queue[tail][2] = 2;
            }
        }
        else if (map[x][y] == '4')
        {
            if (!vis[x + 1][y] && x + 1 > 0 && x + 1 <= n && fx == 3)
            {
                if (map[x + 1][y] == '.')
                {
                    map[x + 1][y] = '!';
                    continue;
                }
                ++tail;
                vis[x + 1][y] = type;
                queue[tail][0] = x + 1;
                queue[tail][1] = y;
                queue[tail][2] = 1;
            }
            if (!vis[x][y - 1] && y - 1 > 0 && y - 1 <= m && fx == 0)
            {
                if (map[x][y - 1] == '.')
                {
                    map[x][y - 1] = '!';
                    continue;
                }
                ++tail;
                vis[x][y - 1] = type;
                queue[tail][0] = x;
                queue[tail][1] = y - 1;
                queue[tail][2] = 2;
            }
        }
    }
    return;
}
    
