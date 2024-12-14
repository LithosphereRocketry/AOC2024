#include <stdlib.h>
#include <string.h>
#include <stdio.h>

long time = 10000;
// long width = 11, height = 7;
long width = 101, height = 103;

char at(char* buf, size_t x, size_t y) {
    // Negative indexes will wrap around
    if(x >= width || y >= height) return '!';
    return buf[y*(width+1) + x];
}

void put(char* buf, size_t x, size_t y, char v) {
    buf[y*(width+1) + x] = v;
}

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");

    char* map = malloc((width+1)*height + 1);
    for(int i = 0; i < time; i++) {
        memset(map, ' ', (width+1)*height + 1);
        for(size_t i = 0; i < height; i++) {
            put(map, width, i, '\n');
        }
        fseek(f, SEEK_SET, 0);
        while(!feof(f)) {
            long x, y, vx, vy;
            fscanf(f, "p=%li,%li v=%li,%li\n", &x, &y, &vx, &vy);

            long fx = (x + (vx + width)*i) % width;
            long fy = (y + (vy + height)*i) % height;
            put(map, fx, fy, '#');
        }
        double neighbors = 0, count = 0;
        for(size_t sy = 0; sy < height; sy++) {
            for(size_t sx = 0; sx < width; sx++) {
                if(at(map, sx, sy) == '#') {
                    count++;
                    if(at(map, sx,   sy+1) == '#') neighbors++;
                    if(at(map, sx+1, sy+1) == '#') neighbors++;
                    if(at(map, sx+1, sy  ) == '#') neighbors++;
                    if(at(map, sx+1, sy-1) == '#') neighbors++;
                    if(at(map, sx,   sy-1) == '#') neighbors++;
                    if(at(map, sx-1, sy-1) == '#') neighbors++;
                    if(at(map, sx-1, sy  ) == '#') neighbors++;
                    if(at(map, sx-1, sy+1) == '#') neighbors++;
                }
            }
        }
        if(neighbors / count > 1.0) {
            printf("%i\n", i);
            puts(map);
        }
    }
    free(map);
}