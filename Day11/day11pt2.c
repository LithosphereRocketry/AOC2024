#include "../utils.h"

size_t ndigits(size_t n) {
    size_t count = 0;
    while(n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

long powli(long b, long e) {
    long result = 1;
    for(long i = 0; i < e; i++) result *= b;
    return result;
}

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    
    longList list_a, list_b;
    ll_init(&list_a);
    ll_init(&list_b);

    longList* from = &list_a;
    longList* to = &list_b;

    long val;
    while(fscanf(f, "%lu", &val) == 1) {
        ll_append(from, val);
    }

    for(size_t round = 0; round < 75; round++) {
        printf("%lu\n", round);
        ll_reserve(to, from->len);
        for(size_t i = 0; i < from->len; i++) {
            long nd, val = from->contents[i];
            if(val == 0) {
                ll_append(to, 1);
            } else if((nd = ndigits(val)) % 2 == 0) {
                long shifter = powli(10, nd/2);
                ll_append(to, val / shifter);
                ll_append(to, val % shifter);
            } else {
                ll_append(to, val*2024L);
            }
        }
        ll_destroy(from);
        ll_init(from);

        longList* tmp = from;
        from = to;
        to = tmp;
    }
    printf("%lu\n", from->len);
    ll_destroy(from);
}