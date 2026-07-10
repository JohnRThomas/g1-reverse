#include "g1_app_symbols.h"
/* named: lc3_ns */
/* Reconstructed lc3_ns @ 0x68e40  (parity: 300/300 trials, PROVEN) */

unsigned lc3_ns(int param_1, int param_2){
    if (param_1 == 0x1d4c){
        if (param_2 == 8000) return 0x3c;
        if (param_2 == 16000) return 0x78;
        if (param_2 == 24000) return 0xb4;
        if (param_2 != 32000){
            if (param_2 == 48000) return 0x168;
            return 0xffffffffu;
        }
    } else {
        if (param_1 != 10000) return 0xffffffffu;
        if (param_2 == 8000) return 0x50;
        if (param_2 == 16000) return 0xa0;
        if (param_2 != 24000){
            if (param_2 == 32000) return 0x140;
            if (param_2 == 48000) return 0x1e0;
            return 0xffffffffu;
        }
    }
    return 0xf0;
}

