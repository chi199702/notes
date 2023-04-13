#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // input
    unsigned int T;
    scanf("%d", &T);
    char string_array[T][1000001]; 
    
    unsigned int i;
    for (i = 0; i < T; ++i) {
        scanf("%s", string_array[i]); 
    }
   
    // process
    int point_index = -1;
    unsigned int index, c;
    unsigned int left_value, right_value;
    for (i = 0; i < T; ++i) {
        left_value = 0;
        right_value = 0;

        // find point index
        char* point_pointer = strchr(string_array[i], '^');
        point_index = point_pointer - string_array[i];

        for (index = 0; (c = string_array[i][index]) != '\0'; ++index) {
            if (isdigit(c)) {
                if (index < point_index) {
                    left_value += (c - '0') * (point_index - index);
                }else {
                    right_value += (c - '0') * (index - point_index);
                }
            }
        }     

        // output
        if (left_value > right_value) {
            printf("left\n");
        }else if (left_value < right_value) {
            printf("right\n");
        }else {
            printf("balance\n");
        }
    }
    
    return 0;
}
