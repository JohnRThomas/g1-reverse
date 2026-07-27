/* Reconstructed FUN_000669f4 @ 0x669f4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_0007e2fa(unsigned long, ...);
extern uint32_t FUN_0007e2ec(uint32_t,uint32_t);
extern uint32_t FUN_000664f0(void);
extern uint32_t FUN_0006649c(void);
extern void FUN_000667e0(void);
extern void FUN_00066720(uint32_t,uint32_t);
extern void FUN_000666e0(uint32_t,uint32_t);

#define g1_recon_nrfx_qspi_cinstr_xfer FUN_000669f4
int g1_recon_nrfx_qspi_cinstr_xfer(uint8_t *param_1, uint32_t param_2,
                                   uint32_t param_3, uint32_t param_4){
    volatile uint8_t *sb = (volatile uint8_t*)0x2000b348UL;
    uint32_t r0v;
    r0v = *(volatile uint8_t*)(sb+0x30);
    if (r0v == 0){
        FUN_0007e2fa(0x00099cbd,0x000f6d9a,0x000f6d5e,0x1dd,param_4);
        r0v = FUN_0007e2ec(0x000f6d5e,0x1dd);
    }
  A20:
    if (r0v != 1) return 0x0bad000b;
    if (*(volatile uint8_t*)(sb+0x38) == 0){
        if (FUN_000664f0() == 0x0bad0007) return 0x0bad0007;
    }
    *(volatile uint32_t*)0x5002b308UL = 1;
    FUN_000667e0();
    if (param_2 != 0) FUN_00066720(param_1[1], param_2);
    *(volatile uint8_t*)(sb+0x39) = 0;
    *(volatile uint32_t*)0x5002b100UL = 0;
    {
        uint32_t v = ((uint32_t)param_1[2] << 0xc) | ((uint32_t)param_1[1] << 8) | (uint32_t)param_1[0]
                   | ((uint32_t)param_1[3] << 0xd) | ((uint32_t)param_1[4] << 0xe) | ((uint32_t)param_1[5] << 0xf);
        *(volatile uint32_t*)0x5002b634UL = v;
    }
    if (FUN_0006649c() == 0x0bad0007){
        if (param_1[4] != 0) return 0x0bad0007;
        FUN_0007e2fa(0x00099cbd,0x000f6dde,0x000f6d5e,0x20a,param_4);
        r0v = FUN_0007e2ec(0x000f6d5e,0x20a);
        goto A20;
    } else {
        *(volatile uint32_t*)0x5002b100UL = 0;
        if (param_3 != 0) FUN_000666e0(param_1[1], param_3);
        return 0x0bad0000;
    }
}
