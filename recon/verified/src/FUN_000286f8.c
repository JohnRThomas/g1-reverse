/* Reconstructed FUN_000286f8 @ 0x286f8  (parity: 1/1 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned undefined4;
typedef unsigned char undefined1;
extern int FUN_000167a8(void);
extern void FUN_00027448(unsigned a, int b, int c);
extern void FUN_000275fc(void);
extern void FUN_0002bc2c(unsigned a, unsigned b, int c);
extern void FUN_0002bffc(unsigned a, int b, int c);
extern void FUN_0002c1fc(void);
extern void FUN_0002c224(int a);
extern void FUN_0002c324(void);
extern int FUN_0002efa8(void);
extern void FUN_0002efc0(void);
extern int FUN_00033cf8(void);
extern void FUN_0007cb8e(int a);
extern void FUN_0007cdb6(unsigned a, int b);
extern void FUN_0007ce60(int a);
extern void send_event_status(int a);
extern int sync_to_slave(unsigned a, int b, int c);
extern void thunk_FUN_00074844(int a, int b);
extern void update_persist_task_status(unsigned a, int b, int c);

void FUN_000286f8(unsigned param_1)
{
    volatile char *pcVar2 = (volatile char *)0x2000ff4d;
    volatile char *pcVar1 = (volatile char *)0x20018d97;
    int iVar3;
    char *pcVar4;
    unsigned uVar5;
    unsigned char uVar6;
    undefined1 *puVar7;

    do {
        while ((iVar3 = FUN_000167a8(), *(volatile char *)(iVar3 + 1) == '\x01' ||
               (iVar3 = FUN_000167a8(), *(volatile char *)(iVar3 + 1) == '\b'))) {
            thunk_FUN_00074844(0x28000, 0);
        }
        pcVar4 = (char *)FUN_000167a8();
        if (*(volatile char *)pcVar4 == '\x01') {
            iVar3 = FUN_000167a8();
            switch (**(volatile unsigned char **)(iVar3 + 0x100c)) {
            case 1:
                uVar5 = FUN_000167a8();
                iVar3 = sync_to_slave(uVar5, 0xd, 0);
                if (iVar3 < 500) {
                    FUN_0007cdb6(param_1, 0);
                    FUN_0007ce60(0);
                    iVar3 = FUN_0002efa8();
                    if (iVar3 == 0) {
                        iVar3 = FUN_000167a8();
                        uVar6 = 3;
                        puVar7 = *(volatile undefined1 **)(iVar3 + 0x100c);
                    } else {
                        iVar3 = FUN_000167a8();
                        uVar6 = 2;
                        puVar7 = *(volatile undefined1 **)(iVar3 + 0x100c);
                    }
                    *(volatile undefined1 *)puVar7 = uVar6;
                    iVar3 = FUN_000167a8();
                    if (**(volatile int **)(iVar3 + 0x1054) != 0x10) {
                        uVar5 = FUN_000167a8();
                        update_persist_task_status(uVar5, 0x10, 2);
                    }
                }
                break;
            case 3:
                uVar5 = FUN_000167a8();
                iVar3 = sync_to_slave(uVar5, 0xe, 0);
                if (iVar3 < 500) {
                    iVar3 = FUN_000167a8();
                    uVar6 = 4;
                    puVar7 = *(volatile undefined1 **)(iVar3 + 0x100c);
LAB_0002884a:
                    *(volatile undefined1 *)puVar7 = uVar6;
                }
                break;
            case 5:
                uVar5 = FUN_000167a8();
                iVar3 = sync_to_slave(uVar5, 0xf, 0);
                if (iVar3 < 500) {
                    FUN_0002efc0();
                    send_event_status(0x18);
                    iVar3 = FUN_000167a8();
                    uVar6 = 6;
                    puVar7 = *(volatile undefined1 **)(iVar3 + 0x100c);
                    goto LAB_0002884a;
                }
                break;
            case 10:
                uVar5 = FUN_000167a8();
                iVar3 = sync_to_slave(uVar5, 0x10, 0);
                if (iVar3 < 500) {
                    iVar3 = FUN_000167a8();
                    **(volatile undefined1 **)(iVar3 + 0x100c) = 0xb;
                    iVar3 = FUN_000167a8();
                    *(volatile undefined1 *)(iVar3 + 0xdb) = 8;
                }
                break;
            case 0xd:
                uVar5 = FUN_000167a8();
                iVar3 = sync_to_slave(uVar5, 0x11, 0);
                if (iVar3 < 500) {
                    iVar3 = FUN_000167a8();
                    uVar6 = 0xe;
                    puVar7 = *(volatile undefined1 **)(iVar3 + 0x100c);
                    goto LAB_0002884a;
                }
                break;
            case 0xf:
                uVar5 = FUN_000167a8();
                iVar3 = sync_to_slave(uVar5, 0x12, 0);
                if (iVar3 < 500) {
                    iVar3 = FUN_000167a8();
                    uVar6 = 0x10;
                    puVar7 = *(volatile undefined1 **)(iVar3 + 0x100c);
                    goto LAB_0002884a;
                }
            }
        } else {
            iVar3 = FUN_000167a8();
            if (**(volatile char **)(iVar3 + 0x100c) == '\x01') {
                uVar5 = FUN_000167a8();
                FUN_00027448(uVar5, 0xe, 0);
                FUN_0007cdb6(param_1, 0);
            } else if (**(volatile char **)(iVar3 + 0x100c) == '\x05') {
                uVar5 = FUN_000167a8();
                FUN_00027448(uVar5, 0xf, 0);
            }
        }
        if (*pcVar1 != '\0') {
            FUN_0007cb8e(2000);
            *pcVar1 = '\0';
        }
        FUN_000275fc();
        pcVar4 = (char *)FUN_000167a8();
        if ((*(volatile char *)pcVar4 == '\x01') && (*pcVar2 != '\0')) {
            FUN_0002c224(3);
            iVar3 = FUN_000167a8();
            if ((*(volatile char *)(iVar3 + 0x108f) != '\0') &&
                ((iVar3 = FUN_00033cf8(), iVar3 != 0 &&
                  (iVar3 = FUN_000167a8(), *(volatile char *)(iVar3 + 0xd5) != '\x04')))) {
                uVar5 = FUN_000167a8();
                FUN_0002bffc(uVar5, 4, 2);
                uVar5 = FUN_000167a8();
                FUN_0002bc2c(0xa0a7b, uVar5, 1);
                FUN_0002c1fc();
            }
            *pcVar2 = '\0';
            FUN_0002c324();
        }
        FUN_0007cb8e(200);
    } while (1);
}

