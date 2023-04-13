#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {
  unsigned int N;
  while (scanf("%d", &N)) {
    if (!N) {
      break;
    }

    unsigned int i;
    double array[N], average = 0.0;
    for (i = 0; i < N; ++i) {
      scanf("%lf", &array[i]);
      average += array[i];
    } 
    average /= N;
    
    double square_sum = 0.0;
    for (i = 0; i < N; ++i) {
      array[i] = (array[i] - average) * (array[i] - average);
      square_sum += array[i];
    }
    printf("%d\n", (int)floor(square_sum / N));
  }
  return 0;
}
