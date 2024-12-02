#include <stdbool.h>
#include "../utils.h"

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    char* line;
    size_t score = 0;
    while(strlen(line = fgets_dup(f)) > 0) {
        score++;
        const char* lptr = line;
        bool first = true;
        int dir = 0;
        int last;
        int current;
        int inc;
        while(sscanf(lptr, "%i%n", &current, &inc) == 1) {
            lptr += inc;
            if(first) {
                first = false;
            } else {
                if(dir == 0) {
                    dir = current > last ? 1 : -1;
                } else {
                    int newdir = current > last ? 1 : -1;
                    if(newdir != dir) {
                        score--; 
                        break;
                    }
                }
                if(abs(current - last) < 1 || abs(current - last) > 3) {
                    score--;
                    break;
                }
            }
            last = current;
        }
        free(line);
    }
    printf("%lu\n", score);
}