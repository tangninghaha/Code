#include <stdio.h>
const int MAXN = 1e5 + 5;

struct Node
{
    long long x;
    long long y;
    int type;
    int bh;
};

Node x[MAXN];
Node y[MAXN];
int rk_x[MAXN], rk_y[MAXN];
Node ans[4 * MAXN];
int len[4 * MAXN];
int vis[MAXN][4];
int fx[MAXN * 4];

int CmpX(const Node &a, const Node &b);
int CmpY(const Node &a, const Node &b);
void FileIO();
int main();
void QsortX(int l, int r, Node *a);
Node Sovle(int n, long long t);
void Swap(Node &a, Node &b);

int CmpX(const Node &a, const Node &b)
{
    if (a.x < b.x)
        return -1;
    if (a.x > b.x)
        return 1;
    if (a.y < b.y)
        return -1;
    if (a.y > b.y)
        return 1;
    return 0; 
}
int CmpY(const Node &a, const Node &b)
{
    if (a.y < b.y)
        return -1;
    if (a.y > b.y)
        return 1;
    if (a.x < b.x)
        return -1;
    if (a.x > b.x)
        return 1;
    return 0; 
}
void FileIO()
{
    freopen("mir.in", "r", stdin);
    freopen("mir.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int n, m;
    long long k;
    scanf("%d%d%lld", &n, &m, &k);
    int xx, yy;
    char cha;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d %c", &xx, &yy, &cha);
        x[i].x = y[i].x = xx;
        x[i].y = y[i].y = yy;
        if (cha == '/')
        {
            x[i].type = y[i].type = 0;
        }
        else
        {
            x[i].type = y[i].type = 1;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        x[i].bh = y[i].bh = i;
    }
    Node anss = Sovle(n, k);
    printf("%lld %lld", anss.x, anss.y);
    return 0;
}
void QsortX(int l, int r, Node *a)
{
    int i = l, j = r;
    Node mid = a[(l + r) >> 1];
    while (i <= j)
    {
        while (CmpX(a[i], mid) < 0)
            ++i;
        while (CmpX(a[j], mid) > 0)
            --j;
        if (i <= j)
        {
            Swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        QsortX(i, r, a);
    if (l < j)
        QsortX(l, j, a);
    return;
}
void QsortY(int l, int r, Node *a)
{
    int i = l, j = r;
    Node mid = a[(l + r) >> 1];
    while (i <= j)
    {
        while (CmpY(a[i], mid) < 0)
            ++i;
        while (CmpY(a[j], mid) > 0)
            --j;
        if (i <= j)
        {
            Swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        QsortY(i, r, a);
    if (l < j)
        QsortY(l, j, a);
    return;
}
Node Sovle(int n, long long t)
{
    Node ret;
    QsortX(1, n, x);
    QsortY(1, n, y);
    for (int i = 1; i <= n; ++i)
    {
        rk_x[x[i].bh] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        rk_y[y[i].bh] = i;
    }
    int now = -1;
    int drct = 3, last_drct;
    for (int i = 1; i <= n; ++i)
    {
        if (x[i].y == 0)
        {
            if (x[i].x > 0)
            {
                ret.x = x[i].x;
                ret.y = x[i].y;
                now = x[i].bh;
                break;
            }
        }
    }
    if (now == -1)
    {
        ret.x = t;
        ret.y = 0;
        return ret;
    }
    int num = 0;
    long long i = ret.x;
    ans[++num] = ret;
    len[num] = ret.x;
    vis[now][3] = num;
    if (x[rk_x[now]].type == 0)
    {
        drct = 0;
    }
    else
    {
        drct = 1;
    }
    last_drct = 3;
    Node nxt;
    int st, ed;
    while (i < t)
    {
        if (drct == 0)
        {
            if (rk_x[now] == n)
            {
                ret.x = x[rk_x[now]].x;
                ret.y = x[rk_x[now]].y;
                if (i != t)
                {
                    ret.y += t - i;
                }
                i = t;
                continue;
            }
            if (x[rk_x[now] + 1].x == x[rk_x[now]].x)
            {
                nxt = x[rk_x[now] + 1];
                i += nxt.y - x[rk_x[now]].y;
                ret.x = nxt.x;
                ret.y = nxt.y;
                if (i > t)
                {
                    ret.y -= i - t;
                    i = t;
                    continue;
                }
                if (vis[nxt.bh][drct])
                {
                    st = vis[nxt.bh][drct];
                    ed = vis[now][last_drct];
                    break;
                }
                if (nxt.type == 0)
                {
                    drct = 3;
                }
                else
                {
                    drct = 2;
                }
                last_drct = 0;
                now = nxt.bh;
                ans[++num] = ret;
                len[num] = i;
                fx[num] = drct;
                vis[now][last_drct] = num;
            }
            else
            {
                ret.x = ans[num].x;
                ret.y = ans[num].y + (t - i);
                return ret;
            }
        }
        else if (drct == 1)
        {
            if (rk_x[now] == 1)
            {
                ret.x = x[rk_x[now]].x;
                ret.y = x[rk_x[now]].y;
                if (i != t)
                {
                    ret.y -= t - i;
                }
                i = t;
                continue;
            }
            if (x[rk_x[now] - 1].x == x[rk_x[now]].x)
            {
                nxt = x[rk_x[now] - 1];
                i += x[rk_x[now]].y - nxt.y;
                ret.x = nxt.x;
                ret.y = nxt.y;
                if (i > t)
                {
                    ret.y += i - t;
                    i = t;
                    continue;
                }
                if (vis[nxt.bh][drct])
                {
                    st = vis[nxt.bh][drct];
                    ed = vis[now][last_drct];
                    break;
                }
                if (nxt.type == 0)
                {
                    drct = 2;
                }
                else
                {
                    drct = 3;
                }
                last_drct = 1;
                now = nxt.bh;
                ans[++num] = ret;
                len[num] = i;
                fx[num] = drct;
                vis[now][last_drct] = num;
            }
            else
            {
                ret.x = ans[num].x;
                ret.y = ans[num].y - (t - i);
                return ret;
            }
        }
        else if (drct == 2)
        {
            if (rk_y[now] == 1)
            {
                ret.x = x[rk_x[now]].x;
                ret.y = x[rk_x[now]].y;
                if (i != t)
                {
                    ret.x -= t - i;
                }
                i = t;
                continue;
            }
            if (y[rk_y[now] - 1].y == y[rk_y[now]].y)
            {
                nxt = y[rk_y[now] - 1];
                i += y[rk_y[now]].x - nxt.x;
                ret.x = nxt.x;
                ret.y = nxt.y;
                if (i > t)
                {
                    ret.x += i - t;
                    i = t;
                    continue;
                }
                if (vis[nxt.bh][drct])
                {
                    st = vis[nxt.bh][drct];
                    ed = vis[now][last_drct];
                    break;
                }
                if (nxt.type == 0)
                {
                    drct = 1;
                }
                else
                {
                    drct = 0;
                }
                last_drct = 2;
                now = nxt.bh;
                ans[++num] = ret;
                len[num] = i;
                fx[num] = drct;
                vis[now][last_drct] = num;
            }
            else
            {
                ret.x = ans[num].x - (t - i);
                ret.y = ans[num].y;
                return ret;
            }
        }
        else if (drct == 3)
        {
            if (rk_y[now] == n)
            {
                ret.x = x[rk_x[now]].x;
                ret.y = x[rk_x[now]].y;
                if (i != t)
                {
                    ret.x += t - i;
                }
                i = t;
                continue;
            }
            if (y[rk_y[now] + 1].y == y[rk_y[now]].y)
            {
                nxt = y[rk_y[now] + 1];
                i += nxt.x - y[rk_y[now]].x;
                ret.x = nxt.x;
                ret.y = nxt.y;
                if (i > t)
                {
                    ret.x -= i - t;
                    i = t;
                    continue;
                }
                if (vis[nxt.bh][drct])
                {
                    st = vis[nxt.bh][drct];
                    ed = vis[now][last_drct];
                    break;
                }
                if (nxt.type == 0)
                {
                    drct = 0;
                }
                else
                {
                    drct = 1;
                }
                last_drct = 3;
                now = nxt.bh;
                ans[++num] = ret;
                len[num] = i;
                fx[num] = drct;
                vis[now][last_drct] = num;
            }
            else
            {
                ret.x = ans[num].x + (t - i);
                ret.y = ans[num].y;
                return ret;
            }
        }
    }
    if (i >= t)
    {
        return ret;
    }
    long long xx = (t - len[st]) % (i - len[st]) + len[st];
    for (i = st; i < ed; ++i)
    {
        if (len[i] <= xx && len[i + 1] > xx)
        {
            ret = ans[i];
            if (fx[i] == 0)
            {
                ret.y += xx - len[i];
            }
            else if (fx[i] == 1)
            {
                ret.y -= xx - len[i];
            }
            else if (fx[i] == 2)
            {
                ret.x -= xx - len[i];
            }
            else if (fx[i] == 3)
            {
                ret.x += xx - len[i];
            }
            return ret;
        }
    }
    ret = ans[ed];
    if (fx[ed] == 0)
    {
        ret.y += xx - len[ed];
    }
    else if (fx[ed] == 1)
    {
        ret.y -= xx - len[ed];
    }
    else if (fx[ed] == 2)
    {
        ret.x -= xx - len[ed];
    }
    else if (fx[ed] == 3)
    {
        ret.x += xx - len[ed];
    }
    return ret;
}
void Swap(Node &a, Node &b)
{
    Node tmp = a;
    a = b;
    b = tmp;
    return;
}
