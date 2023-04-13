#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  unsigned int n = 0, i, j;
  while (scanf("%d", &n)) {
    if (!n) {
      break;
    }

    char string_array[2 * n - 1][21];
    for (i = 0; i < 2 * n - 1; ++i) {
      scanf("%s", string_array[i]);
    }
    unsigned int flag[2 * n - 1];
    memset((void*)flag, 0, sizeof(unsigned int) * (2 * n - 1));

    // process
    for (i = 0; i < 2 * n - 1; ++i) {
      if (flag[i]) {
        continue;
      }
      for (j = i + 1; j < 2 * n - 1; ++j) {
        if (flag[j] == 0 && strcmp(string_array[i], string_array[j]) == 0) {
          flag[i] = flag[j] = 1;
          break;
        }
      }
    }

    // output
    for (i = 0; i < 2 * n - 1; ++i) {
      if (flag[i] == 0) {
        printf("%s\n", string_array[i]);
        break;
      }
    }
  }
  return 0;
}
