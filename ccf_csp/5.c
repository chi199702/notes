#include <stdio.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
  unsigned int t, B;
  char string[10000];
  scanf("%d", &t);
  
  while (t--) {
    scanf("%d%s", &B, string);
    unsigned int i, sum = 0;
    
    for (i = 0; string[i] != '\0'; ++i) {
      if (isdigit(string[i])) {
        sum += string[i] - '0';
      }else {
        sum += string[i] - 'a' + 10;
      }
    }

    for (i = 0; i < B; ++i) {
      if ((sum + i) % (B - 1) == 0) {
        if (10 <= i && i <= 15) {
          printf("%c\n", 'a' - 10 + i);
        }else {
          printf("%d\n", i);
        }
        break;
      }
    }
  }
  return 0;
}
