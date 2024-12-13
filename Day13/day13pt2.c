#include <stdio.h>

int main(int argc, char** argv) {
    FILE* f = fopen("input.txt", "r");
    size_t score = 0;
    while(!feof(f)) {
        long ax, ay, bx, by, px, py;
        fscanf(f, "Button A: X+%li, Y+%li\n"
                  "Button B: X+%li, Y+%li\n"
                  "Prize: X=%li, Y=%li\n\n", &ax, &ay, &bx, &by, &px, &py);
        px += 10000000000000L;
        py += 10000000000000L;
        /**
         * A*ax + B*bx = px
         * A*ay + B*by = py
         * 
         * [A][ax bx] = [px]
         * [B][ay by] = [py]
         * 
         * Eliminate:
         * [ax bx px]
         * [ay by py]
         * 
         * [1 bx/ax px/ax]
         * [ay by   py   ]
         * 
         * [1 bx/ax         px/ax      ]
         * [0 by-ay*bx/ax   py-ay*px/ax]
         * 
         * [1 bx/ax         px/ax      ]
         * [0 ax*by-ay*bx   ax*py-ay*px]
         * 
         * [1 bx/ax   px/ax                        ]
         * [0 1       (ax*py-ay*px) / (ax*by-ay*bx)]
         * 
         * [1 0 px/ax - bx/ax * (ax*py-ay*px) / (ax*by-ay*bx)]
         * [0 1 (ax*py-ay*px) / (ax*by-ay*bx)                ]
         * 
         * Simplifying the A result:
         * px/ax - bx/ax * (ax*py-ay*px) / (ax*by-ay*bx)
         * px/ax - (bx*py- bx*ay*px/ax) / (ax*by-ay*bx)
         * px/ax - (bx*py - bx*ay*px/ax) / (ax*by-ay*bx)
         * (px/ax*(ax*by-ay*bx) - bx*py + bx*ay*px/ax) / (ax*by-ay*bx)
         * (px*by - px*ay*bx/ax - bx*py + bx*ay*px/ax) / (ax*by-ay*bx)
         * (px*by-bx*py) / (ax*by-ay*bx)
         * 
         * Final closed form:
         * A = (px*by-bx*py) / (ax*by-ay*bx)
         * B = (ax*py-ay*px) / (ax*by-ay*bx)
         */
        long Anumer = (px*by-bx*py);
        long Bnumer = (ax*py-ay*px);
        long denom = (ax*by-ay*bx);

        if(Anumer % denom == 0 && Bnumer % denom == 0) {
            score += 3*Anumer/denom + Bnumer/denom;
        }
    }
    printf("%lu\n", score);
}