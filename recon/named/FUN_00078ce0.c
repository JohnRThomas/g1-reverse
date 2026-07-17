/* readable reconstruction; identity: FUN_00078ce0 @ 0x00078ce0
 * public-name: FUN_00078ce0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __assert_func                            <= FUN_00076a94 @ 0x00076a94
 *   Balloc                                   <= FUN_000785d4 @ 0x000785d4
 *   clz32                                    <= FUN_00087510 @ 0x00087510
 *   ctz32_normalize_inplace                  <= FUN_00087554 @ 0x00087554
 * address symbols (name @ address):
 *   rodata_f8c42                             @ 0x000f8c42
 *   rodata_f8cd5                             @ 0x000f8cd5
 */
/* Reconstructed FUN_00078ce0 @ 0x78ce0  (parity: 300/300 trials, PROVEN) */

extern int __assert_func(unsigned a, unsigned b, int c, unsigned d);
extern int Balloc(unsigned a, int b);
extern int clz32(unsigned a);
extern int ctz32_normalize_inplace(void*a);
int FUN_00078ce0(unsigned a0, unsigned a1, unsigned a2, double input){
    union { double value; struct { unsigned lo, hi; } words; } bits = { input };
    unsigned lo = bits.words.lo, hi = bits.words.hi;
    int iVar1 = Balloc(a0, 1);
    if (iVar1 == 0) __assert_func(0x000f8cd5, 0x30a, 0, 0x000f8c42);
    unsigned uVar6 = (hi >> 20) & 0x7ff;
    unsigned mant = hi & 0xfffff;
    if (uVar6 != 0) mant |= 0x100000;
    unsigned uVar2, iVar4;
    if (lo == 0){
        unsigned tmp = mant;
        int r = ctz32_normalize_inplace(&tmp);
        uVar2 = (unsigned)r + 0x20;
        iVar4 = 1;
        *(volatile unsigned*)(iVar1 + 0x14) = tmp;
        mant = tmp;
    } else {
        unsigned buf[2]; buf[0] = lo; buf[1] = mant;
        int r = ctz32_normalize_inplace(buf);
        uVar2 = (unsigned)r;
        unsigned l1 = buf[0]; unsigned l2 = buf[1];
        if (uVar2 == 0){
            *(volatile unsigned*)(iVar1 + 0x14) = l1;
            mant = l2;
        } else {
            unsigned uVar5 = l2 << ((0x20 - uVar2) & 0xff);
            mant = l2 >> (uVar2 & 0xff);
            *(volatile unsigned*)(iVar1 + 0x14) = uVar5 | l1;
        }
        *(volatile unsigned*)(iVar1 + 0x18) = mant;
        iVar4 = (mant == 0) ? 1 : 2;
    }
    *(volatile int*)(iVar1 + 0x10) = (int)iVar4;
    int iVar3;
    if (uVar6 == 0){
        *(volatile int*)a1 = (int)(uVar2 - 0x432);
        int t = clz32(*(volatile unsigned*)(iVar1 + iVar4*4 + 0x10));
        iVar3 = (int)iVar4 * 0x20 - t;
    } else {
        iVar3 = 0x35 - (int)uVar2;
        *(volatile int*)a1 = (int)((uVar6 - 0x433) + uVar2);
    }
    *(volatile int*)a2 = iVar3;
    return iVar1;
}
