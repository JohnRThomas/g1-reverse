/* Reconstructed FUN_0004e484 @ 0x4e484  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef struct { unsigned int a; unsigned int b; } S;
extern void FUN_0004e474(void);

void FUN_0004e484(void)
{
    volatile S *p1 = (volatile S *)0x2000a10cUL;
    p1->a = 0;
    p1->b = 0;
    FUN_0004e474();
}

