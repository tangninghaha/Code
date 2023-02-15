#include <stdio.h>
const int MAXLEN = 5000005;
char cha[MAXLEN];
int sum_b[MAXLEN], sum_w[MAXLEN];
void FileIO();
int main()
{
    FileIO();
    int t;
    scanf("%d", &t);
    for (int T = 1; T <= t; ++T)
    {
        int n, len = 0;
        int x;
        char c;
        int st, ed;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &x);
            c = getchar();
            while (c != 'B' && c != 'W')
                c = getchar();
            st = len + 1;
            ed = len + x;
            for (int j = st; j <= ed; ++j)
            {
                cha[j] = c;
            }
            len += x;
        }
        for (int i = 1; i <= len; ++i)
        {
            sum_b[i] = sum_b[i - 1] + (cha[i] == 'B');
            sum_w[i] = sum_w[i - 1] + (cha[i] == 'W');
        }
        int n_b_num, n_w_num;
        int nxt_st, nxt_ed;
        bool sovled;
        int cnt, ans = 1;
        for (int l = 1; l <= len; ++l)
        {
            if (len % l)
                continue;
            n_b_num = sum_b[l];
            n_w_num = sum_w[l];
            ed = len / l;
            sovled = true;
            cnt = 0;
            for (int i = 2; i <= ed; ++i)
            {
                if (sovled)
                {
                    ++cnt;
                    nxt_st = (i - 1) * l + 1;
                    sovled = false; 
                }
                nxt_ed = i * l;
                if (n_b_num == 0 || n_w_num == 0)
                {
                    if ((sum_b[nxt_ed] - sum_b[nxt_st - 1]) && !n_b_num)
                    {
                        sovled = false;
                        break;
                    }
                    if ((sum_w[nxt_ed] - sum_w[nxt_st - 1]) && !n_w_num)
                    {
                        sovled = false;
                        break;
                    }
                    sovled = true;
                    continue;
                }
                if (!((sum_b[nxt_ed] - sum_b[nxt_st - 1]) % n_b_num))
                {
                    if (!(sum_b[nxt_ed] - sum_b[nxt_st - 1]))
                    {
                        continue;
                    }
                    if (!((sum_w[nxt_ed] - sum_w[nxt_st - 1]) % n_w_num))
                    {
                        if (!(sum_w[nxt_ed] - sum_w[nxt_st - 1]))
                        {
                            continue;
                        }
                        sovled = true;
                    }
                }
            }
            if (sovled)
            {
                ++cnt;
                ans = cnt > ans ? cnt : ans;
 
            }
       }
        printf("%d\n", ans);
    }
    return 0;
}
void FileIO()
{
    freopen("silly.in", "r", stdin);
    freopen("silly.out", "w", stdout);
    return;
}
