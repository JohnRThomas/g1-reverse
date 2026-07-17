#include "g1_net_symbols.h"
/* net-core FUN_0102ea40 @ 0x102ea40 */
#include <stdint.h>

extern void FUN_0102e284(uint32_t channel, uint32_t format,
                         const uint32_t *record, uint32_t flags);
extern void FUN_010359b8(uint32_t context, const uint32_t *values);

void FUN_0102ea40(uint32_t context, const uint32_t *values)
{
    if (values != 0) {
        uint32_t record[5];

        record[0] = 5;
        record[1] = ((unsigned long)&rodata_103d82a) /*=0x103d82a*/;
        record[2] = values[0];
        record[3] = values[1];
        record[4] = values[2];
        FUN_0102e284(((unsigned long)&rodata_103c0c4) /*=0x103c0c4*/, 0x2840, record, 0);

        record[0] = 5;
        record[1] = ((unsigned long)&rodata_103d859) /*=0x103d859*/;
        record[2] = values[3];
        record[3] = values[4];
        record[4] = values[5];
        FUN_0102e284(((unsigned long)&rodata_103c0c4) /*=0x103c0c4*/, 0x2840, record, 0);

        record[2] = 3;
        record[3] = ((unsigned long)&rodata_103d888) /*=0x103d888*/;
        record[4] = values[7];
        FUN_0102e284(((unsigned long)&rodata_103c0c4) /*=0x103c0c4*/, 0x1840, &record[2], 0);

        record[2] = 3;
        record[3] = ((unsigned long)&rodata_103d897) /*=0x103d897*/;
        record[4] = values[6];
        FUN_0102e284(((unsigned long)&rodata_103c0c4) /*=0x103c0c4*/, 0x1840, &record[2], 0);
    }
    FUN_010359b8(context, values);
}
