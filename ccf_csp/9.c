// 0
// 80
// 201
// 300
// 1170
// 1420

#include <stdio.h>

int main(int argc, char* argv[]) {
  unsigned int n, s;
  scanf("%d%d", &n, &s);
  unsigned int i, h, m, array[n];
  
  for (i = 0; i < n; ++i) {
    scanf("%d%d", &h, &m);
    array[i] = h * 60 + m;
  }
  
  unsigned int answer;
  if (s < array[0]) {
    if ((array[n - 1] + 1 + s) > 1440) {
      if ((array[n - 1] + 1 + s) % 1440 + s < array[0]) {
        answer = (array[n - 1] + 1 + s) % 1440;
        printf("%d %d\n", answer / 60, answer - answer / 60 * 60);
        return 0;
      }
    }else {
      printf("%d %d\n", 0, 0);
      return 0;
    }
  }
  for (i = 0; i < n - 1; ++i) {
    if (array[i] + 1 + 2 * s < array[i + 1]) {
      answer = array[i] + 1 + s;
      printf("%d %d\n", answer / 60, answer - answer / 60 * 60);
      return 0;
    }
  } 
  answer = array[i] + 1 + s;
  printf("%d %d\n", answer / 60, answer - answer / 60 * 60);
  return 0;
}
