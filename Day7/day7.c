#include "../utils.h"

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
            for(size_t i = 0; i < 1 << (lnums.len - 1); i++) {
                size_t acc = lnums.contents[0];
                size_t sr = i;
                for(int j = 1; j < lnums.len; j++) {
                    if(sr & 1) {
                        acc *= lnums.contents[j];
                    } else {
                        acc += lnums.contents[j];
                    }
                    sr >>= 1;
                }
                if(acc == total) {
                    score += total;
                    break;
                } else if(acc > total) break;
            }
        }

        il_destroy(&lnums);
        free(line);
    }
    printf("%lu\n", score);
}