#include <cstdio>

#define DEBUG

/* Constant */
const int MAXN = 55;
const int MAXK = 15;
const int MAXS = 1030;
const int MAXQ = 3e6 + 5;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

const int INF = 1e8 + 5;

/* Declaration */
int main();
void Bfs();
int Min(int, int);

#ifdef DEBUG
void Print(int x);
#endif

/* Variable */

#ifdef DEBUG
int fromd[MAXQ];
#endif

char map[MAXN][MAXN];
int rk[MAXN][MAXN];
bool kind[MAXK];
int n, m;
int sp_tot;
int sp[MAXN][2];

int twom[MAXK];
int f[MAXN][MAXN][MAXS];

int queue[MAXQ][4];

int ans[MAXK];

/* Definition */
int main()
{
    twom[0] = 1;
    for (int i = 1; i <= 10; ++i)
    {
        twom[i] = twom[i - 1] << 1;
    }

    freopen("in.txt", "r", stdin);
    char tmp;
    tmp = getchar();
    int good_tot = 0;
    while (tmp != EOF)
    {
        while (tmp != 'X' && tmp != '.' && tmp != 'I' && tmp != EOF)
            tmp = getchar();
        if (tmp == EOF)
            break;
        ++n;
        m = 0;
        while (tmp == 'X' || tmp == '.' || tmp == 'I')
        {
            ++m;
            map[n][m] = tmp;
            if (tmp == 'X')
            {
                ++sp_tot;
                sp[sp_tot][0] = n;
                sp[sp_tot][1] = m;
                kind[sp_tot] = 0;
                rk[n][m] = sp_tot;
            }
            else if (tmp == 'I')
            {
                ++good_tot;
                ++sp_tot;
                sp[sp_tot][0] = n;
                sp[sp_tot][1] = m;
                kind[sp_tot] = 1;
                rk[n][m] = sp_tot;
            }
            tmp = getchar();
        }
    }

    Bfs();

    int num = 0;
    for (int i = 1; i <= good_tot; ++i)
    {
        ans[i] = INF;
    }
    for (int i = 1; i < twom[sp_tot]; ++i)
    {
        num = 0;
        for (int j = 1; j <= sp_tot; ++j)
        {
            if ((i >> (j - 1)) & 1)
            {
                if (kind[j])
                {
                    ++num;
                }
                else
                {
                    break;
                }
            }
        }
        ans[num] = Min(ans[num], f[0][0][i]);
    }
    for (int i = 1; i <= good_tot; ++i)
    {
        printf("%d\n", ans[i]);
    }
}
void Bfs()
{
    int head = 0, tail = 1;
    queue[1][0] = 0;
    queue[1][1] = 0;
    queue[1][2] = 4;
    queue[1][3] = 0;

    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= m; ++j)
        {
            for (int k = 0; k < twom[sp_tot]; ++k)
            {
                f[i][j][k] = INF;
            }
        }
    }
    f[0][0][0] = 0;

    int nx, ny;
    int from;
    int s;
    int ns;
    int x, y;
    while (head < tail)
    {
        ++head;
        x = queue[head][0];
        y = queue[head][1];
        from = queue[head][2];
        s = queue[head][3];
        for (int t = 0; t < 4; ++t)
        {
            if ((from == 1 && t == 0) || (from == 0 && t == 1) || (from == 2 && t == 3) || (from == 3 && t == 2))
                continue;
            nx = x + dx[t];
            ny = y + dy[t];
            if (nx < 0 || ny < 0 || nx > n || ny > m)
                continue;

            ++tail;
#ifdef DEBUG
            fromd[tail] = head;
#endif
            queue[tail][0] = nx;
            queue[tail][1] = ny;
            queue[tail][2] = t;
            ns = s;
            for (int i = 1; i <= sp_tot; ++i)
            {
                if (nx < sp[i][0] && ((sp[i][1] == ny && t == 3) || (sp[i][1] == y && t == 2)))
                {
                    ns = ns ^ twom[rk[sp[i][0]][sp[i][1]] - 1];
                }
            }
            queue[tail][3] = ns;
            if (f[nx][ny][ns] > f[x][y][s] + 1)
            {
//                if (nx == 0 && ny == 0 && ns == 8)
//                    Print(tail);
                f[nx][ny][ns] = f[x][y][s] + 1;
            }
            else
            {
                --tail;
            }
        }
    }
    return;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}

#ifdef DEBUG
void Print(int _x)
{
    while (_x)
    {
        printf("(%d, %d)", queue[_x][0], queue[_x][1]);
        if (fromd[_x])
            printf("<-");
        _x = fromd[_x];
    }
    printf("\n");
}
#endif
