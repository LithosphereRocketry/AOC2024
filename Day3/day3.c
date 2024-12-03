#include "../utils.h"
#include <ctype.h>

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    char* data = fread_dup(f);

    char* dptr = data;
    size_t score = 0;
    while(*dptr) {
        if(strncmp(dptr, "mul(", 4) == 0) {
            dptr += 4;
            if(!isdigit(*dptr)) continue;
            int i = 0;
            while(isdigit(*dptr)) {
                i *= 10;
                i += (*dptr) - '0';
                dptr++;
            }
            if(*dptr != ',') continue;
            dptr++;
            if(!isdigit(*dptr)) continue;
            int j = 0;
            while(isdigit(*dptr)) {
                j *= 10;
                j += (*dptr) - '0';
                dptr++;
            }
            if(*dptr != ')') continue;
            score += i*j;
        } else {
            dptr++;
        }
    }
    printf("%lu\n", score);

    free(data);
}