/* Full reconstruction FUN_00063b7c @ 0x00063b7c (44-byte exact extent). */
#include <stdint.h>

extern void FUN_0004d678(void);
extern void FUN_0004d944(uintptr_t, uint32_t, const void *, uint32_t, ...);
extern void FUN_00050af8(uint32_t) __attribute__((noreturn));

struct log_record2 { uint32_t count, format; };

void FUN_00063b7c(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    struct log_record2 record = { 2, 0x000f66f9u };
    FUN_0004d678();
    FUN_0004d944(0x000881a8u, 0x1040u, &record, 0, a, b, c, d);
    FUN_00050af8(0);
}
