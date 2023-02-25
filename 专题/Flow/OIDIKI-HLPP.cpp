#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;
const int N = 1200, M = 120000, INF = 0x3f3f3f3f;
int n, m, s, t;

struct qxx
{
    int nex, t, v;
};

qxx e[M * 2 + 1];
int h[N + 1], cnt = 1;

void add_path(int f, int t, int v)
{
    e[++cnt] = (qxx) {h[f], t, v}, h[f] = cnt;
}

void add_flow(int f, int t, int v)
{
    add_path(f, t, v);
    add_path(t, f, 0);
}

int ht[N + 1], ex[N + 1],
    gap[N];  // ??; ???; gap ?? gap[i] ???? i ??????
stack<int> B[N];  // ? B[i] ????? ht[v]==i ?v
int level = 0;    // ?????????

int push(int u)        // ????????????????
{
    bool init = u == s;  // ??????
    for (int i = h[u]; i; i = e[i].nex)
    {
        const int &v = e[i].t, &w = e[i].v;
        if (!w || init == false && ht[u] != ht[v] + 1)  // ???????????1
            continue;
        int k = init ? w : min(w, ex[u]);
        // ??????????????,????????????????
        if (v != s && v != t && !ex[v]) B[ht[v]].push(v), level = max(level, ht[v]);
        ex[u] -= k, ex[v] += k, e[i].v -= k, e[i ^ 1].v += k;  // push
        if (!ex[u]) return 0;  // ??????????
    }
    return 1;
}

void relabel(int u)    // ????(??)
{
    ht[u] = INF;
    for (int i = h[u]; i; i = e[i].nex)
        if (e[i].v) ht[u] = min(ht[u], ht[e[i].t]);
    if (++ht[u] < n)    // ??????? n ???
    {
        B[ht[u]].push(u);
        level = max(level, ht[u]);
        ++gap[ht[u]];  // ????,?? gap
    }
}

bool bfs_init()
{
    memset(ht, 0x3f, sizeof(ht));
    queue<int> q;
    q.push(t), ht[t] = 0;
    while (q.size())    // ?? BFS, ?????????????
    {
        int u = q.front();
        q.pop();
        for (int i = h[u]; i; i = e[i].nex)
        {
            const int &v = e[i].t;
            if (e[i ^ 1].v && ht[v] > ht[u] + 1) ht[v] = ht[u] + 1, q.push(v);
        }
    }
    return ht[s] != INF;  // ??????,?? 0
}

// ?????????????, ???????????? 0
int select()
{
    while (B[level].size() == 0 && level > -1) level--;
    return level == -1 ? 0 : B[level].top();
}

int hlpp()                    // ?????
{
    if (!bfs_init()) return 0;  // ????
    memset(gap, 0, sizeof(gap));
    for (int i = 1; i <= n; i++)
        if (ht[i] != INF) gap[ht[i]]++;  // ??? gap
    ht[s] = n;
    push(s);  // ?????
    int u;
    while ((u = select()))
    {
        B[level].pop();
        if (push(u))    // ????
        {
            if (!--gap[ht[u]])
                for (int i = 1; i <= n; i++)
                    if (i != s && i != t && ht[i] > ht[u] && ht[i] < n + 1)
                        ht[i] = n + 1;  // ????? n+1 ??????????
            relabel(u);
        }
    }
    return ex[t];
}

int main()
{
    freopen("in.txt", "r", stdin);
    scanf("%d%d", &m, &n);
    s = 1;
    t = n;
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        add_flow(u, v, w);
    }
    printf("%d", hlpp());
    return 0;
}

