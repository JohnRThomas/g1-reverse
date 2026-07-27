#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00030528 @ 0x00030528
 * public-name: flash_write_and_verify_blob
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   attr_store_set                           <= FUN_00030178 @ 0x00030178
 *   attr_store_init_sequence                 <= FUN_00030288 @ 0x00030288
 *   flash_write_and_verify_blob              <= FUN_00030528 @ 0x00030528
 *   flash_data_checksum_neg_sum              <= FUN_0007cf34 @ 0x0007cf34
 *   wait_attr_0x4714_clear                   <= FUN_0007cfac @ 0x0007cfac
 *   attr_configure_pair                      <= FUN_0007cfdc @ 0x0007cfdc
 *   attr_configure_pair_with_init            <= FUN_0007d02a @ 0x0007d02a
 *   attr_configure_mode3_readback            <= FUN_0007d05e @ 0x0007d05e
 * address symbols (name @ address):
 *   rodata_ff20                              @ 0x0000ff20
 *   rodata_10000                             @ 0x00010000
 */
/* Reconstructed FUN_00030528 @ 0x30528  (parity: 300/300 trials, PROVEN) */
extern int attr_store_set(int a0,int a1,int a2,int a3,int a4);
extern int attr_store_init_sequence(int);
extern unsigned int flash_data_checksum_neg_sum(const unsigned char *, unsigned int, unsigned int);
extern int wait_attr_0x4714_clear(void);
extern int attr_configure_pair(unsigned int, unsigned int);
extern int attr_configure_pair_with_init(int a0,int a1,int a2);
extern int attr_configure_mode3_readback(void *a0,int a1);

int flash_write_and_verify_blob(char *param_1, unsigned int param_2, int param_3, int param_4)
{
    unsigned char *pbVar1, *pbVar2, *pbVar3, *pbVar12;
    unsigned char bVar4;
    unsigned short uVar5;
    int iVar6, iVar7;
    int uVar8;
    unsigned int uVar9, uVar11;
    int *puVar10;
    unsigned int local_1c;

    local_1c = param_2;
    iVar6 = attr_store_set(((unsigned long)&rodata_ff20) /*=0xff20*/, 0x3c00ffff, param_3, param_4, (int)param_1);
    if ((iVar6 == 0) && (iVar6 = attr_store_set(0x4444, ((unsigned long)&rodata_10000) /*=0x10000*/, 0, 0, 0), iVar6 == 0) &&
        (iVar6 = attr_store_set(0x4820, 6, 0, 0, 0), iVar6 == 0) &&
        (*param_1 != 1 || (iVar6 = attr_store_set(0x4794, 0x5a637955, 0, 0, 0), iVar6 == 0))) {
        uVar11 = **(unsigned int**)(param_1 + 0x10);
        iVar6 = attr_store_set(((unsigned long)&rodata_ff20) /*=0xff20*/, 0x3c00f091, 0, 0, 0);
        if ((iVar6 == 0) && (iVar6 = attr_store_set(0x4820, 6, 0, 0, 0), iVar6 == 0) &&
            (*param_1 != 0 || (iVar6 = attr_store_set(0x4794, 0x5a637955, 0, 0, 0), iVar6 == 0))) {
            uVar9 = uVar11 & 0x7f;
            if (uVar9 != 0) uVar9 = 1;
            for (iVar6 = 0; uVar9 + (uVar11 >> 7) != (unsigned int)iVar6; iVar6 = iVar6 + 1) {
                iVar7 = attr_store_set(0x4704, *(int*)(*(int*)(param_1 + 0x10) + 4) + iVar6 * 0x80, 0, 0, 0);
                if (iVar7 != 0) return iVar7;
                iVar7 = attr_store_set(0x4710, 5, 0, 0, 0);
                if (iVar7 != 0) return iVar7;
                iVar7 = attr_store_set(0x472c, 0xf0, 0, 0, 0);
                if (iVar7 != 0) return iVar7;
                iVar7 = attr_store_set(0x4714, 1, 0, 0, 0);
                if (iVar7 != 0) return iVar7;
                iVar7 = wait_attr_0x4714_clear();
                if (iVar7 != 0) return iVar7;
            }
            iVar6 = attr_store_set(0x472c, 0x16, 0, 0, 0);
            if ((iVar6 == 0) && (iVar6 = attr_store_set(0x4820, 4, 0, 0, 0), iVar6 == 0)) {
                pbVar12 = *(unsigned char**)(param_1 + 4);
                uVar9 = *(unsigned int*)(param_1 + 8);
                uVar5 = *(unsigned short*)(param_1 + 0xc);
                uVar11 = attr_store_init_sequence((unsigned char)*param_1);
                if (uVar11 == 0) {
                    for (; uVar11 < uVar9; uVar11 = uVar11 + 4) {
                        iVar6 = attr_configure_pair((uVar5 + uVar11) & 0xffff,
                            ((unsigned int)pbVar12[1] << 0x10) | ((unsigned int)pbVar12[0] << 0x18) |
                            (unsigned int)pbVar12[3] | ((unsigned int)pbVar12[2] << 8));
                        pbVar12 = pbVar12 + 4;
                        if (iVar6 != 0) goto LAB_00030622;
                    }
                    local_1c = attr_store_set(0x4820, 4, 0, 0, 0);
                    if (local_1c == 0) {
                        pbVar12 = *(unsigned char**)(param_1 + 4);
                        uVar11 = *(unsigned int*)(param_1 + 8);
                        iVar6 = attr_store_set(((unsigned long)&rodata_ff20) /*=0xff20*/, 0x3c00f091, 0, 0, 0);
                        if ((iVar6 == 0) && (uVar9 = attr_store_set(0x4820, 4, 0, 0, 0), uVar9 == 0)) {
                            for (; uVar9 < uVar11; uVar9 = uVar9 + 4) {
                                iVar6 = attr_configure_mode3_readback(&local_1c, (*(int*)(param_1 + 0xc) + uVar9) & 0xffff);
                                if (iVar6 != 0) goto LAB_00030622;
                                pbVar1 = pbVar12 + 1; bVar4 = *pbVar12; pbVar2 = pbVar12 + 3;
                                pbVar3 = pbVar12 + 2; pbVar12 = pbVar12 + 4;
                                if ((((unsigned int)*pbVar1 << 0x10) | ((unsigned int)bVar4 << 0x18) |
                                     (unsigned int)*pbVar2 | ((unsigned int)*pbVar3 << 8)) != local_1c)
                                    goto LAB_00030622;
                            }
                            iVar6 = attr_configure_pair_with_init(*(unsigned short*)(*(int*)(param_1 + 0x10) + 8), 0x20222022, (unsigned char)*param_1);
                            if (iVar6 == 0) {
                                puVar10 = *(int**)(param_1 + 0x10);
                                uVar8 = flash_data_checksum_neg_sum(*(int*)(param_1 + 4), *(int*)(param_1 + 8), *puVar10);
                                iVar6 = attr_configure_pair_with_init(*(unsigned short*)(puVar10 + 3), uVar8, (unsigned char)*param_1);
                                if (iVar6 == 0) {
                                    if (*param_1 != 1) return 0;
                                    iVar6 = attr_store_set(0x4794, 0, 0, 0, 0);
                                    return iVar6;
                                }
                            }
                        }
                    }
                }
LAB_00030622:
                iVar6 = -1;
            }
        }
    }
    return iVar6;
}
