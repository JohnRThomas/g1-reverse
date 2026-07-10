/* Reconstructed FUN_00082bd4 @ 0x82bd4  (parity: 300/300 trials, PROVEN) */

extern int FUN_0008256e(void);
extern void *FUN_00059c04(int a);
extern void set_change_aware(void *a, int b);
extern void *FUN_00059bcc(unsigned char a, int b);
extern int FUN_0005a0e8(void *a);

void sc_restore_rsp(int param_1, unsigned int param_2, int param_3, unsigned int param_4)
{
    int iVar1;
    unsigned char *puVar2;

    iVar1 = FUN_0008256e();
    if (iVar1 != 0) {
        void *r = FUN_00059c04(param_1);
        if (r != 0) {
            if ((int)((unsigned int)(*(volatile unsigned char *)((int)r + 8)) << 0x1f) < 0) {
                set_change_aware(r, 1);
            }
        }
    }
    if (param_3 == 0) {
        puVar2 = FUN_00059bcc(*(volatile unsigned char *)(param_1 + 8), param_1 + 0x90);
        if (puVar2 != 0) {
            *(volatile int *)(puVar2 + 8) = param_3;
            FUN_0005a0e8(puVar2);
            return;
        }
    }
}

