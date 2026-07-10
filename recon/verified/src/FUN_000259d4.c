/* Reconstructed FUN_000259d4 @ 0x259d4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(int,...);
extern int FUN_0008638c(int);
extern void FUN_000864c2(void);
int FUN_000259d4(void){
    *(volatile uint32_t*)(0x20007a48UL+8) = 0x00088a38;
    *(volatile uint16_t*)(0x200023ccUL+4) = 0x53;
    *(volatile uint16_t*)(0x200023ccUL+8) = 0x53;
    *(volatile uint32_t*)(0x200023ccUL+0xc) = 0x1000;
    *(volatile uint32_t*)(0x20007a48UL+0x10) = 0x20007a60;
    *(volatile uint32_t*)(0x20007a48UL+4) = 0x200023cc;
    FUN_000864c2();
    int r = FUN_0008638c(*(volatile uint32_t*)0x200023ccUL);
    uint32_t s = (r==0)? 0x0009f3faUL : 0x0009f418UL;
    DEBUG_PRINT(s);
    int r2v = FUN_0008638c(*(volatile uint32_t*)0x200023ccUL);
    int ret;
    if(r2v==0){
        uint32_t base = *(volatile uint32_t*)0x200023ccUL;
        DEBUG_PRINT(0x0009f433UL, *(volatile uint32_t*)base);
        ret = 0;
    } else {
        DEBUG_PRINT(0x0009f487UL);
        ret = 0x20007a48;
    }
    return ret;
}

