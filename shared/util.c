#include "util.h"

unsigned int ws_log16(unsigned int x) {
    unsigned int l = 0;
    while (x >>= 4) ++l; // bitshift right by 4 until x == 0
    return l;
}