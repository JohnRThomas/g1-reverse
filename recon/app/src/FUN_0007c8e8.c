/* Reconstructed FUN_0007c8e8 @ 0x7c8e8  (parity: 300/300 trials, PROVEN)
 *
 * BRING-UP WIRING FIX (P4 iteration 32) -- dropped register argument, the
 * class the parity harness is structurally blind to (the callee is an
 * order-keyed oracle, so an extra register argument it never reads is not
 * compared).  The shipped body is a four-argument tail call:
 *
 *   7c8e8  mov  r2, r1        ; r2 = param_2   (the read buffer)
 *   7c8ea  cbz  r1, 7c8f4
 *   7c8ec  movs r3, #1        ; r3 = 1         <-- THE READ LENGTH
 *   7c8ee  mov  r1, r3        ; r1 = 1         (the 16-bit register index)
 *   7c8f0  b.w  0x257ec       ; FUN_000257ec(dev, 1, buf, 1)
 *
 * `movs r3,#1` supplies BOTH the register index (via `mov r1,r3`) and the
 * length; the reconstruction declared the callee with three parameters and
 * dropped r3.  FUN_000257ec forwards its 4th parameter to FUN_00025740 as the
 * i2c_msg[1].len of an i2c_write_read, so with r3 left holding whatever the
 * previous call returned, `nrfx_twim_xfer` received a length of 0x200305a4
 * (a kernel spinlock address) and tripped
 * NRFX_ASSERT(TWIM_LENGTH_VALIDATE) at nrfx_twim.c:593 -> K_ERR_KERNEL_PANIC.
 * Measured in iteration 32: the ST25DV system-port (0x57) register-1 read.
 */

extern unsigned int FUN_000257ec(unsigned int a, unsigned int b, unsigned int c,
                                 unsigned int d);

unsigned int FUN_0007c8e8(unsigned int param_1, int param_2)
{
    if (param_2 != 0) {
        return FUN_000257ec(param_1, 1, param_2, 1);
    }
    return 0xffffffea;
}
