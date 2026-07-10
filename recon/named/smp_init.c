/* named: smp_init */
/* Reconstructed smp_init @ 0x5cc30  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void *a, int b, unsigned int c, unsigned int d, unsigned int e);
extern int bt_rand(unsigned int a, unsigned int b);
extern void atomic_set_bit(void *a, unsigned int b);
extern unsigned int bt_pub_key_get(void);

unsigned int smp_init(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar2;
    memset_bytes((void*)param_1, 0, 0xf0, param_4, param_4);
    int iVar1 = bt_rand(param_1+0x27, 0x10);
    if (iVar1 == 0) {
        atomic_set_bit((void*)param_1, 5);
        uVar2 = bt_pub_key_get();
        *(volatile unsigned int*)0x2000af48UL = uVar2;
        uVar2 = 0;
    } else {
        uVar2 = 8;
    }
    return uVar2;
}

