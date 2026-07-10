/* named: get_demo_image_source */
/* Reconstructed get_demo_image_source @ 0x36820  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(void);
extern int get_device_info(void);
extern void pixelto4bithex(void);
extern int malloc(void);
extern void heap_free(void);
extern void printf(void);
extern int FUN_0007d1c8(void);
extern void memcpy(void);
extern void memset_bytes(void);
extern int strncmp(void);

typedef int (*fnptr)(int,int,int,int);

void get_demo_image_source(unsigned param_1)
{
    int puVar2 = malloc();
    if (puVar2 == 0) { DEBUG_PRINT(); return; }
    memset_bytes();
    if (4 < param_1) { DEBUG_PRINT(); param_1 = 0; }

    int r3a = get_device_info();
    int fn = *(volatile int*)(r3a + 0x1030);
    get_device_info();
    int iVar12 = (int)(param_1 * 0x3ebe + 0x180000);
    int iVar3 = ((fnptr)(intptr_t)fn)(0, iVar12, puVar2, 0x50);
    if (iVar3 != 0) { DEBUG_PRINT(); goto TAIL; }

    iVar3 = strncmp();
    if (iVar3 != 0) { DEBUG_PRINT(); goto TAIL; }

    int iVar3b = FUN_0007d1c8();
    int iVar5 = FUN_0007d1c8();
    int iVar6 = FUN_0007d1c8();

    if (*(volatile uint16_t*)(puVar2 + 0x1c) != 1) {
        printf();
        goto TAIL;
    }

    {
        int iv5 = iVar5;
        int iVar10 = iv5 + 7;
        *(volatile int*)0x20009fc4 = 0;
        if (iVar10 < 0) iVar10 = iv5 + 0xe;
        *(volatile int*)0x20009fc8 = 0;
        int iVar11 = iv5 + 0x1f;
        if (iVar11 < 0) iVar11 = iv5 + 0x3e;
        iVar12 = iVar12 + iVar3b + (iVar6 - 1) * (iVar11 >> 5) * 4;
        for (int r7 = 0; r7 < iVar6; r7++) {
            *(volatile int*)0x20009fc4 = 0;
            memset_bytes();
            int r7a = get_device_info();
            int fn2 = *(volatile int*)(r7a + 0x1030);
            get_device_info();
            int iVar7 = ((fnptr)(intptr_t)fn2)(0, iVar12, puVar2, iVar10 >> 3);
            if (iVar7 != 0) { DEBUG_PRINT(); goto TAIL; }
            for (int fp = 0; fp < (iVar10 >> 3); fp++) {
                pixelto4bithex();
            }
            if (*(volatile int*)0x20009fcc != 0) {
                *(volatile int*)0x20009fc8 = 0;
                get_device_info();
                memcpy();
            }
            iVar12 = iVar12 + (iVar11 >> 5) * -4;
        }
    }
TAIL:
    heap_free();
    return;
}

