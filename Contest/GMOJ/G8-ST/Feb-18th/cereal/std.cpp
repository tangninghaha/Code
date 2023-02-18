#include <cstdio>

/* Constant */
const int N = 1e5;
const int INF = 1 << 29;

/* Class */
class Graph
{
  public:
    int head[N * 2 + 1];
    int nxt[N * 2 +1];
    int to[N * 2 + 1];
    int dis[N * 2 + 1];
    int tot;
    Graph()
    {
      tot = 1;
    }
    void Add(int _u, int _v, int _w)
    {
      ++tot;
      nxt[tot] = head[_u];
      to[tot] = _v;
      dis[tot] = _w;
      head[_u] = tot;
      return;
    }
};

/* Declaration */

/* Variable */
Graph G;

/* Definition */
int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  int f, s;
  for (int i = 1; i <= n; ++i)
    G.Add(1, i + 1, INF), G.Add(i + 1, 1, 0);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d%d", &f, &s);
    G.Add(i + 1, f + n + 1, 1);
    G.Add(f + n +1, i + 1, 1);
  }
}
