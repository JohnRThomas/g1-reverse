/* Reconstructed update_display_status @ 0x7cce8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0002bed0(void);
extern void FUN_0002efc0(void);
extern void FUN_0007ce60(int);
extern void FUN_00086c78(void*, int, int);
extern void send_event_status(int);

void update_display_status(int param_1, int param_2)
{
    int iVar1;
    char *pcVar2;
    char cVar3 = 0;

    iVar1 = FUN_0002bed0();
    if (iVar1 == 0) {
        return;
    }
    if ((*(char*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0x1004) + 6) != 0) ||
        ((cVar3 = *(char*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0x1008) + 6)), cVar3 != 0)) {
        FUN_0002efc0();
        FUN_00086c78((void*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0x1008) + 6), 0, 400);
        FUN_00086c78((void*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0x1004) + 6), 0, 400);
        cVar3 = 1;
    }
    if (**(char**)(intptr_t)(param_1 + 0x1000) != 0) {
        **(char**)(intptr_t)(param_1 + 0x1000) = 0;
        cVar3 = 1;
    }
    if (*(char*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0xffc) + 1) != 0) {
        FUN_0002efc0();
        *(unsigned char*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0xffc) + 1) = 0;
        cVar3 = 1;
    }
    if (**(char**)(intptr_t)(param_1 + 0x1020) != 0) {
        FUN_0002efc0();
        **(unsigned char**)(intptr_t)(param_1 + 0x1020) = 0;
        cVar3 = 1;
    }
    if (**(char**)(intptr_t)(param_1 + 0x1010) != 0) {
        **(char**)(intptr_t)(param_1 + 0x1010) = 0;
        cVar3 = 1;
    }
    if (**(char**)(intptr_t)(param_1 + 0x1014) != 0) {
        **(char**)(intptr_t)(param_1 + 0x1014) = 0;
        cVar3 = 1;
    }
    if (*(char*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0x100c) + 7) == 0) {
        pcVar2 = *(char**)(intptr_t)(param_1 + 0x101c);
        if (*pcVar2 == 0) {
            if (cVar3 == 0) {
                return;
            }
            goto LAB_0007cd8a;
        }
    } else {
        FUN_0002efc0();
        FUN_0007ce60(1);
        pcVar2 = *(char**)(intptr_t)(param_1 + 0x101c);
        if (*pcVar2 == 0) goto LAB_0007cd8a;
    }
    *pcVar2 = 0;
LAB_0007cd8a:
    if (param_2 != 0) {
        send_event_status(0);
    }
    FUN_00086c78((void*)(intptr_t)(param_1 + 0xef), 0, 0x5dc);
    return;
}

