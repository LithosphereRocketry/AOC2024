#include "../utils.h"

void putnode(char* field, size_t width, size_t height, size_t x, size_t y) {
    if(x >= 0 && y >= 0 && x < width && y < height) {
        field[y*(width+1) + x] = 1;
    }
}

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    char* data = fread_dup(f);
    
    size_t len = strlen(data);
    char* anodes = malloc(len);
    memset(anodes, 0, len);
    size_t width = strchr(data, '\n') - data;
    printf("%lu %lu\n", len, width);

    for(size_t i = 0; i < len; i++) {
        for(size_t j = i+1; j < len; j++) {
            if(data[i] != '\n' && data[i] != '.' && data[i] == data[j]) {
                size_t ix = (i % (width+1));
                size_t iy = (i / (width+1));
                size_t jx = (j % (width+1));
                size_t jy = (j / (width+1));
                putnode(anodes, width, len/(width+1), (long) ix*2 - (long) jx,
                                                      (long) iy*2 - (long) jy);
                putnode(anodes, width, len/(width+1), (long) jx*2 - (long) ix,
                                                      (long) jy*2 - (long) iy);
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