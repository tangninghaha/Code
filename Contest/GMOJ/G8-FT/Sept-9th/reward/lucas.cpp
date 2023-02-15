#include <cstdio>

/* Constant */
const int MAXP = 1e5 + 5;

/* Declaration */
int main();
int C(int, int, const int);
void FileIO();

/* Variable */
int jc[MAXP];

/* Definition */
void FileIO()
{
    freopen("reward.in", "r", stdin);
    freopen("reward.out", "w", stdout);
    return;
}
int C(int n, int m, const int mod)
{
    return jc[n] * nyjc[m];
}
