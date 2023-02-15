#include <cstdio>
#include <cstring>

/* Constant */
const int MAXS = 32768;
const int MAXN = 5e7 + 5;

/* Declaration */
int main();
void Bfs();

/* Variable */
bool pd[MAXS][MAXS];
int twom[16];

int queue[MAXN][3];

int n;

int ans2, ans3;

/* Definition */
int main()
{
    twom[0] = 1;
    for (int i = 1; i <= 15; ++i)
    {
        twom[i] = twom[i - 1] << 1;
    }
    scanf("%d", &n);
    int x = n;
    for (int i = 1; i <= x; ++i)
    {
        memset(pd, 0, sizeof(pd));
        n = i;
        Bfs();
        printf("%d %d\n", ans2, ans3);
    }
}
void Bfs()
{
    queue[0][0] = twom[n] - 1;
    queue[0][1] = 0;
    int head = -1, tail = 0;
    int s1, s2, s3;
    bool pd2 = false;
    bool pd3 = false;
    int tail_num = 0, head_num = 0;
    int minnum;
    while (((long long)head + head_num * MAXN < (long long)tail + tail_num * MAXN) && (!pd2 || !pd3))
    {
        ++head;
        if (head == MAXN)
        {
            head = 0;

        }
        s1 = queue[head][0];
        s2 = queue[head][1];
        s3 = twom[n] - 1;
        s3 ^= s1;
        s3 ^= s2;
        if (s2 == twom[n] - 1)
        {
            ans2 = queue[head][2];
            pd2 = true;
        }
        if (s3 == twom[n] - 1)
        {
            ans3 = queue[head][2];
            pd3 = true;
        }
        minnum = n + 1;
        for (int i = 1; i <= n; ++i)
        {
            if (!((s1 >> (i - 1)) & 1))
                continue;
            for (int j = 1; j <= n; ++j)
            {
                if ((s2 >> (j - 1)) & 1)
                {
                    minnum = j;
                    break;
                }
            }
            if (minnum < i)
                continue;
            ++tail;
            if (tail == MAXN)
            {
                tail = 0;
                ++tail_num;
            }
            queue[tail][0] = s1 ^ twom[i - 1];
            queue[tail][1] = s2 ^ twom[i - 1];
            queue[tail][2] = queue[head][2] + 1;
            if (pd[queue[tail][0]][queue[tail][1]])
            {
                --tail;
                tail = (tail % MAXN + MAXN) % MAXN;
            }
            else
            {
                pd[queue[tail][0]][queue[tail][1]] = true;
            }
            break;
        }
        for (int i = 1; i <= n; ++i)
        {
            if (!((s2 >> (i - 1)) & 1))
                continue;
            for (int j = 1; j <= n; ++j)
            {
                if ((s3 >> (j - 1)) & 1)
                {
                    minnum = j;
                    break;
                }
            }
            if (minnum < i)
                continue;
            ++tail;
            if (tail == MAXN)
            {
                tail = 0;
                ++tail_num;
            }
            queue[tail][0] = s1;
            queue[tail][1] = s2 ^ twom[i - 1];
            queue[tail][2] = queue[head][2] + 1;
            if (pd[queue[tail][0]][queue[tail][1]])
            {
                --tail;
                tail = (tail % MAXN + MAXN) % MAXN;
            }
            else
            {
                pd[queue[tail][0]][queue[tail][1]] = true;
            }
            break;
        }
        for (int i = 1; i <= n; ++i)
        {
            if (!((s3 >> (i - 1)) & 1))
                continue;
            for (int j = 1; j <= n; ++j)
            {
                if ((s1 >> (j - 1)) & 1)
                {
                    minnum = j;
                    break;
                }
            }
            if (minnum < i)
                continue;
            ++tail;
            if (tail == MAXN)
            {
                tail = 0;
                ++tail_num;
            }
            queue[tail][0] = s1 ^ twom[i - 1];
            queue[tail][1] = s2;
            queue[tail][2] = queue[head][2] + 1;
            if (pd[queue[tail][0]][queue[tail][1]])
            {
                --tail;
                tail = (tail % MAXN + MAXN) % MAXN;
            }
            else
            {
                pd[queue[tail][0]][queue[tail][1]] = true;
            }
            break;
        }
    }
//    printf("%lld\n", (long long)tail + tail_num * MAXN);
    return;
}
