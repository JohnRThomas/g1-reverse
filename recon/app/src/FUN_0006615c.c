/* Reconstructed FUN_0006615c @ 0x6615c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0007e2fa(unsigned,unsigned,unsigned,unsigned);
extern long long FUN_0007e2ec(unsigned,unsigned);
extern void FUN_00066050(void);
unsigned FUN_0006615c(int param_1, int param_2){
    unsigned r0v = (unsigned)param_1;
    unsigned r1v = (unsigned)param_2;
    if (r0v != 0) goto L_174;
    FUN_0007e2fa(0x99cbd,0xf6c00,0xf6ceb,0x78);
    { long long r=FUN_0007e2ec(0xf6ceb,0x78); r0v=(unsigned)r; r1v=(unsigned)((unsigned long long)r>>32);}
L_174:
    if (r1v != 0) goto L_186;
    FUN_0007e2fa(0x99cbd,0xf6abf,0xf6ceb,0x79);
    { long long r=FUN_0007e2ec(0xf6ceb,0x79); r0v=(unsigned)r; r1v=(unsigned)((unsigned long long)r>>32);}
    goto L_174;
L_186:
    {
        volatile unsigned char* p = (volatile unsigned char*)0x2000b330UL;
        if (*(volatile unsigned char*)(p + 0x10) != 0) return 0xbad0005;
        *(volatile int*)(p + 4) = 0;
        *(volatile int*)(p + 8) = 0;
        *(volatile unsigned short*)(p + 0x12) = 0;
        *(volatile unsigned char*)(p + 0x11) = 0;
        unsigned char uVar1 = *(unsigned char*)(r0v + 0x15);
        *(volatile int*)p = (int)r1v;
        *(volatile unsigned char*)(p + 0x15) = uVar1;
        if (*(unsigned char*)(r0v + 0x10) > 0x50) return 0xbad0004;
        if (*(unsigned char*)(r0v + 0x11) > 0x50) return 0xbad0004;
        FUN_00066050();
        *(volatile unsigned char*)(p + 0x10) = 1;
        return 0xbad0000;
    }
}

