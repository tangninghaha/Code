#include <cstdio>

/* Constant */
const int MAXN = 1e6 + 5;
const int MAXP = 1e3 + 5;

/* Declaration */
int main();

/* Variable */
int queue[MAXN][4];
int pc[MAXP][MAXP];

/* Definition */
int main()
{
    int n;
    scanf("%d", &n);
    int head = 0, tail = 1;
    queue[1][0] = 1;
    queue[1][1] = 0;
    while (head < tail)
    {
        ++head;
        ++tail;
        queue[tail][0] = queue[head][0];
        queue[tail][1] = queue[head][1] + 1;
        queue[tail][2] = queue[head][2] + 1;
        queue[tail][3] = head;
        if (pc[queue[tail][0]][queue[tail][1]])
        {
            --tail;
        }
        else
            pc[queue[tail][0]][queue[tail][1]] = true;
        if (queue[tail][0] == n)
        {
            printf("%d\n", queue[tail][2]);
            int x = tail;
            while (x)
            {
                printf("%d %d\n", queue[x][0], queue[x][1]);
                x = queue[x][3];
            }
            return 0;
        }
        ++tail;
        queue[tail][0] = queue[head][0] * queue[head][1];
        queue[tail][1] = queue[head][1];
        queue[tail][2] = queue[head][2] + 1;
        queue[tail][3] = head;
        if (pc[queue[tail][0]][queue[tail][1]])
        {
            --tail;
        }
        else
            pc[queue[tail][0]][queue[tail][1]] = true;
        if (queue[tail][0] == n)
        {
            printf("%d\n", queue[tail][2]);
            int x = tail;
            while (x)
            {
                printf("%d %d\n", queue[x][0], queue[x][1]);
                x = queue[x][3];
            }
            return 0;
        }
    }
}
