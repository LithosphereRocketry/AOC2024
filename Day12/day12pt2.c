#include <stdbool.h>
#include "../utils.h"

size_t w, h;

enum direction {
    NORTH, EAST, SOUTH, WEST
};

char at(char* buf, size_t x, size_t y) {
    // Negative indexes will wrap around
    if(x >= w || y >= h) return '!';
    return buf[y*(w+1) + x];
}

void put(char* buf, size_t x, size_t y, char v) {
    if(x >= w || y >= h) return;
    buf[y*(w+1) + x] = v;
}

size_t flood(char* buf, size_t x, size_t y, char c) {
    size_t total = 1;
    put(buf, x, y, ' ');
    if(at(buf, x+1, y) == c) {
        total += flood(buf, x+1, y, c);
    }
    if(at(buf, x-1, y) == c) {
        total += flood(buf, x-1, y, c);
    }
    if(at(buf, x, y+1) == c) {
        total += flood(buf, x, y+1, c);
    }
    if(at(buf, x, y-1) == c) {
        total += flood(buf, x, y-1, c);
    }
    return total;
}

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    char* data = fread_dup(f);
    w = strchr(data, '\n') - data;
    h = strlen(data) / (w + 1);
    
    size_t score = 0;
    size_t x = 0, y = 0;
    size_t remtiles = w*h;
    while(remtiles > 0) {
        size_t area = flood(data, x, y, at(data, x, y));
        remtiles -= area;
        
        while(at(data, x+1, y) == ' ') x++;

        char* walked_data = strdup(data);
        size_t sides = 0;
        while(1) {
            size_t wx = x, wy = y;
            enum direction dir = EAST;
            put(walked_data, wx+1, wy, '!');
            do {
                switch(dir) {
                    case NORTH: {
                        if(at(walked_data, wx+1, wy) != ' ') { // outside corner
                            put(walked_data, wx+1, wy, '!');
                            dir = EAST;
                            sides++;
                        } else if(at(walked_data, wx+1, wy-1) != ' ') { // straight
                            put(walked_data, wx+1, wy-1, '!');
                            wx++;
                        } else { // inside corner
                            wx++;
                            wy--;
                            sides++;
                            dir = WEST;
                        }
                    } break;
                    case EAST: {
                        if(at(walked_data, wx, wy+1) != ' ') { // outside corner
                            put(walked_data, wx, wy+1, '!');
                            dir = SOUTH;
                            sides++;
                        } else if(at(walked_data, wx+1, wy+1) != ' ') { // straight
                            put(walked_data,  wx+1, wy+1, '!');
                            wy++;
                        } else { // inside corner
                            wx++;
                            wy++;
                            sides++;
                            dir = NORTH;
                        }
                    } break;
                    case SOUTH: {
                        if(at(walked_data, wx-1, wy) != ' ') { // outside corner
                            put(walked_data, wx-1, wy, '!');
                            dir = WEST;
                            sides++;
                        } else if(at(walked_data, wx-1, wy+1) != ' ') { // straight
                            put(walked_data, wx-1, wy+1, '!');
                            wx--;
                        } else { // inside corner
                            wx--;
                            wy++;
                            sides++;
                            dir = EAST;
                        }
                    } break;
                    case WEST: {
                        if(at(walked_data, wx, wy-1) != ' ') { // outside corner
                            put(walked_data, wx, wy-1, '!');
                            dir = NORTH;
                            sides++;
                        } else if(at(walked_data, wx-1, wy-1) != ' ') { // straight
                            put(walked_data, wx-1, wy-1, '!');
                            wy--;
                        } else { // inside corner
                            wx--;
                            wy--;
                            sides++;
                            dir = SOUTH;
                        }
                    } break;
                }
            } while(wx != x || wy != y || dir != EAST);

            bool done = true;
            for(size_t sy = 0; sy < h; sy++) {
                for(size_t sx = 0; sx < w; sx++) {
                    if(at(walked_data, sx, sy) == ' ') {
                        if(at(walked_data, sx+1, sy) != ' '
                        && at(walked_data, sx+1, sy) != '!') {
                            x = sx;
                            y = sy;
                            done = false;
                            break;
                        }
                    }
                }
            }
            if(done) break;
        }
        free(walked_data);

        for(char* p = data; *p; p++) {
            if(*p == ' ') *p = '.';
        }
        score += area * sides;

        while(remtiles > 0 && (at(data, x, y) == '!' || at(data, x, y) == '.')) {
            x++;
            if(x >= w) {
                x = 0;
                y++;
                if(y >= h) {
                    y = 0;
                }
            }
        }
    }
    printf("%lu\n", score);
    free(data);
}