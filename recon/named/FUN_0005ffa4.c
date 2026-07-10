/* named: FUN_0005ffa4 */
/* Reconstructed FUN_0005ffa4 @ 0x5ffa4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004ba38(int);
extern int nrfx_pdm_buffer_set(int,int);
extern int nrfx_pdm_stop(void);
extern int k_mem_slab_alloc(int,void*,int,int);
extern int k_mem_slab_free(int, ...);
extern int k_msgq_put(int,int,int,int);
extern int FUN_000837a2(int,int,void*);
#define PW(off) (*(volatile uint32_t *)(0x2000b008 + (off)))
#define CB(off) (*(volatile char *)(0x2000b008 + (off)))
#define WB(off) (*(volatile unsigned char *)(0x2000b008 + (off)))

void FUN_0005ffa4(char *param_1)
{
    int iVar2;
    unsigned int uVar3;
    char cVar4;
    int local_40, local_3c, iStack_38;
    uint32_t local_30[4];
    int local_20, local_1c;

    cVar4 = *param_1;
    if (cVar4 == '\0') {
        iVar2 = *(int *)(param_1 + 4);
        if (CB(0x52) != '\0') {
            if (iVar2 == 0) {
LAB_00060032:
                if (CB(0x51) == '\0') return;
                WB(0x51) = 0;
                if (-1 < (int)((unsigned int)WB(0x50) << 0x1f)) return;
                FUN_0004ba38(PW(0));
                return;
            }
            goto LAB_00060086;
        }
LAB_0005ffbe:
        if (iVar2 == 0) return;
        cVar4 = '\0';
LAB_000600b0:
        iVar2 = k_msgq_put(0x2000b024, (int)(param_1 + 4), 0, 0);
        if (iVar2 < 0) {
            local_1c = 0x000f585d;
            local_20 = 2;
            FUN_000837a2(0x000881a0, 0x1040, &local_20);
            k_mem_slab_free(PW(0x14), *(int *)(param_1 + 4));
            goto LAB_00060008;
        }
    } else {
        iVar2 = k_mem_slab_alloc(PW(0x14), local_30, 0, 0);
        uVar3 = 0x000f5822;
        if ((iVar2 < 0) ||
            (iVar2 = nrfx_pdm_buffer_set(local_30[0], (unsigned int)(PW(0x18) << 0xf) >> 0x10), uVar3 = 0x000f5840,
             iVar2 != 0x0bad0000)) {
            local_40 = 3;
            local_3c = uVar3;
            iStack_38 = iVar2;
            FUN_000837a2(0x000881a0, 0x1840, &local_40);
            if (CB(0x52) == '\0') {
                if (*(int *)(param_1 + 4) == 0) goto LAB_00060008;
                goto LAB_000600b0;
            }
            cVar4 = CB(0x52);
            if (*(int *)(param_1 + 4) == 0) {
                if ((CB(0x51) != '\0') &&
                    (WB(0x51) = 0, (int)((unsigned int)WB(0x50) << 0x1f) < 0)) {
                    FUN_0004ba38(PW(0));
                }
                goto LAB_00060008;
            }
        } else {
            iVar2 = *(int *)(param_1 + 4);
            if (CB(0x52) == '\0') goto LAB_0005ffbe;
            if (iVar2 == 0) goto LAB_00060032;
            cVar4 = '\0';
        }
LAB_00060086:
        k_mem_slab_free(PW(0x14));
        if ((CB(0x51) != '\0') &&
            (WB(0x51) = 0, (int)((unsigned int)WB(0x50) << 0x1f) < 0)) {
            FUN_0004ba38(PW(0));
        }
    }
    if (cVar4 == '\0') return;
LAB_00060008:
    WB(0x52) = 1;
    nrfx_pdm_stop();
    return;
}

