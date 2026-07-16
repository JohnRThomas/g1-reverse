/* Reconstructed FUN_000729fc @ 0x729fc
 * CFG_VERIFY_PREFIX_FIRST: drains callback-owned queue until it reports empty. */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern int FUN_00072040(uint32_t); extern void FUN_00072078(uint32_t);
extern int FUN_000744a4(void *); extern void FUN_000738d4(void);
extern void FUN_0008688e(void *, int); extern void FUN_000739f0(uint32_t,uint32_t);
extern void FUN_0007e2fa(uint32_t,...); extern void FUN_0007e2ec(uint32_t,uint32_t);
void FUN_000729fc(uint8_t *queue)
{
    uint32_t bp=__get_BASEPRI(); __set_BASEPRI_MAX(0x20); __ISB();
    if (!FUN_00072040(0x2000b474)) { FUN_0007e2fa(0x99cbd,0xf0920,0xf08c7,0x72); FUN_0007e2fa(0xf0935,0x2000b474); FUN_0007e2ec(0xf08c7,0x72); }
    FUN_00072078(0x2000b474);
    uint8_t *p; while ((p=(uint8_t *)(uintptr_t)FUN_000744a4(queue)) != 0) { *(uint32_t *)(p+0x90)=0xfffffff5; FUN_000738d4(); }
    *(uint32_t *)(queue+8)=0; FUN_0008688e(queue+0x10,2); FUN_000739f0(0x2000b474,bp);
}
