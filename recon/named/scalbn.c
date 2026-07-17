/* readable reconstruction; identity: FUN_000870ea @ 0x000870ea
 * public-name: scalbn
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __muldf3                                 <= FUN_0000d8f8 @ 0x0000d8f8
 *   scalbn                                   <= FUN_000870ea @ 0x000870ea
 */
/* Reconstructed FUN_000870ea @ 0x870ea  (parity: 300/300 trials, PROVEN) */

extern double FUN_00078bf8(double value);
extern unsigned long long __muldf3(unsigned int lo, unsigned int hi, unsigned int z, unsigned int newhi);

double scalbn(unsigned int param_1, unsigned int param_2, int param_3)
{
    union { struct { unsigned int lo, hi; } w; double d; } u;
    u.w.lo = param_1;
    u.w.hi = param_2;
    u.d = FUN_00078bf8(u.d);
    if (param_3 != 0) {
        int iVar1 = 0x6b - (int)(((unsigned int)(param_2 << 1)) >> 0x15);
        if (iVar1 > 0) {
            unsigned int newhi = (unsigned int)iVar1 * 0x100000u + 0x3ff00000u;
            unsigned long long r = __muldf3(u.w.lo, u.w.hi, 0, newhi);
            u.w.lo = (unsigned int)r;
            u.w.hi = (unsigned int)(r >> 32);
        }
    }
    return u.d;
}
