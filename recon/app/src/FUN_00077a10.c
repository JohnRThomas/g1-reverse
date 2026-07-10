/* Reconstructed FUN_00077a10 @ 0x77a10  (parity: 300/300 trials, PROVEN) */

typedef unsigned char byte;
typedef unsigned long long u64;
extern u64 strtoll_internal(void *reent, byte *s, void *endptr, void *base_tab);
u64 FUN_00077a10(byte *param_1, void *param_2) {
    void *r = *(void **)0x20002d20;
    return strtoll_internal(r, param_1, param_2, (void *)0x20002d84);
}

