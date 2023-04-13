#include <iostream>
#include <algorithm>

using namespace std;

struct People {
  int num;
  int s;
  int v;
};

bool cmp(const People& lhs, const People& rhs) {
  return lhs.s < rhs.s;
}

People peoples[10000500];

int main(int argc, char* argv[]) {
  int N, K, i, mid;
  cin >> N >> K;
   
  for (i = 0; i < N; ++i) {
    cin >> peoples[i].s;
    peoples[i].num = i + 1;
  } 
  for (i = 0; i < N; ++i) {
    cin >> peoples[i].v;
  } 
  sort(peoples, peoples + N, cmp);

  int safe = 0, right_minv = 10000001, left_maxv = -1;
  for (mid = 0; mid < N; ++mid) {
    if (peoples[mid].v > left_maxv) {
      left_maxv = peoples[mid].v;
    }
    if (peoples[mid].num == K) {
      break;
    }
  } 

  for (i = mid; i < N; ++i) {
    if (peoples[i].s > peoples[mid].s && peoples[i].v >= left_maxv) {
      ++safe;
    }
    if (peoples[i].v < right_minv) {
      right_minv = peoples[i].v;
    }
  }

  for (i = 0; i < mid; ++i) {
    if (peoples[i].s < peoples[mid].s && peoples[i].v <= right_minv) {
      ++safe;
    }
  }

  cout << N - safe << endl;
  return 0;
}
