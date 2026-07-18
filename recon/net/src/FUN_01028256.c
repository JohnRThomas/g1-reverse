/* net-core FUN_01028256 @ 0x1028256  (CFG-directed candidate) */
#include <stdint.h>
extern uint32_t FUN_0100f66c(void);
extern uint32_t FUN_0101e398(void);
extern uint32_t FUN_01028134(uint32_t,uint32_t);
extern uint32_t FUN_0101e404(uint32_t);
extern __attribute__((noreturn)) void FUN_01008d00(uint32_t,uint32_t);
#define sdc_assertion_fail FUN_01008d00 /* Raw backmap: 0x01008d00. */
uint32_t FUN_01028256(void) {
    uint32_t selected=0;
    uint32_t result=0;
    for(uint32_t remaining=0x23;remaining!=0;--remaining) {
        uint32_t candidate=FUN_0100f66c();
        result=FUN_0101e398();
        if(result!=0) {
            if(FUN_01028134(candidate,0)==0) {
                selected=candidate;
                result=FUN_0101e404(candidate);
            } else result=0;
        }
        if(result!=0) break;
    }
    if(selected==0) sdc_assertion_fail(0xf,0x20a);
    return selected;
}
