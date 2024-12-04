#include "../utils.h"
#include <stdbool.h>

const char* word = "XMAS";

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
    for(int y = 0; y < rows; y++) {
        for(int x = 0; x < char_row; x++) {
            if(x + strlen(word) <= char_row) {
                bool hit = true;
                for(int i = 0; i < strlen(word); i++) {
                    if(at(x+i, y) != word[i]) hit = false;
                }
                if(hit) score++; 
            }
            if(x >= strlen(word) - 1) {
                bool hit = true;
                for(int i = 0; i < strlen(word); i++) {
                    if(at(x-i, y) != word[i]) hit = false;
                }
                if(hit) score++; 
            }
            if(y + strlen(word) <= rows) {
                bool hit = true;
                for(int i = 0; i < strlen(word); i++) {
                    if(at(x, y+i) != word[i]) hit = false;
                }
                if(hit) score++; 
            }
            if(y >= strlen(word) - 1) {
                bool hit = true;
                for(int i = 0; i < strlen(word); i++) {
                    if(at(x, y-i) != word[i]) hit = false;
                }
                if(hit) score++; 
            }

            if(x + strlen(word) <= char_row && y + strlen(word) <= rows) {
                bool hit = true;
                for(int i = 0; i < strlen(word); i++) {
                    if(at(x+i, y+i) != word[i]) hit = false;
                }
                if(hit) score++; 
            }
            if(x >= strlen(word) - 1 && y + strlen(word) <= rows) {
                bool hit = true;
                for(int i = 0; i < strlen(word); i++) {
                    if(at(x-i, y+i) != word[i]) hit = false;
                }
                if(hit) score++; 
            }
            if(x + strlen(word) <= char_row && y >= strlen(word) - 1) {
                bool hit = true;
                for(int i = 0; i < strlen(word); i++) {
                    if(at(x+i, y-i) != word[i]) hit = false;
                }
                if(hit) score++; 
            }
            if(x >= strlen(word) - 1 && y >= strlen(word) - 1) {
                bool hit = true;
                for(int i = 0; i < strlen(word); i++) {
                    if(at(x-i, y-i) != word[i]) hit = false;
                }
                if(hit) score++; 
            }
        }
    }
    printf("%lu\n", score);

    free(fdata);
}