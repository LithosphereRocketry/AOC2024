#include "../utils.h"

struct file_block {
    size_t id;
    size_t size;
    size_t space;
};

void printfs(struct file_block* fs, size_t len) {
    for(size_t i = 0; i < len; i++) {
        for(size_t j = 0; j < fs[i].size; j++) putchar(fs[i].id + '0');
        for(size_t j = 0; j < fs[i].space; j++) putchar('.');
    }
}


int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    char* data = fread_dup(f);
    size_t len = (strlen(data) + 1)/2; // 2 bytes per entry

    struct file_block* fs = malloc(len * sizeof(struct file_block));

    for(size_t i = 0; i < len; i++) {
        fs[i].id = i;
        fs[i].size = data[2*i] - '0';
        if(i == len-1) {
            fs[i].space = 0; // no trailing record size
        } else {
            fs[i].space = data[2*i + 1] - '0';        
        }
    }

    size_t first_cand = 0;
    for(size_t i = len-1; i > 0; i--) {
        size_t goodInd = -1;
        while(fs[first_cand].space == 0) first_cand++;
        for(size_t j = first_cand; j < i; j++) {
            if(fs[j].space >= fs[i].size) {
                goodInd = j;
                break;
            }
        }
        if(goodInd != -1) {
            fs[i-1].space += fs[i].size + fs[i].space;
            fs[i].space = fs[goodInd].space - fs[i].size;
            fs[goodInd].space = 0;
            struct file_block tmp = fs[i];
            for(long j = i-1; j > goodInd; j--) {
                fs[j+1] = fs[j];
            }
            fs[goodInd+1] = tmp;
            i++;
            // we shifted the array over, so i now points to something different
        }
    }

    size_t blocks = 0;
    size_t score = 0;
    for(size_t i = 0; i < len; i++) {
        score += fs[i].id*( // unnecessary closed form optimization
            blocks*fs[i].size // rectangular part
          + fs[i].size*(fs[i].size - 1) / 2 // triangular part
        );
        blocks += fs[i].size + fs[i].space;
    }

    printf("%lu\n", score);

    free(fs);
    free(data);
}