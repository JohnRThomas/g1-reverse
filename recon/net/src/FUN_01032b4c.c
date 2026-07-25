/* net-core FUN_01032b4c @ 0x1032b4c  (P4 iteration 23)
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
 *   emu.compare(orig, 0x1032b4c, 0x52, cand, code_base=NET_CODE_BASE,
 *               trials=300, no_return=True, call_arities=None)
 *   -> pass True, checked 300, mismatches 0
 * CFG_VERIFY_CALL_ARITIES=
 */
/* net-core ESB RADIO packet configuration @ analysis 0x01032b4c, extent 0x52.
 * Ghidra gap function (the catalogued neighbour FUN_01032ad8 ends at
 * 0x01032b38); recovered because FUN_010333b4 reaches it through the two
 * mode-setup trampolines whose runtime pointers 0x010333a5 / 0x010333e5 it
 * stores into the radio callback slot.
 * Packs a 13-byte descriptor into RADIO.PCNF0 (0x41008514) and
 * RADIO.PCNF1 (0x41008518). */
void FUN_01032b4c(const unsigned char *cfg)
{
    volatile unsigned int *const radio = (volatile unsigned int *)0x41008000u;
    unsigned int v;

    v  = (unsigned int)cfg[2] << 16;
    v |= (unsigned int)cfg[1] << 8;
    v |= (unsigned int)cfg[0];
    v |= (unsigned int)cfg[3] << 20;
    v |= (unsigned int)cfg[4] << 22;
    v |= (unsigned int)cfg[5] << 24;
    v |= (unsigned int)cfg[6] << 26;
    v |= (unsigned int)cfg[7] << 29;
    radio[0x514 / 4] = v;

    v  = (unsigned int)cfg[10] << 16;
    v |= (unsigned int)cfg[9] << 8;
    v |= (unsigned int)cfg[8];
    v |= (unsigned int)cfg[11] << 24;
    v |= (unsigned int)cfg[12] << 25;
    radio[0x518 / 4] = v;
}
