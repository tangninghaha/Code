#include <cstdio>

/* Constant */
const int MAXN = 1e6 + 5;
const int MAXM = 5e5 + 5;
const int MAXQ = 2e5 + 5;

/* Declaration */
int main();
void Swap(int&, int&);
void Qsort(int, int, int*);

/* Variable */
char a[MAXN];
int col[MAXM], row[MAXM];
int aa[MAXQ], bb[MAXQ];
int rk[2][MAXM];

/* Definition */
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    char tmp;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            while (tmp < 'a' || tmp > 'z')
                tmp = getchar();
            a[(i - 1) * m + j] = tmp;
            tmp = getchar();
        }
    }
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= n; ++i)
        row[i] = i;
    for (int i = 1; i <= m; ++i)
        col[i] = i;
    long long suma = 0, sumb = 0;
    if (q & 1)
    {
        for (int i = 1; i <= q; ++i)
        {
            scanf("%d%d", &aa[i], &bb[i]);
            if (i & 1)
            {
                suma += aa[i];
                sumb += bb[i];
            }
            else
            {
                suma -= aa[i];
                sumb -= bb[i];
            }
        }
        Qsort(1, q, aa);
        Qsort(1, q, bb);
        int h_num = 0, w_num = 0, k = 0;
        for (int i = 1; i <= n; ++i)
        {
            while (aa[k + 1] < i && k + 1 <= q)
            {
                ++k;
                if (k & 1)
                    ++h_num;
                else
                    --h_num;
            }
            row[i] = suma;
            row[i] -= i;
            row[i] += 1;
            row[i] += h_num * n;
            rk[0][row[i]] = i;
        }
        k = 0;
        for (int i = 1; i <= m; ++i)
        {
            while (bb[k + 1] < i && k + 1 <= q)
            {
                ++k;
                if (k & 1)
                    ++w_num;
                else
                    --w_num;
            }
            col[i] = sumb;
            col[i] -= i;
            col[i] += 1;
            col[i] += w_num * m;
            rk[1][col[i]] = i;
        }
    }
    else
    {
        for (int i = 1; i <= q; ++i)
        {
            scanf("%d%d", &aa[i], &bb[i]);
            if (i & 1)
            {
                suma -= aa[i];
                sumb -= bb[i];
            }
            else
            {
                suma += aa[i];
                sumb += bb[i];
            }
        }
        Qsort(1, q, aa);
        Qsort(1, q, bb);
        int h_num = 0, w_num = 0, k = 0;
        for (int i = 1; i <= n; ++i)
        {
            while (aa[k + 1] < i && k + 1 <= q)
            {
                ++k;
                if (k & 1)
                    --h_num;
                else
                    ++h_num;
            }
            row[i] = suma;
            row[i] += i;
            row[i] += h_num * n;
            rk[0][row[i]] = i;
        }
        k = 0;
        for (int i = 1; i <= m; ++i)
        {
            while (bb[k + 1] < i && k + 1 <= q)
            {
                ++k;
                if (k & 1)
                    --w_num;
                else
                    ++w_num;
            }
            col[i] = sumb;
            col[i] += i;
            col[i] += w_num * m;
            rk[1][col[i]] = i;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            printf("%c", a[(rk[0][i] - 1) * m + rk[1][j]]);
        }
        printf("\n");
    }

}
void Qsort(int l, int r, int* _a)
{
    int i = l, j = r;
    int mid = _a[l + r >> 1];
    while (i <= j)
    {
        while (_a[i] < mid)
            ++i;
        while (_a[j] > mid)
            --j;
        if (i <= j)
        {
            Swap(_a[i], _a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r, _a);
    if (l < j)
        Qsort(l, j, _a);
    return;
}
void Swap(int& _a, int& _b)
{
    int tmp = _a;
    _a = _b;
    _b = tmp;
    return;
}
