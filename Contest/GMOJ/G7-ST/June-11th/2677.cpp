#include <stdio.h>

const int MAXN = 30010, MAXM = 200010;
int point[MAXN];
int head[MAXN], to[MAXM * 2], nxt[MAXM * 2], tot; // Edge
int fa[MAXN], deep[MAXN], size[MAXN], heavy_son[MAXN], fa_price[MAXN];
int top[MAXN], dfn[MAXN], rnk[MAXN], dfn_num;

namespace heavy_path
{
    void Dfs1(int x);
    void Dfs2(int x, int top_now);
}
namespace line_tree
{
    int tr[MAXN * 4 + 5000], lazy_tag[MAXN * 4 + 5000];
    void Build(int l, int r, int k);
    void Update(int l, int r, int st, int ed, int k, int sum);
    int GetAns(int l, int r, int st, int ed, int k);
    void DownLazy(int l, int r, int x);
}
void Add(int x, int y);

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &u, &v);
        Add(u, v);
        Add(v, u);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &point[i]);
    }
    heavy_path::Dfs1(1);
    heavy_path::Dfs2(1, 1);
    line_tree::Build(1, n, 1);
    int type;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &type, &u, &v);
        if (type == 1)
        {
            line_tree::Update(1, n, dfn[u], dfn[u], 1, v - point[u]);
            point[u] = v;
        }
        else
        {
            int ans = 0;
            int fu = top[u], fv = top[v];
            while(fu != fv)
            {
                if (deep[fu] > deep[fv])
                {
                    ans += line_tree::GetAns(1, n, dfn[fu], dfn[u], 1);
                    u = fa[fu];
                }
                else
                {
                    ans += line_tree::GetAns(1, n, dfn[fv], dfn[v], 1);
                    v = fa[fv];
                }
                fu = top[u];
                fv = top[v];
            }
            if (dfn[u] < dfn[v])
            {
                ans += line_tree::GetAns(1, n, dfn[u], dfn[v], 1);
            }
            else
            {
                ans += line_tree::GetAns(1, n, dfn[v], dfn[u], 1);
            }
            printf("%d\n", ans);
        }
    }
}

void Add(int x, int y)
{
    tot++;
    nxt[tot] = head[x];
    to[tot] = y;
    head[x] = tot;
}

void heavy_path::Dfs1(int x)
{
    size[x] = 1;
    deep[x] = deep[fa[x]] + 1;
    for (int i = head[x]; i; i = nxt[i])
    {
        if (to[i] != fa[x])
        {
            fa[to[i]] = x;
            Dfs1(to[i]);
            size[x] += size[to[i]];
            if (size[to[i]] > size[heavy_son[x]])
            {
                heavy_son[x] = to[i];
            }
        }
    }
    return;
}

void heavy_path::Dfs2(int x, int top_now)
{
    dfn[x] = ++dfn_num;
    rnk[dfn[x]] = x;
    top[x] = top_now;
    if (heavy_son[x])
        Dfs2(heavy_son[x], top_now);
    for (int i = head[x]; i; i = nxt[i])
    {
        if (to[i] != fa[x] && to[i] != heavy_son[x])
        {
            Dfs2(to[i], to[i]);
        }
    }
    return;
}

void line_tree::Build(int l, int r, int k)
{
    if (l == r)
    {
        tr[k] = point[rnk[l]];
        return;
    }
    int mid = (l + r) >> 1;
    Build(l, mid, k * 2);
    Build(mid + 1, r, k * 2 + 1);
    tr[k] = tr[k * 2] + tr[k * 2 + 1];
    return;
}

void line_tree::Update(int l, int r, int st, int ed, int k, int sum)
{
    if (st <= l && r <= ed)
    {
        lazy_tag[k] += sum;
        tr[k] += sum * (r - l + 1);
        return;
    }
    int mid = (l + r) >> 1;
    DownLazy(l, r, k);
    if (st <= mid)
    {
        Update(l, mid, st, ed, k * 2, sum);
    }
    if (ed > mid)
    {
        Update(mid + 1, r, st, ed, k * 2 + 1, sum);
    }
    tr[k] = tr[k * 2] + tr[k * 2 + 1];
    return;
}
int line_tree::GetAns(int l, int r, int st, int ed, int k)
{
    if (st <= l && r <= ed)
    {
        return tr[k];
    }
    int mid = (l + r) >> 1;
    DownLazy(l, r, k);
    int ret = 0;
    if (st <= mid)
    {
        ret += GetAns(l, mid, st, ed, k * 2);
    }
    if (ed > mid)
    {
        ret += GetAns(mid + 1, r, st, ed, k * 2 + 1);
    }
    return ret;
}
void line_tree::DownLazy(int l, int r, int x)
{
    if (!lazy_tag[x]) return;
    int mid = (l + r) >> 1;
    lazy_tag[x * 2] += lazy_tag[x];
    lazy_tag[x * 2 + 1] += lazy_tag[x];
    tr[x * 2] += lazy_tag[x * 2] * (mid - l + 1);
    tr[x * 2 + 1] += lazy_tag[x * 2 + 1] * (r - mid);
    lazy_tag[x] = 0;
    return;
}
