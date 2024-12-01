#include <stdlib.h>
#include <stdio.h>
#include "../utils.h"


int cmp_long(const void* pp, const void* pq) {
    long p = *(long*) pp;
    long q = *(long*) pq;
    if(p < q) return -1;
    if(p > q) return 1;
    return 0;
}

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    size_t sz = fsize(f);
    char* fdata = malloc(sz+1);
    fread(fdata, 1, sz, f);
    fdata[sz] = '\0';

    size_t rows = memcount('\n', fdata, sz);
    
    long* col1 = malloc(rows*sizeof(long));
    long* col2 = malloc(rows*sizeof(long));

    char* dataptr = fdata;
    for(size_t i = 0; i < rows; i++) {
        int nchars;
        sscanf(dataptr, "%ld %ld\n%n", col1+i, col2+i, &nchars);
        dataptr += nchars;
    }

    qsort(col1, rows, sizeof(long), cmp_long);    
    qsort(col2, rows, sizeof(long), cmp_long);

    size_t c2marker = 0;
    long score = 0;
    for(size_t i = 0; i < rows; i++) {
        long n_right = 0;
        long n_left = 1;
        while(c2marker < rows && col2[c2marker] < col1[i]) c2marker++;
        while(c2marker < rows && col2[c2marker] == col1[i]) {
            n_right++;
            c2marker++;
        }
        while(i+1 < rows && col1[i] == col1[i+1]) {
            n_left++;
            i++;
        }
        score += n_left * n_right * col1[i];
    }
    printf("%ld\n", score);

    free(col1);
    free(col2);
}