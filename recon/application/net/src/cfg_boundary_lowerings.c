/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Strong owner for the sole synthetic CFG-boundary call retained by the
 * differential reconstruction harness.  Original CPUNET instructions at
 * 0x0100d4cc are exactly:
 *
 *     movs r0, #0
 *     bx   lr
 *
 * Keeping this as an out-of-line owner preserves the harness's boundary-call
 * model while giving the integrated image the original C semantics.
 */
unsigned int FUN_shadow_default(void)
{
    return 0;
}
