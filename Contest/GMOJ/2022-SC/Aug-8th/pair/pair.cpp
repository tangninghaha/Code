#include <stdio.h>

const int MAXN = 5e5 + 5;
struct HighNum
{
    int a[MAXN];
    int len;
    void Read();
};
bool operator!= (const HighNum &aa, const HighNum &bb);

HighNum l[6], r[6];
HighNum t[6];

void FileIO();
void C1(HighNum &x);
int main();
void P1(HighNum &x);
void Swap(int &a, int &b);

void HighNum::Read()
{
    char cha = getchar();
    while (cha < '0' || cha > '9')
    {
        cha = getchar();
    }
    while (cha >= '0' && cha <= '9')
    {
        a[++len] = cha - '0';
        cha = getchar();
    }
    for (int i = 1; i <= len / 2; ++i)
    {
        Swap(a[i], a[len - i + 1]);
    }
    return;
}
bool operator!= (const HighNum &aa, const HighNum &bb)
{
    if (aa.len != bb.len)
        return true;
    int i = aa.len, j = 1;
    int mid = aa.len / 2;
    while (i > mid && j <= mid)
    {
        if (aa.a[i] != bb.a[i])
            return true;
        if (aa.a[j] != bb.a[j])
            return true;
        --i;
        ++j;
    }
    while (i > mid)
    {
        if (aa.a[i] != bb.a[i])
            return true;
        --i;
    }
    while (j <= mid)
    {
        if (aa.a[j] != bb.a[j])
            return true;
        ++j;
    }
    return false;
}
void FileIO()
{
    freopen("pair.in", "r", stdin);
    freopen("pair.out", "w", stdout);
    return;
}
void C1(HighNum &x)
{
    x.a[1]--;
    int k = 1;
    while (x.a[k] < 0)
    {
        --x.a[k + 1];
        x.a[k] += 10;
        if (k + 1 == x.len && k + 1 == 0)
        {
            --x.len;
        }
    }
    return;
}
int main()
{
    FileIO();
    int n, I;
    scanf("%d%d", &n, &I);
    long long num = 0;
    for (int i = 1; i <= n; ++i)
    {
        num = 0;
        l[i].Read();
        r[i].Read();
        t[i] = l[i];
        C1(t[i]);
        do
        {
            P1(t[i]);
            for (int j = 1; j <= t[i].len; ++j)
            {
                for (int k = 1; k < j; ++k)
                {
                    if (t[i].a[j] > t[i].a[k])
                    {
                        ++num;
                    }
                }
            }
        }
        while (t[i] != r[i]);
        printf("%lld\n", num);
    }
    return 0;
}
void P1(HighNum &x)
{
    x.a[1]++;
    int k = 1;
    while (x.a[k] >= 10)
    {
        if (k == x.len)
        {
            x.len = k + 1;
        }
        x.a[k + 1] += x.a[k] / 10;
        x.a[k] %= 10;
        ++k;
    }
    return;
}
void Swap(int &a, int  &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
