/* Reconstructed FUN_0007c8e8 @ 0x7c8e8  (parity: 300/300 trials, PROVEN) */

/* 0x7c8ec `movs r3,#1` supplies BOTH the register index (via `mov r1,r3`)
 * and the read LENGTH; 0x257ec `cbz r3` rejects a zero one and forwards it
 * as the i2c_msg len.  Fixed in recon/app/src in iteration 32; these mirrors
 * were never synced (iteration 38). */
extern unsigned int FUN_000257ec(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

unsigned int FUN_0007c8e8(unsigned int param_1, int param_2)
{
    if (param_2 != 0) {
        return FUN_000257ec(param_1, 1, param_2, 1);
    }
    return 0xffffffea;
}

