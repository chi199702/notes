#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
  char string[5000];
  scanf("%s", string);
  
  unsigned int string_length = strlen(string);
  unsigned int prefix_a[string_length], prefix_b[string_length];
  memset((void*)prefix_a, 0, sizeof(unsigned int) * string_length);
  memset((void*)prefix_b, 0, sizeof(unsigned int) * string_length);

  string[0] == 'a' ? ++prefix_a[0] : ++prefix_b[0];
  unsigned int i, j, tmp, max = 0;
  for (i = 1; i < string_length; ++i) {
    if (string[i] == 'a') {
      prefix_a[i] = prefix_a[i - 1] + 1;
      prefix_b[i] = prefix_b[i - 1];
    }else {
      prefix_a[i] = prefix_a[i - 1];
      prefix_b[i] = prefix_b[i - 1] + 1;
    }
  }
  
  unsigned int left_a, mid_b, right_a;
  for (j = 0; j < string_length; ++j) {
    for (i = j; i < string_length; ++i) {
      left_a = j == 0 ? 0 : prefix_a[j];
      mid_b = prefix_b[i] - (j == 0 ? 0 : prefix_b[j - 1]);
      right_a = prefix_a[string_length - 1] - prefix_a[i];
      tmp = left_a + mid_b + right_a;
      (tmp > max) && (max = tmp);
    }
  }
  printf("%d\n", max);
  return 0;
}
