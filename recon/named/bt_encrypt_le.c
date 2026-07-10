/* named: bt_encrypt_le */
/* Reconstructed bt_encrypt_le @ 0x81326  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void safe_memmove_or_die(void*, int);
extern int tc_aes128_set_encrypt_key(void*, void*);
extern int tc_aes_encrypt(int, void*, void*);
unsigned bt_encrypt_le(int param_1, int param_2, int param_3){
    unsigned char auStack_d0[16];
    unsigned char auStack_c0[180];
    if (param_1 != 0 && param_2 != 0 && param_3 != 0){
        safe_memmove_or_die(auStack_d0, param_1);
        int iVar2 = tc_aes128_set_encrypt_key(auStack_c0, auStack_d0);
        if (iVar2 != 0){
            safe_memmove_or_die(auStack_d0, param_2);
            iVar2 = tc_aes_encrypt(param_3, auStack_d0, auStack_c0);
            if (iVar2 != 0){
                unsigned char *puVar4 = (unsigned char*)(param_3 - 1);
                unsigned char *puVar3 = (unsigned char*)(param_3 + 0x10);
                do {
                    puVar4 = puVar4 + 1;
                    unsigned char uVar1 = *puVar4;
                    puVar3 = puVar3 - 1;
                    *puVar4 = *puVar3;
                    *puVar3 = uVar1;
                } while (puVar4 != (unsigned char*)(param_3 + 7));
                return 0;
            }
        }
    }
    return 0xffffffea;
}

