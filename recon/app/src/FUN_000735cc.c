/* Reconstructed FUN_000735cc @ 0x735cc */
#include <stdint.h>
#include <stdbool.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern int FUN_00086406(void); extern int FUN_00072040(uint32_t); extern void FUN_00072078(uint32_t); extern uint64_t FUN_0007205c(uint32_t);
extern void FUN_0008656a(void*); extern void FUN_00086596(void*); extern int FUN_00072c98(void*,void*); extern void FUN_00072908(void*,uint32_t,uint32_t,uint32_t);
extern void FUN_0007e2fa(uint32_t,...); extern void FUN_0007e2ec(uint32_t,uint32_t);
bool FUN_000735cc(uint8_t *obj,uint8_t *request)
{
    if (!obj) { FUN_0007e2fa(0x99cbd,0xf82df,0xf820f,0x411); FUN_0007e2ec(0xf820f,0x411); }
    if (!request) { FUN_0007e2fa(0x99cbd,0xf8291,0xf820f,0x412); FUN_0007e2ec(0xf820f,0x412); }
    if (FUN_00086406()) { FUN_0007e2fa(0x99cbd,0xf3d75,0xf820f,0x413); FUN_0007e2ec(0xf820f,0x413); }
    uint32_t bp=__get_BASEPRI(); __set_BASEPRI_MAX(0x20); __ISB();
    if (!FUN_00072040(0x2000b480)) { FUN_0007e2fa(0x99cbd,0xf0920,0xf08c7,0x72); FUN_0007e2fa(0xf0935,0x2000b480); FUN_0007e2ec(0xf08c7,0x72); }
    FUN_00072078(0x2000b480); bool active=(*(uint32_t *)(obj+0xc)&0xf)!=0; int notify=0;
    if (active) { FUN_0008656a(obj); FUN_00086596(obj); notify=FUN_00072c98(obj,request); }
    uint64_t unlock=FUN_0007205c(0x2000b480);
    if (!(uint32_t)unlock) { FUN_0007e2fa(0x99cbd,0xf08f4,0xf08c7,0xf0); FUN_0007e2fa(0xf090b,0x2000b480); FUN_0007e2ec(0xf08c7,0xf0); }
    __set_BASEPRI(bp); __ISB();
    if (notify) FUN_00072908(request+8,(uint32_t)(unlock>>32),UINT32_MAX,UINT32_MAX);
    return active;
}
