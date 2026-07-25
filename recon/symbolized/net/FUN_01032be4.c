#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01032be4 @ 0x01032be4
 * public-name: FUN_01032be4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_crc_scratch                  @ 0x21000684
 */
/* net-core FUN_01032be4 @ 0x1032be4  (P4 iteration 23; symbolized)
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
 *   emu.compare(orig, 0x1032be4, 0x44, cand, code_base=NET_CODE_BASE,
 *               trials=300, no_return=True, call_arities=(1,))
 *   -> pass True, checked 300, mismatches 0
 * CFG_VERIFY_CALL_ARITIES=1
 */
/* net-core ESB RADIO mode-1 packet setup @ analysis 0x01032be4, extent 0x44.
 * Stored as runtime Thumb pointer 0x010333e5 by FUN_010333b4 when the recovered
 * config byte saved[0] == 1.  The incoming argument is not used. */
extern void FUN_01032b4c(const unsigned char *cfg);

void FUN_01032be4(unsigned int unused)
{
    unsigned char cfg[13];

    (void)unused;
    *(unsigned int *)(cfg + 9) = 0u;
    *(unsigned int *)(cfg + 1) = 0u;
    *(unsigned int *)(cfg + 5) = 0u;
    cfg[2]  = 3;
    cfg[0]  = 8;
    cfg[11] = 1;
    cfg[10] = (unsigned char)(((const volatile unsigned char *)&g_net_radio_crc_scratch) /*=0x21000684*/ [17] - 1);
    cfg[8]  = 0xfb;
    FUN_01032b4c(cfg);
}
