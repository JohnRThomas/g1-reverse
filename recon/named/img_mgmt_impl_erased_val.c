/* named: img_mgmt_impl_erased_val */
/* Reconstructed img_mgmt_impl_erased_val @ 0x51a5c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern long long FUN_0005169c(void);
extern int flash_area_open(unsigned a, void* b);
extern unsigned char flash_area_erased_val(unsigned a);
extern void nullsub_3(unsigned a);
extern void FUN_0008096a(unsigned a, int b, void* c);
unsigned img_mgmt_impl_erased_val(void){
    unsigned local_1c[2];
    long long uVar3 = FUN_0005169c();
    int r5 = (int)(unsigned)uVar3;
    unsigned uVar2;
    if (r5 < 0){
        uVar2 = 0xe;
    } else {
        int local_24 = flash_area_open((unsigned)r5 & 0xff, &local_1c[0]);
        if (local_24 == 0){
            unsigned char uVar1 = flash_area_erased_val(local_1c[0]);
            *(volatile unsigned char*)(uintptr_t)((unsigned long long)uVar3 >> 32) = uVar1;
            nullsub_3(local_1c[0]);
            uVar2 = 0;
        } else {
            volatile struct { unsigned a, b, c, d; } s;
            s.a = 4; s.b = 0xf25fb; s.c = (unsigned)r5; s.d = (unsigned)local_24;
            FUN_0008096a(0x88208, 0x2040, (void*)&s);
            uVar2 = 0xa;
        }
    }
    return uVar2;
}

