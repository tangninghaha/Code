#include <stdio.h>
#include <queue>
#define INF 1000000010

const int MAXN = 105, MAXM = 10005, MAXQ = 100005;

struct Queue
{
    int size;
    int a[MAXQ];
    int num[MAXQ];
    void up(int x);
    void down(int x);
    int front();
    void pop();
    bool empty();
    void insert(int ax, int numb);
    int search[MAXN];
};

int min(int a, int b);
int Edge[MAXN][MAXN];
int f[MAXN][11];
Queue queue;
int vis[MAXN];
int n, m, k;
void swap(int &a, int &b);

void Bfs();
void Init();

int main()
{
//    freopen("data3.in", "r", stdin);
    Init();
    scanf("%d%d%d", &n, &m, &k);
    int u, v, w;
    for(int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        if (Edge[u][v] == INF)
        {
            Edge[u][v] = w;
        }
        else
        {
            if (Edge[u][v] > w)
                Edge[u][v] = w;
        }
    }
    Bfs();
    int ans = INF;
    for (int i = 0; i <= k; ++i)
    {
        ans = min(ans, f[n][i]);
    }
    printf("%d", ans == INF ? -1 : ans);
    return 0;
}

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
void Init()
{
    for (int i = 2; i < MAXN; ++i)
    {
        for (int j = 0; j < 11; ++j)
        {
            f[i][j] = INF;
        }
    }
    for (int i = 0; i < MAXN; ++i)
    {
        for (int j = 0; j < MAXN; ++j)
        {
            Edge[i][j] = INF;
        }
    }
    return;
}

void Bfs()
{
    queue.insert(0, 1);
    int now = 0, min_dis;
    while (!queue.empty())
    {
        now = queue.front();
        queue.pop();
        vis[now]++;
        for (int i = 1; i <= n; ++i)
        {
            if (Edge[now][i] != INF && now != i && vis[i] < 1)
            {
                min_dis = INF;
                for (int j = 0; j <= k; ++j)
                {
                    if (Edge[i][now] != INF)
                    {
                        f[i][j] = min(f[i][j], f[now][j] + Edge[now][i]);
                        min_dis = min(min_dis, f[i][j]);
                    }
                    else if(j + 1 <= k)
                    {
                        f[i][j + 1] = min(f[i][j + 1],
                                          f[now][j] + Edge[now][i] * 2);
                        min_dis = min(min_dis, f[i][j + 1]);
                    }
                }
                queue.insert(min_dis, i);
            }
        }
    }
    return;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

void Queue::down(int x)
{
    int nxt = x * 2;
    while ((a[x] > a[nxt] && nxt <= size) || (a[x] > a[nxt + 1] && nxt + 1 <= size))
    {
        if (a[nxt + 1] < a[nxt]) ++nxt;
        swap(a[x], a[nxt]);
        search[num[nxt]] = x;
        search[num[x]] = nxt;
        swap(num[x], num[nxt]);
        x = nxt;
        nxt = x * 2;
    }
    return;
}

void Queue::up(int x)
{
    int nxt = x / 2;
    while(a[nxt] > a[x] && nxt >= 1)
    {
        swap(a[nxt], a[x]);
        search[num[nxt]] = x;
        search[num[x]] = nxt;
        swap(num[nxt], num[x]);
        x = nxt;
        nxt = x / 2;
    }
    return;
}

int Queue::front()
{
    return num[1];
}

void Queue::pop()
{
    search[num[1]] = 0;
    swap(a[1], a[size]);
    swap(num[1], num[size]);
    --size;
    down(1);
    return;
}

bool Queue::empty()
{
    return size == 0;
}

void Queue::insert(int ax, int numb)
{
    if (search[numb] != 0)
    {
        a[search[numb]] = min(a[search[numb]], ax);
        up(search[numb]);
    }
    else
    {
        ++size;
        a[size] = ax;
        num[size] = numb;
        search[numb] = size;
        up(size);
    }
    return;
}
