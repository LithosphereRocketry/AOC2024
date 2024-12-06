#include <stdio.h>
#include <stdbool.h>
#include "../utils.h"

char* data;
size_t w, h;
size_t x, y;

enum direction {
    NORTH = 0b0001, EAST = 0b0010, SOUTH = 0b0100, WEST = 0b1000
};

char at(char* buf, size_t x, size_t y) {
    if(x < 0 || x >= w || y < 0 || y >= h) return '!';
    return buf[y*(w+1) + x];
}

void put(char* buf, size_t x, size_t y, char v) {
    buf[y*(w+1) + x] = v;
}

size_t score = 0;

void walk(char* grid, size_t x, size_t y, enum direction dir, bool canPlace) {
    size_t nx, ny;
    switch(dir) {
        case NORTH: nx = x; ny = y-1; break;
        case EAST: nx = x+1; ny = y; break;
        case SOUTH: nx = x; ny = y+1; break;
        case WEST: nx = x-1; ny = y; break;
    }
    if(at(grid, nx, ny) == 0x30 && canPlace) {
        char* specgrid = strdup(grid);
        put(specgrid, nx, ny, '$');
        walk(specgrid, x, y, dir, false);
        free(specgrid);
    }

    if(at(grid, nx, ny) == '#' || at(grid, nx, ny) == '$') {
        walk(grid, x, y, (dir << 1 | dir >> 3) & 0xF, canPlace);
    } else if(at(grid, x, y) != '!') {
        if(at(grid, x, y) & dir & 0x0F) {
            score++;
        } else {
            put(grid, x, y, at(grid, x, y) | dir);
            walk(grid, nx, ny, dir, canPlace);
        }
    }
}

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    data = fread_dup(f);
    w = strchr(data, '\n') - data;
    h = strlen(data) / (w + 1);

    for(size_t i = 0; i < h; i++) {
        for(size_t j = 0; j < w; j++) {
            if(at(data, j, i) == '^') {
                x = j; y = i;
                put(data, j, i, 0x30);
            }
            if(at(data, j, i) == '.') {
                put(data, j, i, 0x30);
            }
        }
    }

    walk(data, x, y, NORTH, true);
    printf("%lu\n", score);
}