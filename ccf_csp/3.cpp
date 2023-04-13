#include <iostream>
#include <set>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  unsigned int n;

  while (cin >> n) {
    if (!n) {
      break;
    }

    string name;
    set<string> names;
    unsigned int count = 2 * n - 1;
    while (count--) {
      cin >> name;
      if (names.find(name) != names.end()) {
        names.erase(name);
      } else {
        names.insert(name);
      }
    }
    cout << *names.begin() << endl;
  }

  return 0;
}
