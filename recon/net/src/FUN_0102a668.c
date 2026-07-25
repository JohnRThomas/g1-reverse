/* P4 iteration 30 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_21000570[];
extern unsigned char g1_net_ram_blk_210045b0[];
#define G1N_21000580 ((unsigned long)(g1_net_ram_blk_21000570 + 0x10))
#define G1N_210045b0 ((unsigned long)(g1_net_ram_blk_210045b0 + 0x0))
#else
#define G1N_21000580 0x21000580ul
#define G1N_210045b0 0x210045b0ul
#endif
/* net-core FUN_0102a668 @ 0x0102a668  (P4 iteration 30, NEW reconstruction)
 * Readable identity: g1_esb_uplink_msgq_init.
 *
 * Raw back-map: runtime 0x0102ae68..0x0102ae98 (analysis 0x0102a668):
 *     r0 = 0x210045b0, r1 = 251, r2 = 4  ->  bl 0x0103b98c
 * i.e. k_msgq_alloc_init(&queue, msg_size = 0xfb, max_msgs = 4).  The 40-byte
 * relocation block at 0x210045b0 is EXACTLY sizeof(struct k_msgq) for this
 * configuration and the recovered field offset confirms it: both existing
 * accessors FUN_0102a698 (put) and FUN_0102a6e0 (get) gate on
 * `*(int *)(0x210045b0 + 0x10) == 0`, which is `buffer_start` -- the field
 * k_msgq_alloc_init fills in.  Until this ran, both accessors returned 1 and
 * the ESB uplink queue was permanently empty.
 *
 * Called exactly once, from the ESB worker thread FUN_0102b204's prologue.
 * 251 * 4 = 1004 bytes come from the thread resource pool, i.e. the system
 * heap whose shipped size (2560 B, measured in iteration 29 SS29.3) is what
 * makes this allocation fit.
 */
#include <stdint.h>

#ifdef G1_COHESIVE_BUILD
#include <zephyr/kernel.h>
#define FUN_0103b18c(queue, msg_size, max_msgs) \
    k_msgq_alloc_init((struct k_msgq *)(uintptr_t)(queue), (msg_size), \
                      (max_msgs))
#else
extern int FUN_0103b18c(unsigned long queue, unsigned int msg_size,
                        unsigned int max_msgs);
#endif
extern void FUN_01039722(const char *format, ...);

int FUN_0102a668(void)
{
    int status = FUN_0103b18c(G1N_210045b0, 0xfbu, 4u);

    if (status != 0 && *(volatile int32_t *)G1N_21000580 > 0) {
        FUN_01039722((const char *)0x0103cd31u);
    }
    return status;
}
