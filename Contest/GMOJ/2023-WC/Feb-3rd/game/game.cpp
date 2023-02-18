#include <cstdio>

/* Constant */
const int N = 300;
const int M = 9e4;
const double MX = 1e99;

/* Declaration */
int main();

/* Variable */
long double jc[M + 1];
long double n_xuan[N + 1];
long double m_xuan[M + 1];

/* Definition */
int main()
{
  jc[0] = 1;
//  for (int i = 1; i <= M; ++i)
//    jc[i] = jc[i - 1] * (long double)i;
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  n_xuan[0] = 1;
  for (int i = 1; i <= n; ++i)
    n_xuan[i] = n_xuan[i - 1] * ((long double)(n - i + 1) / i);
  m_xuan[0] = 1;
  for (int i = 1; i <= n * n; ++i)
  {
    if (k < i)
      break;
    m_xuan[i] = m_xuan[i - 1] * ((long double)(k - i + 1) / (m - i + 1));
  }
  long double ans = 0;
  long double sum;
  int t;
  for (int i = 0; i <= n; ++i)
  {
    for (int j = 0; j <= n; ++j)
    {
      t = n * (i + j) - i * j;
      if (k < t)
        continue; 
//      sum = jc[n] / jc[i] / jc[n - i];
//      sum *= jc[n] / jc[j] / jc[n - j];
      sum = n_xuan[i] * n_xuan[j];
//      sum *= jc[k] * jc[m - t] / jc[k - t] / jc[m];
      sum *= m_xuan[t];
      ans += sum;
    }
  }
  if (ans > MX)
    printf("1e99");
  else
    printf("%Lf", ans);
  return 0;
}
