/* P4 iteration 26 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_21004a60[];
extern unsigned char g1_net_ram_blk_21006458[];
#define G1N_21004a60 ((unsigned long)(g1_net_ram_blk_21004a60 + 0x0))
#define G1N_21006458 ((unsigned long)(g1_net_ram_blk_21006458 + 0x0))
#else
#define G1N_21004a60 0x21004a60ul
#define G1N_21006458 0x21006458ul
#endif
/* Pinned NCS ESB transmission start @ 0x01033858.
 * Raw back-map: FUN_01033858@0x01033858; true extent 0x26.
 * Public identity: esb_start_tx.
 * CFG_VERIFY_CALL_ARITIES=1
 */
#include <stdint.h>

extern void FUN_01032c28(void);

#define esb_start_tx_transaction FUN_01032c28
#define esb_start_tx             FUN_01033858

int esb_start_tx(void)
{
    volatile uint8_t *const esb_state =
        (volatile uint8_t *)G1N_21006458;
    volatile uint32_t *const tx_fifo =
        (volatile uint32_t *)G1N_21004a60;

    if (*esb_state != 0)
        return -16;
    if (tx_fifo[0x28 / 4] == 0)
        return -61;
    esb_start_tx_transaction();
    return 0;
}
