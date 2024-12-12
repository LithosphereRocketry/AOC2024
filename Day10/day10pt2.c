#include "../utils.h"
#include <stdbool.h>

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    char* data = fread_dup(f);

    size_t len = strlen(data);
    size_t width = strchr(data, '\n') - data;

    size_t score = 0;
    size_t* reachable = malloc(len*sizeof(size_t));
    for(size_t i = 0; i < len; i++) {
        if(data[i] == '0') {
            memset(reachable, 0, len*sizeof(size_t));
            reachable[i] = 1;
            for(size_t h = 1; h < 10; h++) {
                for(size_t j = 0; j < len; j++) {
                    if(data[j] == '0'+h) {
                        if(j > 0 && data[j-1] == '0'+h-1) {
                            reachable[j] += reachable[j-1];
                        }
                        if(j >= width+1 && data[j-width-1] == '0'+h-1) {
                            reachable[j] += reachable[j-width-1];
                        }
                        if(j < len-1 && data[j+1] == '0'+h-1) {
                            reachable[j] += reachable[j+1];
                        }
                        if(j < len-width-1 && data[j+width+1] == '0'+h-1) {
                            reachable[j] += reachable[j+width+1];
                        }
                    }
                }
            }
            for(size_t j = 0; j < len; j++) {
                if(data[j] == '9') {
                    score += reachable[j];
                }
            }
        }
    }
    printf("%lu\n", score);
    free(reachable);
    free(data);
}