/* named: gatt_hash_settings_set */
/* Reconstructed gatt_hash_settings_set @ 0x5a28c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00082a42(unsigned int a, unsigned int b, void *c);
typedef int (*fn_t)(unsigned int, unsigned int, unsigned int);

int gatt_hash_settings_set(unsigned int param_1, unsigned int param_2, fn_t param_3, unsigned int param_4)
{
    int iVar1;
    unsigned int local_20;
    unsigned int local_1c;
    int iStack_18;

    iVar1 = param_3(param_4, 0x20006390UL, 0x10);
    if (iVar1 < 0) {
        local_1c = 0x000f4783UL;
        local_20 = 3;
        iStack_18 = iVar1;
        FUN_00082a42(0x00088128UL, 0x1840, &local_20);
        return iVar1;
    } else {
        return 0;
    }
}

