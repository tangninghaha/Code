#include <cstdio>
#include <fstream>

using std::ifstream;
using std::ofstream;

/* Constant */
const int N = 1000;

/* Variable */
int a[N + 1];
int f[N + 1];
int s[N + 1];
bool vis[N + 1];

/* Definition */
int main(int argc, char **argv)
{
  ifstream input;
  input.open(argv[1]);
  int n, m;
  input >> n >> m;
  for (int i = 1; i <= n; ++i)
  {
    input >> f[i] >> s[i];
  }
  input.close();
  ifstream std_out;
  ifstream yourout;
  std_out.open(argv[3]);
  yourout.open(argv[2]);
  int ans1;
  int ans2;
  std_out >> ans1;
  yourout >> ans2;
  std_out.close();
  ifstream full_score_in;
  int full_score = atoi(argv[4]);
  ofstream score;
  score.open(argv[5]);
  ofstream message;
  message.open(argv[6]);
  if (ans1 != ans2)
  {
    score << 0;
    score.close();
    message << "Your Answer Wrong! Your Answer: " << ans2 << "; Standard Answer: " << ans1 << std::endl;
    message.close();
    return 0;
  }
  for (int i = 1; i <= n; ++i)
    yourout >> a[i];
  yourout.close(); 
  int num = 0;
  for (int i = 1; i <= n; ++i)
  {
    if (!vis[f[a[i]]])
      vis[f[a[i]]] = true;
    else if (!vis[s[a[i]]])
      vis[s[a[i]]] = true;
    else
      ++num;
  }
  if (num != ans2)
  {
    score << 0;
    score.close();
    message << "Your Solution Wrong!\n";
    message.close(); 
    return 0;
  }
  message << "Accept\n";
  message.close();
  score << full_score;
  score.close();
  return 0;
}
