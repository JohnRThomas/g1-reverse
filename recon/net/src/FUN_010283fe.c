/* net-core FUN_010283fe @ 0x10283fe  (CFG-directed candidate) */
#include <stdint.h>
extern void FUN_01021920(uint32_t, const void *, uint32_t, uint32_t, uint32_t); /* =FUN_01021920 */
void FUN_010283fe(uint32_t context, uint32_t detail0, uint32_t detail1)
{
    struct diagnostic_args { uint32_t detail0; uint32_t detail1; } args;
    args.detail0 = detail0;
    args.detail1 = detail1;
    FUN_01021920(context, &args, 0x988u, 0u, context);
}
