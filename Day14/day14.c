#include <stdio.h>

long time = 100;
// long width = 11, height = 7;
long width = 101, height = 103;

int main(int argc, char** argv) {
    size_t centerx = (width-1)/2;
    size_t centery = (height-1)/2;
    FILE* f = fopen("input.txt", "r");

    size_t count_tl = 0, count_tr = 0, count_bl = 0, count_br = 0;
    while(!feof(f)) {
        long x, y, vx, vy;
        fscanf(f, "p=%li,%li v=%li,%li\n", &x, &y, &vx, &vy);
        long fx = (x + (vx + width)*time) % width;
        long fy = (y + (vy + height)*time) % height;
        if(fx < centerx && fy < centery) count_tl++;
        if(fx < centerx && fy > centery) count_bl++;
        if(fx > centerx && fy < centery) count_tr++;
        if(fx > centerx && fy > centery) count_br++;
    }
    size_t score = count_bl*count_br*count_tl*count_tr;
    printf("%lu\n", score);
}