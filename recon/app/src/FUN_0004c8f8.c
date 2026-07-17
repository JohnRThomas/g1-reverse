/* Reconstructed FUN_0004c8f8 @ 0x4c8f8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern unsigned FUN_000723b8(int,...);
extern unsigned FUN_00072558(int,...);
extern unsigned FUN_0007e55a(int,...);
extern unsigned FUN_0007e574(int,...);
extern unsigned FUN_0007e5c8(int,...);
extern unsigned FUN_0007e658(int,...);
extern unsigned FUN_0007e65e(int,...);
extern unsigned FUN_0007e672(int,...);
extern unsigned FUN_0007e6e2(int,...);
extern unsigned FUN_0007e776(int,...);
extern unsigned FUN_0007e7ea(int,...);
extern unsigned FUN_0007e83a(int,...);

struct storage_update_frame {
    uint8_t reserved0[8];
    uint32_t lock;
    uint8_t reserved8[4];
    uint32_t cursor;
    uint16_t item[3];
    uint8_t reserved22[2];
    uint16_t update_id;
    int16_t update_offset;
    uint16_t update_length;
    uint8_t reserved30;
    uint8_t update_tag;
    uint8_t reserved32[8];
    uint32_t log_record[2];
};

unsigned FUN_0004c8f8(int param_1, unsigned param_2, int param_3, unsigned param_4)
{
    unsigned uVar1, uVar3, uVar5, uVar6;
    int iVar2;
    struct storage_update_frame frame;

    if (*(char *)(param_1 + 0x10) == 0) {
        uVar5 = 0xfffffff3;
        frame.log_record[1] = 0x000f0ae4;
        frame.log_record[0] = 2;
        FUN_0007e658(0x000881b8, 0x1040, (int)frame.log_record);
    } else {
        int p2c = *(int *)(param_1 + 0x2c);
        iVar2 = FUN_0007e65e(p2c, 8);
        uVar3 = FUN_0007e65e(p2c, param_4);
        if (((unsigned)*(unsigned short *)(param_1 + 0xc) + iVar2 * -4 < param_4) ||
            ((param_4 != 0) && (param_3 == 0))) {
            uVar5 = 0xffffffea;
        } else {
            frame.cursor = *(unsigned *)(param_1 + 4);
            do {
                uVar5 = frame.cursor;
                unsigned r = FUN_0007e6e2(param_1, (int)&frame.cursor,
                                           (int)&frame.item[0]);
                if (r != 0) return r;
                if (frame.item[0] == (unsigned short)param_2) {
                    r = FUN_0007e672(param_1, (int)&frame.item[0]);
                    if ((int)r != 0) {
                        if (param_4 == 0) {
                            if (frame.item[2] == 0) return 0;
                        } else if (frame.item[2] == param_4) {
                            r = FUN_0007e574(param_1,
                                (uVar5 & 0xffff0000) + (unsigned)frame.item[1],
                                param_3, param_4);
                            if ((int)r < 1) return r;
                        }
                        goto LAB_0004c9ba;
                    }
                }
            } while (*(unsigned *)(param_1 + 4) != frame.cursor);
            uVar5 = 0;
            if (param_4 != 0) {
LAB_0004c9ba:
                if (uVar3 != 0) uVar3 = (uVar3 + iVar2) & 0xffff;
                frame.lock = param_1 + 0x14;
                FUN_000723b8(frame.lock, 0, 0xffffffff, 0xffffffff);
                uVar1 = 0xffff0000;
                for (uVar6 = 0; uVar6 != *(unsigned short *)(param_1 + 0xe); uVar6 = uVar6 + 1) {
                    uVar5 = *(unsigned *)(param_1 + 4);
                    if (uVar3 + *(int *)(param_1 + 8) <= uVar5) {
                        frame.update_offset = (short)*(int *)(param_1 + 8);
                        frame.update_tag = 0xff;
                        frame.update_id = (unsigned short)param_2;
                        frame.update_length = (unsigned short)param_4;
                        FUN_0007e5c8((int)&frame.update_id);
                        uVar5 = FUN_0007e776(param_1, *(unsigned *)(param_1 + 8), param_3, param_4);
                        iVar2 = FUN_0007e65e(*(int *)(param_1 + 0x2c), param_4);
                        *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + iVar2;
                        if ((uVar5 == 0) &&
                            (uVar5 = FUN_0007e7ea(param_1,
                                                 (int)&frame.update_id),
                             uVar5 == 0)) {
                            uVar5 = param_4;
                        }
                        goto LAB_0004ca30;
                    }
                    iVar2 = FUN_0007e65e(*(int *)(param_1 + 0x2c), 8);
                    frame.update_id = 0xffff;
                    frame.update_tag = 0xff;
                    frame.update_length = 0;
                    frame.update_offset = (short)uVar5 + (short)iVar2;
                    *(unsigned *)(param_1 + 4) = ((uVar5 & uVar1) + (unsigned)*(unsigned short *)(param_1 + 0xc)) - iVar2;
                    FUN_0007e5c8((int)&frame.update_id);
                    FUN_0007e7ea(param_1, (int)&frame.update_id);
                    FUN_0007e55a(param_1, param_1 + 4);
                    *(unsigned *)(param_1 + 8) = *(unsigned *)(param_1 + 4) & uVar1;
                    uVar5 = FUN_0007e83a(param_1);
                    if (uVar5 != 0) goto LAB_0004ca30;
                }
                uVar5 = 0xffffffe4;
LAB_0004ca30:
                FUN_00072558(frame.lock);
            }
        }
    }
    return uVar5;
}
