/* named: nvs_write */
/* Reconstructed nvs_write @ 0x4c8f8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern unsigned k_mutex_lock(int,...);
extern unsigned k_mutex_unlock(int,...);
extern unsigned nvs_sector_advance(int,...);
extern unsigned nvs_flash_block_cmp(int,...);
extern unsigned nvs_ate_crc8_update(int,...);
extern unsigned nvs_log_err(int,...);
extern unsigned nvs_al_size(int,...);
extern unsigned nvs_ate_valid(int,...);
extern unsigned nvs_prev_ate(int,...);
extern unsigned nvs_flash_al_wrt(int,...);
extern unsigned nvs_flash_ate_wrt(int,...);
extern unsigned nvs_gc(int,...);

unsigned nvs_write(int param_1, unsigned param_2, int param_3, unsigned param_4)
{
    unsigned uVar1, uVar3, uVar5, uVar6;
    int iVar2;
    unsigned local_4c;
    unsigned short local_48, local_46, local_44;
    unsigned short local_40;
    short local_3e;
    unsigned short local_3c;
    unsigned char local_3a;
    unsigned local_30, local_2c;

    if (*(char *)(param_1 + 0x10) == 0) {
        uVar5 = 0xfffffff3;
        local_2c = 0x000f0ae4;
        local_30 = 2;
        nvs_log_err(0x000881b8, 0x1040, (int)&local_30);
    } else {
        int p2c = *(int *)(param_1 + 0x2c);
        iVar2 = nvs_al_size(p2c, 8);
        uVar3 = nvs_al_size(p2c, param_4);
        if (((unsigned)*(unsigned short *)(param_1 + 0xc) + iVar2 * -4 < param_4) ||
            ((param_4 != 0) && (param_3 == 0))) {
            uVar5 = 0xffffffea;
        } else {
            local_4c = *(unsigned *)(param_1 + 4);
            do {
                uVar5 = local_4c;
                unsigned r = nvs_prev_ate(param_1, (int)&local_4c, (int)&local_48);
                if (r != 0) return r;
                if (local_48 == (unsigned short)param_2) {
                    r = nvs_ate_valid(param_1, (int)&local_48);
                    if ((int)r != 0) {
                        if (param_4 == 0) {
                            if (local_44 == 0) return 0;
                        } else if (local_44 == param_4) {
                            r = nvs_flash_block_cmp(param_1, (uVar5 & 0xffff0000) + (unsigned)local_46, param_3, param_4);
                            if ((int)r < 1) return r;
                        }
                        goto LAB_0004c9ba;
                    }
                }
            } while (*(unsigned *)(param_1 + 4) != local_4c);
            uVar5 = 0;
            if (param_4 != 0) {
LAB_0004c9ba:
                if (uVar3 != 0) uVar3 = (uVar3 + iVar2) & 0xffff;
                k_mutex_lock(param_1 + 0x14, 0, 0xffffffff, 0xffffffff);
                uVar1 = 0xffff0000;
                for (uVar6 = 0; uVar6 != *(unsigned short *)(param_1 + 0xe); uVar6 = uVar6 + 1) {
                    uVar5 = *(unsigned *)(param_1 + 4);
                    if (uVar3 + *(int *)(param_1 + 8) <= uVar5) {
                        local_3e = (short)*(int *)(param_1 + 8);
                        local_3a = 0xff;
                        local_40 = (unsigned short)param_2;
                        local_3c = (unsigned short)param_4;
                        nvs_ate_crc8_update((int)&local_40);
                        uVar5 = nvs_flash_al_wrt(param_1, *(unsigned *)(param_1 + 8), param_3, param_4);
                        iVar2 = nvs_al_size(*(int *)(param_1 + 0x2c), param_4);
                        *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + iVar2;
                        if ((uVar5 == 0) && (uVar5 = nvs_flash_ate_wrt(param_1, (int)&local_40), uVar5 == 0)) {
                            uVar5 = param_4;
                        }
                        goto LAB_0004ca30;
                    }
                    iVar2 = nvs_al_size(*(int *)(param_1 + 0x2c), 8);
                    local_40 = 0xffff;
                    local_3a = 0xff;
                    local_3c = 0;
                    local_3e = (short)uVar5 + (short)iVar2;
                    *(unsigned *)(param_1 + 4) = ((uVar5 & uVar1) + (unsigned)*(unsigned short *)(param_1 + 0xc)) - iVar2;
                    nvs_ate_crc8_update((int)&local_40);
                    nvs_flash_ate_wrt(param_1, (int)&local_40);
                    nvs_sector_advance(param_1, param_1 + 4);
                    *(unsigned *)(param_1 + 8) = *(unsigned *)(param_1 + 4) & uVar1;
                    uVar5 = nvs_gc(param_1);
                    if (uVar5 != 0) goto LAB_0004ca30;
                }
                uVar5 = 0xffffffe4;
LAB_0004ca30:
                k_mutex_unlock(param_1 + 0x14);
            }
        }
    }
    return uVar5;
}

