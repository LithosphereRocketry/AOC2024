#include "../utils.h"

size_t w, h;

char at(char* buf, size_t x, size_t y) {
    // Negative indexes will wrap around
    if(x >= w || y >= h) return '!';
    return buf[y*(w+1) + x];
}

void put(char* buf, size_t x, size_t y, char v) {
    buf[y*(w+1) + x] = v;
}

struct region {
    size_t area;
    size_t perimeter;
};

struct region flood_perimeter(char* buf, size_t x, size_t y, char c) {
    struct region total = {1, 0};
    put(buf, x, y, ' ');
    if(at(buf, x+1, y) == c) {
        struct region r = flood_perimeter(buf, x+1, y, c);
        total.area += r.area;
        total.perimeter += r.perimeter;
    } else if(at(buf, x+1, y) != ' ') {
        total.perimeter ++;
    }
    if(at(buf, x-1, y) == c) {
        struct region r = flood_perimeter(buf, x-1, y, c);
        total.area += r.area;
        total.perimeter += r.perimeter;
    } else if(at(buf, x-1, y) != ' ') {
        total.perimeter ++;
    }

    if(at(buf, x, y+1) == c) {
        struct region r = flood_perimeter(buf, x, y+1, c);
        total.area += r.area;
        total.perimeter += r.perimeter;
    } else if(at(buf, x, y+1) != ' ') {
        total.perimeter ++;
    }
    if(at(buf, x, y-1) == c) {
        struct region r = flood_perimeter(buf, x, y-1, c);
        total.area += r.area;
        total.perimeter += r.perimeter;
    } else if(at(buf, x, y-1) != ' ') {
        total.perimeter ++;
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
    while(y < h) {
        struct region r = flood_perimeter(data, x, y, at(data, x, y));
        for(char* p = data; *p; p++) {
            if(*p == ' ') *p = '!';
        }
        score += r.area*r.perimeter;

        while(y < h && at(data, x, y) == '!') {
            x++;
            if(x >= w) {
                x = 0;
                y++;
            }
        }
    }
    printf("%lu\n", score);
    free(data);
}