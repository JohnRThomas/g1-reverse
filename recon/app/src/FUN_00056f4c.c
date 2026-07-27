/* Reconstructed FUN_00056f4c @ 0x56f4c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0007e2fa(unsigned long, ...);
extern uint64_t FUN_0007e2ec(uint32_t,uint32_t);
extern uint64_t FUN_0008148a(void);

uint32_t FUN_00056f4c(int param_1, uint8_t *param_2v){
    volatile uint8_t *p2 = param_2v;
    volatile uint8_t *p1 = (volatile uint8_t*)param_1;
    volatile uint8_t *pb;
    volatile uint8_t *pm;
    p2[0] = p1[2];
    p2[1] = p1[3];
    p2[2] = p1[8];
    uint32_t uVar5 = p1[0xd];
    if (uVar5 > 8){
        FUN_0007e2fa(0x00099cbd,0x000f7a30,0x000f3a5d,0x9b0);
        FUN_0007e2fa(0x000f3de7, uVar5);
        uint64_t re = FUN_0007e2ec(0x000f3a5d, 0x9b0);
        pb = (volatile uint8_t*)(uint32_t)(re >> 32);
        pm = (volatile uint8_t*)0x000f3a5dUL;   /* r2 clobbered to last e2fa arg */
        goto L_faa;
    }
    p2[0x24] = *(volatile uint8_t*)(0x000f3e4eUL + uVar5);
    p2[0x27] = 0;
    p2[0x25] = p1[9];
    uint64_t r = FUN_0008148a();
    pb = (volatile uint8_t*)(uint32_t)(r >> 32);
    pb[0x26] = (uint8_t)r;
    if (p1[2] == 1){
        pm = p1;
      L_faa:
        *(volatile uint32_t*)(pb+8) = (uint32_t)((uint32_t)pm + 0x90);
        *(volatile uint32_t*)(pb+4) = (uint32_t)((uint32_t)pm[8]*7 + 0x20002000UL);
        {
            uint32_t iVar3 = (uint32_t)pm + 0x97, iVar4 = (uint32_t)pm + 0x9e;
            if (pm[3] != 0){ iVar3 = (uint32_t)pm + 0x9e; iVar4 = (uint32_t)pm + 0x97; }
            *(volatile uint32_t*)(pb+0xc) = iVar3;
            *(volatile uint32_t*)(pb+0x10) = iVar4;
        }
        *(volatile uint16_t*)(pb+0x14) = *(volatile uint16_t*)(pm+0xa6);
        *(volatile uint16_t*)(pb+0x16) = *(volatile uint16_t*)(pm+0xac);
        *(volatile uint16_t*)(pb+0x18) = *(volatile uint16_t*)(pm+0xae);
        *(volatile uint32_t*)(pb+0x1c) = (uint32_t)((uint32_t)pm + 0xc4);
        *(volatile uint32_t*)(pb+0x20) = (uint32_t)((uint32_t)pm + 0xc6);
        {
            int c0 = *(volatile int*)(pm+0xc0);
            if (c0 != 0 && ((int)((uint32_t)*(volatile uint8_t*)(c0+0xd) << 0x1b) < 0))
                pb[0x27] = 1;
        }
        {
            int c0 = *(volatile int*)(pm+0xc0);
            if (c0 != 0 && ((int)((uint32_t)*(volatile uint8_t*)(c0+0xd) << 0x1a) < 0))
                pb[0x27] = pb[0x27] | 2;
        }
        return 0;
    }
    return 0xffffffea;
}

