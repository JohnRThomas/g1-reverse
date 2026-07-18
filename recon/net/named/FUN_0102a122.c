/* readable reconstruction; identity: FUN_0102a122 @ 0x0102a122
 * public-name: FUN_0102a122
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_conn_window_admit                    <= FUN_010231c8 @ 0x010231c8
 */
/* net-core FUN_0102a122 @ 0x102a122  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void *FUN_01021ac0(void);
extern int FUN_010219c4(char *a);
extern int sdc_conn_window_admit(unsigned char a, void *b);
extern void FUN_010256dc(unsigned int a, unsigned int b);

unsigned int FUN_0102a122(unsigned int param_1, char *param_2)
{
    unsigned char *puVar1;
    int iVar2;
    unsigned char bVar7;
    unsigned char uVar5;
    unsigned short uVar6;
    unsigned int uVar4;

    puVar1 = (unsigned char *)FUN_01021ac0();
    if (puVar1 == 0) {
        return 0xfffffffe;
    }
    bVar7 = puVar1[0x26];
    if ((unsigned int)(bVar7 - 1) > 1u) {
        return 0xffffffdd;
    }
    if (param_2 == 0) {
        return 0xffffffea;
    }
    iVar2 = FUN_010219c4(param_2);
    if (iVar2 == 0) {
        return 0xffffffea;
    }

    if (*param_2 == 0) {
        puVar1[0xb] = 0;
        *puVar1 = 1;
        if (param_2[4] == 0) {
            uVar6 = 0x2b;
        } else {
            uVar6 = 0;
        }
        *(volatile unsigned short *)(puVar1 + 8) = uVar6;
        if (param_2[5] == 0) {
            uVar5 = 2;
        } else {
            uVar5 = 3;
        }
        puVar1[10] = uVar5;
        *(volatile int *)(puVar1 + 4) = *(int *)(param_2 + 8) + 0x73;
        *(volatile unsigned int *)(puVar1 + 0x10) = *(unsigned int *)(param_2 + 0xc);
        uVar5 = 3;
        puVar1[0x26] = uVar5;
        iVar2 = sdc_conn_window_admit(puVar1[0x27], puVar1);
        if (iVar2 == 0) {
            FUN_010256dc(0x6a, 0x2b1);
            goto AFTER_PANIC;
        }
        return 0;
    } else {
        if (bVar7 != 2) {
            return 0xffffffdd;
        }
        goto BVAR7_2_BLOCK;
    }

AFTER_PANIC:
BVAR7_2_BLOCK:
    if (bVar7 != 2) {
        return 0xffffffdd;
    }
    {
        unsigned char b7 = bVar7;
        *puVar1 = 0;
        puVar1[0xb] = 0;
        if (param_2[4] == 0) {
            uVar6 = 0x2b;
        } else {
            uVar6 = 0;
        }
        *(volatile unsigned short *)(puVar1 + 8) = uVar6;
        if (param_2[5] != 0) {
            b7 = 3;
        }
        puVar1[10] = b7;
        uVar4 = *(unsigned int *)(param_2 + 8);
        *(volatile int *)(puVar1 + 4) = *(int *)(param_2 + 0xc) + 0x73;
        {
            uint32_t low = *(volatile uint32_t *)(puVar1 + 0x18);
            int32_t high = *(volatile int32_t *)(puVar1 + 0x1c);
            uint32_t sum = low + uVar4;
            high += (int32_t)uVar4 >> 31;
            high += sum < low;
            *(volatile uint32_t *)(puVar1 + 0x10) = sum;
            *(volatile int32_t *)(puVar1 + 0x14) = high;
        }
        puVar1[0x26] = (unsigned char)(bVar7 + 2);
        iVar2 = sdc_conn_window_admit(puVar1[0x27], puVar1);
        if (iVar2 == 0) {
            FUN_010256dc(0x6a, 0x2b1);
            goto BVAR7_2_BLOCK;
        }
        return 0;
    }
}
