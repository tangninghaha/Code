#include <cstdio>
#include <cstdlib>
#include <fstream>
using std::ifstream;

int main()
{
  ifstream file1;
  int num;
  while (true)
  {
    system("gen > in.txt");
    system("test < in.txt > out.txt");
    file1.open("out.txt");
    file1 >> num;
    if (num)
      break;
    file1.close();
  }
}
