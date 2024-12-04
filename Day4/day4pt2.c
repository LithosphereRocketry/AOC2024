#include "../utils.h"
#include <stdbool.h>

size_t char_row = 0;
size_t rows = 0;
char* fdata = NULL;

char at(size_t x, size_t y) {
    if(char_row && fdata) {
        return fdata[y*(char_row+1) + x];
    }
    return -1;
}

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    fdata = fread_dup(f);
    char_row = strchr(fdata, '\n') - fdata;
    rows = strlen(fdata)/(char_row+1);

    size_t score = 0;
    for(int y = 1; y < rows-1; y++) {
        for(int x = 1; x < char_row-1; x++) {
            if(at(x, y) == 'A'
            && (
                at(x+1, y+1) == 'M' && at(x-1, y-1) == 'S'
             || at(x+1, y+1) == 'S' && at(x-1, y-1) == 'M'
            ) && (
                at(x-1, y+1) == 'M' && at(x+1, y-1) == 'S'
             || at(x-1, y+1) == 'S' && at(x+1, y-1) == 'M'
            )) {
                score++;
            }
        }
    }
    printf("%lu\n", score);

    free(fdata);
}