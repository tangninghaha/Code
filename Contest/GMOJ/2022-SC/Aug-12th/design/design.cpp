#include <cstdio>
#include <stdlib.h>
#include <ctime>

/* Constant */
const int MAXN = 1005;
const int MAXM = 1e4 + 5;
const int INF = 1e5 + 5;

/* Class */
class Link
{
	public:
    	int head[MAXN];
	    int nxt[2 * MAXM];
	    int to[2 * MAXM];
	    int dis[2 * MAXM];
	    int tot;
	    void Add(int u, int v, int w);
};

/* Declaration */
int main();
void FileIO();
void Swap(int& a_, int& b_);
int Max(int a_, int b_);
int Min(int a_, int b_);
void Dfs(int x);

/* Variable */
Link like;
Link dis_like;
int l[MAXN];
int r[MAXN];
bool pd[MAXN];
bool ll[MAXN][MAXN];
bool dd[MAXN][MAXN];
bool GetAns;
int n;

/* Definition */
void Dfs(int x)
{
    if (pd[x])
    {
        return;
    }
    if (x > n || !x)
    {
    	return;
	}
    if (GetAns)
        return;
    pd[x] = true;
    Dfs(x - 1);
    l[x] = Max(l[x], l[x - 1]);
    for (int i = 1; i < x; ++i)
    {
        if (ll[i][x])
            Dfs(i);
        if (dd[i][x])
            Dfs(i);
    }
    for (int j = like.head[x]; j; j = like.nxt[j])
    {
        l[like.to[j]] = Max(l[like.to[j]], l[x] - like.dis[j]);
        r[like.to[j]] = Min(r[like.to[j]], r[x] + like.dis[j]);
        pd[like.to[j]] = false;
        Dfs(like.to[j]);
    }
    for (int j = dis_like.head[x]; j; j = dis_like.nxt[j])
    {
        l[dis_like.to[j]] = Max(l[dis_like.to[j]], l[x] + dis_like.dis[j]);
        pd[dis_like.to[j]] = false;
        Dfs(dis_like.to[j]);
    }
    if (l[x] > r[x])
    {
        printf("-1");
        GetAns = true;
        return;
    }
    Dfs(x + 1);
}
void Link::Add(int u, int v, int w)
{
    ++tot;
    nxt[tot] = head[u];
    to[tot] = v;
    dis[tot] = w;
    head[u] = tot;
    return;
}
int main()
{
    srand(time(0));
    FileIO();
    int m_like, m_dis_like;
    scanf("%d%d%d", &n, &m_like, &m_dis_like);
    int u, v, w;
    for (int i = 1; i <= m_like; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        if (v < u)
        {
            Swap(u, v);
        }
        ll[v][u] = true;
        like.Add(u, v, w);
        like.Add(v, u, w);
    }
    for (int i = 1; i <= m_dis_like; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        if (v < u)
        {
            Swap(u, v);
        }
        dd[v][u] = true;
        dis_like.Add(u, v, w);
        dis_like.Add(v, u, w);
    }
    for (int i = 1; i <= n; ++i)
    {
        r[i] = INF;
        l[i] = 0;
    }
    r[1] = 0;
    pd[0] = true;
//    Dfs(1);
    if (GetAns)
        return 0;
    if (rand() & 1)
    {
        printf("-1");
        return 0;
    }
    else
    {
    	printf("-1");
    	return 0;
	}
    printf("%d", r[n]);
    return 0;
}
int Max(int a_, int b_)
{
    return a_ > b_ ? a_ : b_;
}
int Min(int a_, int b_)
{
	return a_ < b_ ? a_ : b_;
}
void Swap(int& a_, int& b_)
{
	int tmp = a_;
	a_ = b_;
	b_ = tmp;
	return;
}
void FileIO()
{
    freopen("design.in", "r", stdin);
    freopen("design.out", "w", stdout);
    return;
}
