//暴力法子字符串查找
//如果找到，返回位置
//如果没找到，返回文本字符串长度

#include <iostream>
#include <string>
using namespace std;

size_t ForceSearch(string pat, string txt) {
  auto M = pat.length();
  auto N = txt.length();
  for (size_t i = 0; i <= N - M; ++i) {
    size_t j;
    for (j = 0; j < M; ++j)
      if (txt[i + j] != pat[j]) break;
    if (j == M) return i;
  }
  return N;
}

int main() {
  string a("I like my cup.");
  string b("cup");
  cout << ForceSearch(b, a) << endl;
  return 0;
}
