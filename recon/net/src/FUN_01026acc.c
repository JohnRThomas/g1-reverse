/* net-core FUN_01026acc @ 0x1026acc  (CFG-directed candidate) */
#include <stdint.h>
extern void FUN_0100951c(void *,void *);
extern __attribute__((noreturn)) void FUN_01008d00(uint32_t,uint32_t);
#define controller_packed_cursor_advance FUN_0100951c
#define sdc_assertion_fail FUN_01008d00
uint32_t FUN_01026acc(uint8_t *owner,uint32_t requested_arg) {
    uint16_t requested=(uint16_t)requested_arg;
    uint16_t *cursor=(uint16_t *)(owner+0x18+(*(uint16_t *)(owner+6)&0x7fff));
    uint16_t limit=*(uint16_t *)owner;
    if(limit<0x45) limit=0x45;
    if(requested>limit) sdc_assertion_fail(0x14,0x104);
    if(owner[0x12]!=1 || *cursor<requested) return 0;
    *cursor=requested;
    controller_packed_cursor_advance(owner,owner+6);
    owner[0x12]=0;
    return 1;
}
