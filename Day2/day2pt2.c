#include <stdbool.h>
#include "../utils.h"

bool eval(int* nums, size_t len) {
    int dir = 0;
    for(int i = 0; i < len-1; i++) {
        if(abs(nums[i+1] - nums[i]) < 1 || abs(nums[i+1] - nums[i]) > 3) return false;
        if(dir != 0) {
            int newdir = nums[i+1] > nums[i] ? 1 : -1;
            if(newdir != dir) return false;
        }
        dir = nums[i+1] > nums[i] ? 1 : -1;
    }
    return true;
}

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    char* line;
    size_t score = 0;
    while(strlen(line = fgets_dup(f)) > 0) {
        const char* lptr = line;
        int current;
        int inc;
        size_t rowct = 0;
        while(sscanf(lptr, "%i%n", &current, &inc) == 1) {
            lptr += inc;
            rowct ++;
        }
        int* nums = malloc(rowct*sizeof(int));
        lptr = line;
        int i = 0;
        bool first = true;
        while(sscanf(lptr, "%i%n", &current, &inc) == 1) {
            lptr += inc;
            nums[i] = current;
            i++;            
        }
        
        if(eval(nums, rowct)) {
            score++;
        } else {
            int j = 0;
            int* subset = malloc((rowct-1)*sizeof(int));    
            for(int i = 0; i < rowct; i++) {
                int x = 0;
                for(int j = 0; j < rowct; j++) {
                    if(j != i) {
                        subset[x] = nums[j];
                        x++;
                    }
                }
                if(eval(subset, rowct-1)) {
                    score++;
                    break;
                }
            }
            free(subset);
        }

        free(nums);
        free(line);
    }
    printf("%lu\n", score);
}