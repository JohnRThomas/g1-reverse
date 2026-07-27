/* Reconstructed FUN_0004ee68 @ 0x4ee68  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern unsigned int FUN_0004ed3c(unsigned int, const void *);
extern int FUN_0007f460(void);
extern int FUN_0007f4c8(int a0);
extern int FUN_0007f4d2(void);
extern int FUN_0007f570(int a0, int a1, void *a2);
extern int FUN_00080d3e(int a0, void *a1);

static __attribute__((always_inline)) inline
void copy17(unsigned char *destination, uintptr_t source)
{
    volatile const unsigned char *bytes =
        (volatile const unsigned char *)source;
    for (unsigned i = 0; i != 17; ++i) destination[i] = bytes[i];
}

int FUN_0004ee68(int param_1, int *param_2)
{
    struct work_area {
        unsigned char selector_a[4];
        unsigned char selector_b[4];
        unsigned char query_a[20];
        unsigned char lookup_a[20];
        unsigned char query_b[20];
        unsigned char lookup_b[20];
        unsigned char query_c[20];
        unsigned char common[24];
    } work;
    int *context;
    int handle;
    int result;

    FUN_0007f4d2();
    context = (int *)(long)FUN_0007f460();
    copy17(work.common + 4, 0x000887b7);
    result = FUN_00080d3e(*context, work.common + 4);
    if (result != 0) return -0x86;

    param_2[0] = 0;
    param_2[1] = 0;
    param_2[2] = 0;
    param_2[3] = 0;
    *(unsigned short *)(param_2 + 4) = 0;

    copy17(work.query_a, 0x000887c8);
    handle = FUN_0004ed3c(param_1, work.query_a);
    if (handle == 0) return -0x16;
    copy17(work.lookup_a, 0x000887c8);
    result = FUN_0007f570(param_1, handle, work.lookup_a);
    if (result == 0) return -0x16;
    *(unsigned short *)((unsigned char *)param_2 + 8) =
        *(unsigned short *)(result + 4);

    copy17(work.query_b, 0x000887d9);
    handle = FUN_0004ed3c(param_1, work.query_b);
    if (handle == 0) return -0x16;
    copy17(work.lookup_b, 0x000887d9);
    result = FUN_0007f570(param_1, handle, work.lookup_b);
    if (result == 0) return -0x16;
    *(unsigned short *)((unsigned char *)param_2 + 10) =
        *(unsigned short *)(result + 4);

    work.selector_a[0] = 0;
    *(unsigned short *)(work.selector_a + 2) = 0x2902;
    result = FUN_0007f570(param_1, handle, work.selector_a);
    if (result == 0) return -0x16;
    *(unsigned short *)((unsigned char *)param_2 + 12) =
        *(unsigned short *)(result + 4);

    copy17(work.query_c, 0x000887ea);
    handle = FUN_0004ed3c(param_1, work.query_c);
    if (handle == 0) return -0x16;
    copy17(work.common + 4, 0x000887ea);
    result = FUN_0007f570(param_1, handle, work.common + 4);
    if (result == 0) return -0x16;
    *(unsigned short *)((unsigned char *)param_2 + 14) =
        *(unsigned short *)(result + 4);

    work.selector_b[0] = 0;
    *(unsigned short *)(work.selector_b + 2) = 0x2902;
    result = FUN_0007f570(param_1, handle, work.selector_b);
    if (result == 0) return -0x16;
    *(unsigned short *)((unsigned char *)param_2 + 16) =
        *(unsigned short *)(result + 4);
    param_2[0] = FUN_0007f4c8(param_1);
    return 0;
}
