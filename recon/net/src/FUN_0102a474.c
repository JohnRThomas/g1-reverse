/* P4 iteration 30 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_210045e0[];
extern unsigned char g1_net_ram_blk_21004b30[];
extern unsigned char g1_net_ram_blk_21004c98[];
#define G1N_210045e4 ((unsigned long)(g1_net_ram_blk_210045e0 + 0x4))
#define G1N_21004b9f ((unsigned long)(g1_net_ram_blk_21004b30 + 0x6f))
#define G1N_21004c9c ((unsigned long)(g1_net_ram_blk_21004c98 + 0x4))
#else
#define G1N_210045e4 0x210045e4ul
#define G1N_21004b9f 0x21004b9ful
#define G1N_21004c9c 0x21004c9cul
#endif
/* net-core FUN_0102a474 @ 0x0102a474  (P4 iteration 30, NEW reconstruction)
 * Readable identity: g1_esb_pending_frame_clear.
 *
 * Raw back-map: runtime 0x0102ac74..0x0102ac98 (analysis 0x0102a474).  The
 * exact inverse of FUN_0102a448 (the app->net sync-frame staging entry): it
 * wipes the 252-byte staging buffer 0x21004b9f, clears the staged length
 * 0x210045e4 that FUN_0102a468 reports to the announce builder FUN_0102b3f0,
 * and clears the ESB receive-ready flag 0x21004c9c.  Called by the ESB worker
 * thread FUN_0102b204 immediately before it relays {0x0d, 0x02} to the app.
 */
#include <stdint.h>

extern void FUN_0103b62e(void *destination, int value, unsigned int length);

void FUN_0102a474(void)
{
    FUN_0103b62e((void *)G1N_21004b9f, 0, 0xfcu);
    *(volatile uint32_t *)G1N_210045e4 = 0;
    *(volatile uint8_t *)G1N_21004c9c = 0;
}
