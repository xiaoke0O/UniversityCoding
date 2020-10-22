/*字符串反转*/

/*讨巧的办法
#include <deque>
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::deque;
using std::string;
int main() {
  string input;
  deque<string> word;
  while (cin >> input) word.push_front(input);

for (decltype(word.size()) index = 0; index < word.size(); ++index) {
    cout << word[index];
  if (index != word.size() - 1) cout << ' ';
  
}
  return 0;
}
*/
/*正规方法*/
#include <iostream>
#include <algorithm>
using namespace std;

void Reverse(string::iterator b, string::iterator e)
{
    while (b < e)
        swap(*b++, *e--);
}

void ReverseString(string &demo)
{
    if (demo.empty())
        return;

    auto sBegin = demo.begin();
    auto sEnd = demo.end() - 1;
    Reverse(sBegin, sEnd);
    sBegin = sEnd = demo.begin();
    while (*sBegin != '\0')
    {
        if (*sBegin == ' ')
        {
            sBegin++;
            sEnd++;
        }
        else if (*sEnd == ' ' || *sEnd == '\0')
        {
            Reverse(sBegin, --sEnd);
            sBegin = ++sEnd;
        }
        else
            sEnd++;
    }
}
int main()
{
    string testString = "hello mei tuan";
    ReverseString(testString);
    cout << testString << endl;
    return 0;
}

