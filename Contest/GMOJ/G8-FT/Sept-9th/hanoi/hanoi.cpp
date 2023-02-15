#include <cstdio>

/* Declaration */
void SovleStd(int source, int target, int spare, int t);
void SovleW(int source, int target, int spare, int t);
int main();
void FileIO();

/* Variable */
int normal[4];
int w[4];
long long step;
long long step_w;
int n, k;

/* Definition */
void SovleStd(int source, int target, int spare, int t)
{
    if (step == k)
        return;
    if (t > 0)
    {
        SovleStd(source, spare, target, t - 1);
        if (step == k)
        {
            return;
        }
        ++step;
        --normal[source];
        ++normal[target];
        if (step == k)
        {
            return;
        }
        SovleStd(spare, target, source, t - 1);
    }
}
void SovleW(int source, int target, int spare, int t)
{
    if (w[1] == normal[1] && w[2] == normal[2] && w[3] == normal[3])
        return;
    if (t > 0)
    {
        SovleW(source, target, spare, t - 1);
        if (w[1] == normal[1] && w[2] == normal[2] && w[3] == normal[3])
            return;
        ++step_w;
        --w[source];
        ++w[spare];
        if (w[1] == normal[1] && w[2] == normal[2] && w[3] == normal[3])
            return;
        SovleW(target, source, spare, t - 1);
        if (w[1] == normal[1] && w[2] == normal[2] && w[3] == normal[3])
            return;
        ++step_w;
        --w[spare];
        ++w[target];
        if (w[1] == normal[1] && w[2] == normal[2] && w[3] == normal[3])
            return;
        SovleW(source, target, spare, t - 1);
    }
}
void FileIO()
{
    freopen("hanoi.in", "r", stdin);
    freopen("hanoi.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    scanf("%d%d", &n, &k);
    normal[1] = n;
    w[1] = n;
    SovleStd(1, 3, 2, n);
    SovleW(1, 3, 2, n);
    printf("%lld", step_w);
    return 0;
}
