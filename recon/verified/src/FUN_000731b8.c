/* Reconstructed FUN_000731b8 @ 0x731b8 */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern int FUN_00086406(void); extern int FUN_00072040(uint32_t); extern void FUN_00072078(uint32_t); extern int FUN_0007205c(uint32_t);
extern void FUN_00086588(void *); extern uint32_t FUN_00074b10(uint32_t,uint32_t,void*,uint32_t,uint32_t,uint32_t,uint32_t);
extern void FUN_0007e2fa(uint32_t,...); extern void FUN_0007e2ec(uint32_t,uint32_t);
uint32_t FUN_000731b8(uint8_t *obj, int requested, uint32_t a, uint32_t b)
{
    if (!obj) { FUN_0007e2fa(0x99cbd,0xf586b,0xf820f,0x2ed,0,requested,a,b); FUN_0007e2ec(0xf820f,0x2ed); }
    if (FUN_00086406()) { FUN_0007e2fa(0x99cbd,0xf3d75,0xf820f,0x2ee,obj,requested,a,b); FUN_0007e2ec(0xf820f,0x2ee); }
    uint32_t bp=__get_BASEPRI(); __set_BASEPRI_MAX(0x20); __ISB();
    if (!FUN_00072040(0x2000b480)) { FUN_0007e2fa(0x99cbd,0xf0920,0xf08c7,0x72,obj,requested,a,b); FUN_0007e2fa(0xf0935,0x2000b480); FUN_0007e2ec(0xf08c7,0x72); }
    FUN_00072078(0x2000b480); uint32_t flags=*(uint32_t *)(obj+0xf0);
    if (!(flags&6)) {
        if (!requested && !*(uint32_t *)(obj+0xd8)) {
            if (FUN_0007205c(0x2000b480)) { __set_BASEPRI(bp); __ISB(); return 0; }
            FUN_0007e2fa(0x99cbd,0xf08f4,0xf08c7,0xf0,obj,requested,a,b); FUN_0007e2fa(0xf090b,0x2000b480); FUN_0007e2ec(0xf08c7,0xf0);
        }
        flags |= requested ? 0xc : 4;
    } else { *(uint32_t *)(obj+0xf0)=flags|4; if (requested) flags|=0xc; else goto run; }
    *(uint32_t *)(obj+0xf0)=flags;
run: FUN_00086588(obj); return FUN_00074b10(0x2000b480,bp,obj+0xe8,UINT32_MAX,UINT32_MAX,UINT32_MAX,0);
}
