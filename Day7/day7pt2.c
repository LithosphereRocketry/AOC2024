#include "../utils.h"

int ndigits(int n) {
    int count = 0;
    while(n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

size_t powz(size_t b, size_t e) {
    size_t result = 1;
    for(size_t i = 0; i < e; i++) result *= b;
    return result;
}

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    size_t score = 0;
    while(!feof(f)) {
        size_t total;
        fscanf(f, "%lu: ", &total);
        char* line = fgets_dup(f);

        char* lptr = line;
        int el, inc;
        intList lnums;
        il_init(&lnums);
        while(sscanf(lptr, "%i%n", &el, &inc) == 1) {
            il_append(&lnums, el);
            lptr += inc;
        }
        if(lnums.len > 0) {
            for(size_t i = 0; i < powz(3, lnums.len-1); i++) {
                size_t acc = lnums.contents[0];
                size_t sr = i;
                for(int j = 1; j < lnums.len; j++) {
                    size_t rhs = lnums.contents[j];
                    switch(sr % 3) {
                        case 0: acc += rhs; break;
                        case 1: acc *= rhs; break;
                        case 2:
                            acc *= powz(10, ndigits(rhs));
                            acc += rhs;
                            break;
                    }
                    sr /= 3;
                    if(acc > total) break;
                }
                if(acc == total) {
                    score += total;
                    break;
                }
            }
        }

        il_destroy(&lnums);
        free(line);
    }
    printf("%lu\n", score);
}