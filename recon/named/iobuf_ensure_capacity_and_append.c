/* readable reconstruction; identity: FUN_00087736 @ 0x00087736
 * public-name: iobuf_ensure_capacity_and_append
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   heap_free_core                           <= FUN_00076d8c @ 0x00076d8c
 *   _malloc_r                                <= FUN_00076e20 @ 0x00076e20
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   heap_realloc_grow                        <= FUN_000876ec @ 0x000876ec
 *   iobuf_ensure_capacity_and_append         <= FUN_00087736 @ 0x00087736
 */
/* Reconstructed FUN_00087736 @ 0x87736  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int heap_free_core(void*,int);
extern int _malloc_r(void*,unsigned);
extern void memcpy(int,int,int);
extern void FUN_00086c44(int,unsigned,unsigned);
extern int heap_realloc_grow(void*,int,unsigned);

unsigned iobuf_ensure_capacity_and_append(uint32_t *param_1, int *param_2, unsigned param_3, unsigned param_4){
    unsigned uVar3;
    if ((unsigned)param_2[2] <= param_4){
        uVar3 = param_2[2];
        if (((int)(short)param_2[3] & 0x480) != 0){
            int iVar4 = param_2[0] - param_2[4];
            unsigned uVar2 = param_4 + 1 + iVar4;
            uVar3 = (unsigned)(((int)param_2[5] * 3) / 2);
            if (uVar3 < uVar2) uVar3 = uVar2;
            int iVar1;
            if (((int)(short)param_2[3] << 0x15) < 0){
                iVar1 = _malloc_r(param_1, uVar3);
                if (iVar1 == 0) goto L877d8;
                memcpy(iVar1, param_2[4], iVar4);
                *(unsigned short*)((char*)param_2+0xc) = (*(unsigned short*)((char*)param_2+0xc) & 0xfb7f) | 0x80;
            } else {
                iVar1 = heap_realloc_grow(param_1, param_2[4], uVar3);
                if (iVar1 == 0){
                    heap_free_core(param_1, param_2[4]);
                    goto L877d8;
                }
            }
            param_2[4] = iVar1;
            param_2[5] = (int)uVar3;
            param_2[0] = iVar1 + iVar4;
            param_2[2] = (int)(uVar3 - iVar4);
            uVar3 = param_4;
        }
        if (uVar3 <= param_4) goto L877a8;
    }
    uVar3 = param_4;
  L877a8:
    FUN_00086c44(param_2[0], param_3, uVar3);
    param_2[2] = param_2[2] - uVar3;
    param_2[0] = param_2[0] + uVar3;
    return 0;
  L877d8:
    *param_1 = 0xc;
    *(unsigned short*)((char*)param_2+0xc) |= 0x40;
    return 0xffffffff;
}
