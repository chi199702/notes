#include <stdio.h>

int main(int argc, char* argv[]) {
  unsigned int t, a, b, result = 0;
  scanf("%d", &t);

  while (t--) {
    scanf("%d%d", &a, &b);
    unsigned int result1 = a / 4 - a / 100 + a / 400;
    unsigned int result2 = b / 4 - b / 100 + b / 400;
    result = result2 - result1 + ((a % 400 == 0 || (a % 100 != 0 && a % 4 == 0)) ? 1 : 0);
    printf("%d\n", result);
    result = 0;
  }
  return 0;
}
