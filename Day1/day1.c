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

    size_t dist = 0;
    for(size_t i = 0; i < rows; i++) {
        dist += labs(col1[i] - col2[i]);
    }
    printf("%ld\n", dist);

    free(col1);
    free(col2);
}