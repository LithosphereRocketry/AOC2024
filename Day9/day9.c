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

    size_t total = 0;
    for(size_t i = 0; i < len; i++) {
        total += fs[i].size + fs[i].space;
    }

    int* fs_mem = malloc(total*sizeof(int));
    int* ptr = fs_mem;
    for(size_t i = 0; i < len; i++) {
        for(size_t j = 0; j < fs[i].size; j++) {
            *ptr = fs[i].id;
            ptr++;
        }
        for(size_t j = 0; j < fs[i].space; j++) {
            *ptr = -1;
            ptr++;
        }
    }

    int* next_free = fs_mem;
    for(size_t i = total-1; i > 0; i--) {
        while(*next_free != -1) next_free++;
        if(next_free > fs_mem+i) break;
        *next_free = fs_mem[i];
        fs_mem[i] = -1;
    }

    size_t score = 0;
    for(size_t i = 0; i < total; i++) {
        if(fs_mem[i] != -1) score += fs_mem[i] * i;
    }
    printf("%lu\n", score);

    free(fs_mem);
    free(fs);
    free(data);
}