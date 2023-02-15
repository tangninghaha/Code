#include <cstdio>
#include <cstdlib>
#include <ctime>

/* Constant */
const int N = 100;
const int M = 50;
const int D = 10000000;

/* Declaration */
bool vis[N + 5][N + 5];

/* Definition */

int main()
{
    freopen("in.txt", "w", stdout);
    srand(time(0));
    printf("%d %d\n", N, M);
    int st, ed, dis;
    for (int i = 1; i <= M; ++i)
    {
        st = rand() % N + 1;
        ed = rand() % N + 1;
        while (vis[st][ed])
        {
            if (rand() & 1)
                st = rand() % N + 1;
            else
                ed = rand() % N + 1;
        }
        vis[st][ed] = vis[ed][st] = true;
        dis = rand() % D + 1;
        printf("%d %d %d\n", st, ed, dis);
    }
    return 0;
}
