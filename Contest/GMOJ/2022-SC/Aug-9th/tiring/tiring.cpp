#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <algorithm>

using std::pair;
using std::make_pair;
const int MAXN = 3e5 + 5, MAXM = 9e5 + 5;

bool vis[MAXN];
struct Graph
{
    int head[MAXN];
    int nxt[MAXM * 2];
    int to[MAXM * 2];
    double dis[MAXM * 2];
    void Add(int x, int y, double z);
    int tot;
};
class Heap
{
    private:
        pair<double, int> num[MAXN];
        int sz;
    public:
        void Pop();
        pair<double, int> Front();
        void Up(int x);
        void Down(int x);
        void Insert(pair<double, int> x);
};
Graph G;

double Abs(double x);
void Dij(int n);
void FileIO();
int main();
template <typename T> void Swap(T &a, T &b);

void Graph::Add(int x, int y, double z)
{
    ++tot;
    nxt[tot] = head[x];
    to[tot] = y;
    dis[tot] = z;
    head[x] = tot;
    return;
}
double diss[MAXN];

Heap h;

void Heap::Pop()
{
    Swap(num[1], num[sz]);
    --sz;
    Down(1);
    return;
}
pair<double, int> Heap::Front()
{
    return num[1];
}
void Heap::Up(int x)
{
    int nxt = x / 2;
    while (num[nxt] > num[x] && nxt)
    {
        Swap(num[nxt], num[x]);
        x = nxt;
        nxt = x / 2;
    }
    return;
}
void Heap::Down(int x)
{
    int nxt = x * 2;
    while ((nxt <= sz && num[nxt] < num[x])
           || (nxt + 1 <= sz && num[nxt + 1] < num[x]))
    {
        if (num[nxt + 1] < num[nxt] && nxt + 1 <= sz)
        {
            ++nxt;
        }
        Swap(num[nxt], num[x]);
        x = nxt;
        nxt = x * 2;
    }
    return;
}
void Heap::Insert(pair<double, int> x)
{
    ++sz;
    num[sz] = x;
    Up(sz);
    return;
}



double Abs(double x)
{
    return x > 0 ? x : -x;
}
void Dij(int n)
{
    diss[1] = 0;
    pair<double, int> now;
    h.Insert(make_pair(0.0, 1));
    int p = 0;
    for (int i = 1; i <= n; ++i)
    {
        now = h.Front();
        while (vis[now.second])
        {
            h.Pop();
            now = h.Front();
        }
        p = now.second;
        vis[now.second] = true;
        h.Pop();
        for (int j = G.head[p]; j; j = G.nxt[j])
        {
            if (!vis[G.to[j]])
            {
                if (diss[G.to[j]] > diss[p] + Abs(G.dis[j]))
                {
                    diss[G.to[j]] = diss[p] + Abs(G.dis[j]);
                    h.Insert(make_pair(diss[G.to[j]], G.to[j]));
                }
            }
        }
    }
    return;
}
void FileIO()
{
    freopen("tiring.in", "r", stdin);
    freopen("tiring.out", "w", stdout);
}
int main()
{
    FileIO();
    int n, m;
    scanf("%d%d", &n, &m);
    int u, v, x;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &u, &v, &x);
        G.Add(3 * u - 2, 3 * v - 1, x);
        G.Add(3 * u - 1, 3 * v, 1.0 / (1.0 - x));
        G.Add(3 * u, 3 * v - 2, 1.0 * (x - 1.0) / x);
        G.Add(3 * v - 2, 3 * u - 1, x);
        G.Add(3 * v - 1, 3 * u, 1.0 / (1.0 - x));
        G.Add(3 * v, 3 * u - 2, 1.0 * (x - 1.0) / x);
    }
    for (int i = 1; i <= 3 * n; ++i)
    {
        diss[i] = 1e8;
    }
    double INF = diss[1];
    Dij(3 * n);
    double ans = diss[3 * n];
    if (diss[3 * n - 1] < ans)
    {
        ans = diss[3 * n - 1];
    }
    if (diss[3 * n - 2] < ans)
    {
        ans = diss[3 * n - 2];
    }
    if (ans == INF)
    {
        printf("chu ti ren shi zhi zhang");
        return 0;
    }
    printf("%.3lf", ans);
    return 0;
}
template <typename T> void Swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
    return;
}
