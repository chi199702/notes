#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

int main(int argc, char* argv[]) {
  unsigned int t;
  string brackets;
  stack<char> stk;
  unordered_set<char> left_bracket = {'<', '(', '{', '['};
  unordered_map<char, char> pair_bracket = {
    {'>', '<'},
    {')', '('},
    {'}', '{'},
    {']', '['}
  };

  cin >> t;
  while (t--) {
    unsigned int flag = 1;
    cin >> brackets;
    for (char c : brackets) {
      if (left_bracket.find(c) != left_bracket.end()) {
        stk.push(c);
      }else {
        if (stk.empty() || stk.top() != pair_bracket[c]) {
          flag = 0;
          printf("No\n");
          break;
        }
        stk.pop();
      } 
    }
    if (flag) {
      printf(stk.empty() ? "Yes\n" : "No\n");
    }
    while (!stk.empty()) {
      stk.pop();
    }
  }
  return 0;
}
