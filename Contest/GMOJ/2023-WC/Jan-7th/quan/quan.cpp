#include <cstdio>
#include <cstring>

/* Constant */
const int INF = 1e8 + 5;
const int MAXN = 105;
const int MAXQ = 1e6 + 5;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

/* Declaration */
int main();
int Min(int, int);
void Bfs(int);

/* Variable */
int queue[MAXQ][5];
int f[MAXN][MAXN][2];
int a[MAXN][2];
bool pd[MAXN][MAXN];
int map[MAXN][MAXN];
int n = 0, m = 0;
int bad_tot;
int bad[MAXN][11];

bool fz[MAXQ][11];

/* Declaration */
int main()
{
    freopen("in.txt", "r", stdin);
    char tmp;
    tmp = getchar();
    int i = 0, j = 0;
    int cnt = 0;
    while (tmp != EOF)
    {
        ++n;
        ++i;
        j = 0;
        while (tmp == 'X' || tmp == '.' || tmp == 'I')
        {
            ++j;
            if (tmp == 'X')
            {
                map[i * 2][j * 2] = 1;
                ++bad_tot;
                bad[bad_tot][0] = i * 2;
                bad[bad_tot][1] = j * 2;
            }
            else if (tmp == '.')
            {
                map[i * 2][j * 2] = 2;
            }
            else
            {
                map[i * 2][j * 2] = 3;
                ++cnt;
                a[cnt][0] = i * 2;
                a[cnt][1] = j * 2;
            }
            tmp = getchar();
        }
        m = j;
        while (tmp != 'X' && tmp != '.' && tmp != 'I' && tmp != EOF)
        {
            tmp = getchar();
        }
    }
    n = 2 * n + 1;
    m = 2 * m + 1;
    for (int x = 1; x <= cnt; ++x)
    {
        Bfs(x);
        printf("%d\n", f[1][1][1]);
    }
    return 0;
}
void Bfs(int k)
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            f[i][j][0] = f[i][j][1] = INF;
        }
    }
    int head = 0, tail = 1;
    f[1][1][0] = 0;
    queue[1][0] = 1;
    queue[1][1] = 1;
    queue[1][2] = 0;
    queue[1][3] = 4;
    int x, y;
    int this_cost;
    int nx, ny;
    int from;
    memset(fz, 0, sizeof (fz));
    while (head < tail)
    {
        ++head;
        x = queue[head][0];
        y = queue[head][1];
        from = queue[head][3];
        for (int t = 0; t < 4; ++t)
        {
            nx = x + dx[t];
            ny = y + dy[t];
            if (nx > 0 && ny > 0 && nx <= n && ny <= m && !map[nx][ny])
            {
                ++tail;
                queue[tail][0] = nx;
                queue[tail][1] = ny;
                queue[tail][4] = head;
                if ((nx < a[k][0] && ny == a[k][1])
                || (x < a[k][0] && y == a[k][1] && ((t == 2 && from == 0) || (t == 0 && from == 2))))
                {
                    queue[tail][2] = !queue[head][2];
                }
                else
                {
                    queue[tail][2] = queue[head][2];
                }
                for (int j = 1; j <= bad_tot; ++j)
                {
                    if ((nx <bad[j][0] && ny == bad[j][1])
                    || (x < bad[j][0] && y == bad[j][1] && ((t == 2 && from == 0) || (t == 0 && from == 2))))
                    {
                        fz[tail][j] = !fz[head][j];
                    }
                    else
                    {
                        fz[tail][j] = fz[head][j];
                    }
                }
                queue[tail][3] = t;
                this_cost = f[x][y][queue[head][2]] + !((nx & 1) && (ny & 1));
                if (f[nx][ny][queue[tail][2]] <= this_cost)
                {
                    --tail;
                }
                else
                {
                    if (nx == 1 && ny == 1)
                    {
//                        int tmp = tail;
//                        while (tmp)
//                        {
//                            printf("(%d,%d) <- ", queue[tmp][0], queue[tmp][1]);
//                            tmp = queue[tmp][4];
//                        }
//                        printf("\n");
                        bool pdd = false;
                        for (int j = 1; j <= bad_tot; ++j)
                        {
                            if (fz[tail][j])
                            {
                                --tail;
                                pdd = true;
                                break;
                            }
                        }
                        if (!pdd)
                        {
                            f[nx][ny][queue[tail][2]] = this_cost;
                        }
                    }
                    else
                        f[nx][ny][queue[tail][2]] = this_cost;
                }
            }
        }
    }
    return;
}
