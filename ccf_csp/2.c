#include <stdio.h>

int main(int argc, char* argv[]) {
    unsigned int n = 0;
    while (scanf("%d", &n)) {
        if (n == 0) {
            break;
        }

        unsigned int i, value = 0;
        for (i = 1; i <= n / 2; ++i) {
            if (n % i == 0) {
                value += i;
            }
        }
        printf("%d\n", value);
    }
    return 0;
}
