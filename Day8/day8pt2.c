#include <stdbool.h>
#include "../utils.h"

bool putnode(char* field, size_t width, size_t height, size_t x, size_t y) {
    if(x >= 0 && y >= 0 && x < width && y < height) {
        field[y*(width+1) + x] = 1;
        return true;
    }
    return false;
}

// there are much better gcd algos but I'm lazy
size_t gcd(size_t a, size_t b) {
    size_t result = a>b ? b : a;
    while(result > 1 && (a % result != 0 || b % result != 0)) result--;
    return result;
}

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    char* data = fread_dup(f);
    
    size_t len = strlen(data);
    char* anodes = malloc(len);
    memset(anodes, 0, len);
    size_t width = strchr(data, '\n') - data;

    for(size_t i = 0; i < len; i++) {
        for(size_t j = i+1; j < len; j++) {
            if(data[i] != '\n' && data[i] != '.' && data[i] == data[j]) {
                size_t ix = (i % (width+1));
                size_t iy = (i / (width+1));
                size_t jx = (j % (width+1));
                size_t jy = (j / (width+1));

                long dx = jx - ix;
                long dy = jy - iy;
                size_t divisor = gcd(labs(dx), labs(dy));
                dx /= divisor;
                dy /= divisor;

                for(int k = 0; true; k++) {
                    bool forward = putnode(anodes,  width, len/(width+1), ix - k*dx, iy - k*dy);
                    bool backward = putnode(anodes,  width, len/(width+1), ix + k*dx, iy + k*dy);
                    if(!forward && !backward) break;
                }
            }
        }
    }

    size_t score = 0;
    for(size_t i = 0; i < len; i++) {
        if(anodes[i]) score++;
    }
    free(anodes);
    free(data);
    printf("%lu\n", score);
}