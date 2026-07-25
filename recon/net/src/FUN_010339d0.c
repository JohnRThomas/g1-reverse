/* P4 iteration 26 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_21004a60[];
#define G1N_21004a60 ((unsigned long)(g1_net_ram_blk_21004a60 + 0x0))
#else
#define G1N_21004a60 0x21004a60ul
#endif
/* Pinned NCS ESB TX FIFO capacity query @ 0x010339d0.
 * Raw back-map: FUN_010339d0@0x010339d0; true extent 0x0e.
 * Public identity: esb_tx_full.
 */
#include <stdbool.h>
#include <stdint.h>

#define esb_tx_full FUN_010339d0

bool esb_tx_full(void)
{
    volatile uint32_t *const tx_fifo =
        (volatile uint32_t *)G1N_21004a60;
    return tx_fifo[0x28 / 4] > 7u;
}
