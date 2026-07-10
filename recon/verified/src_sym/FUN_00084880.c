/* Reconstructed FUN_00084880 @ 0x84880  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void *a, int b, unsigned int c);
extern void FUN_00084840(unsigned int a, void *b);

void FUN_00084880(unsigned int param_1, int *param_2)
{
    unsigned char local_24[20];
    int iVar1 = *param_2;
    if (iVar1 != 0) {
        memset_bytes(local_24, 0, 0x14);
        local_24[0] = 4;
        *(int*)(local_24+4) = iVar1;
        FUN_00084840(param_1, local_24);
        *param_2 = 0;
    }
}

