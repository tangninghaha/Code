#include <stdio.h>
#include <cstring>

const int MAXN = 1e3 + 1, MAXM = 1e3 + 1, SIZE = MAXN * MAXN;

struct Vector
{
    Vector();
    int a[SIZE];
    int head[MAXN];
    int nxt[SIZE];
    int size[MAXN];
    int tot;
    int GetNum(int x, int y);
    void push(int x, int num);
};
Vector dis;
int s[MAXN];

int main()
{
    int n, t;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &s[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= s[i]; ++j)
        {
            scanf("%d", &t);
            dis.push(i, t);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= s[i]; ++j)
        {
            printf("%d ", dis.GetNum(i, j));
        }
        printf("\n");
    }
    return 0;
}


Vector::Vector()
{
    tot = 0;
    memset(size, 0, sizeof(size));
}
int Vector::GetNum(int x, int y)
{
    int k = size[x];
    for (int i = head[x]; i; i = nxt[i])
    {
        if (k == y)
        {
            return a[i];
        }
        --k;
    }
    return -1;

}
void Vector::push(int x, int num)
{
    ++tot;
    nxt[tot] = head[x];
    a[tot] = num;
    ++size[x];
    head[x] = tot;
}
