/* net-core FUN_01032ba4 @ 0x1032ba4  (P4 iteration 23)
 *
 * Recovered from a GHIDRA GAP: the catalogued neighbour FUN_01032ad8 ends at
 * 0x01032b38 and the next catalogued entry is FUN_01032c28, so 0x01032b4c,
 * 0x01032ba4 and 0x01032be4 were never catalogued and net_recon_kit.prove()'s
 * identity gate rejects them ("name/address does not match net catalog").
 *
 * They are reached ONLY through the two runtime Thumb pointers 0x010333a5 and
 * 0x010333e5 that FUN_010333b4 stores into the radio callback slot and then
 * calls -- i.e. exactly the "net residual 1 (interior address inside
 * FUN_010333b4)" that commit 0a7dee8c could not rebind because no defined
 * symbol existed for them.  Runtime->analysis is -0x800:
 *     0x010333a5 -> analysis 0x01032ba4    0x010333e5 -> analysis 0x01032be4
 * Both land on a real `push {r0, r1, r2, r3, r4, lr}` prologue after a literal
 * pool, so they are genuine function entries, not interior labels.
 *
 * PROOF.  All three are BRANCH-FREE straight-line code -- no conditional
 * branch, no cbz/cbnz, no tbb/tbh -- so cfg_verify's contribution (deriving
 * inputs from the CFG so every branch/case is exercised) is vacuous, and 300
 * randomized trials through the same tools/parity/emu.py differential harness
 * are complete coverage.  Measured:
 *   emu.compare(orig, 0x1032ba4, 0x40, cand, code_base=NET_CODE_BASE,
 *               trials=300, no_return=True, call_arities=(3,1))
 *   -> pass True, checked 300, mismatches 0
 * CFG_VERIFY_CALL_ARITIES=3,1
 */
/* net-core ESB RADIO mode-0 packet setup @ analysis 0x01032ba4, extent 0x40.
 * Stored as runtime Thumb pointer 0x010333a5 by FUN_010333b4 when the recovered
 * config byte saved[0] == 0. */
extern void FUN_0103b62e(void *dst, int value, unsigned int len);
extern void FUN_01032b4c(const unsigned char *cfg);

void FUN_01032ba4(unsigned int length)
{
    unsigned char cfg[13];

    FUN_0103b62e(cfg, 0, 13);
    *(unsigned int *)cfg = 0x00010100u;
    cfg[8]  = (unsigned char)length;
    cfg[9]  = (unsigned char)length;
    cfg[10] = (unsigned char)(*(volatile unsigned char *)(0x21000684u + 17) - 1);
    cfg[11] = 1;
    FUN_01032b4c(cfg);
}
