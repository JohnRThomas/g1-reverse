/* P4 iteration 26/27 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_21000570[];
#define G1N_21000580 ((unsigned long)(g1_net_ram_blk_21000570 + 0x10))
#else
#define G1N_21000580 0x21000580ul
#endif
/* net-core FUN_0102b900 @ 0x102b900 */
#include <stdint.h>

extern int FUN_01036198(void *queue, const uint8_t *value,
                        unsigned flags, unsigned timeout);
extern void FUN_01039722(const void *message, int status);

#ifdef G1_COHESIVE_BUILD
struct k_msgq;
extern struct k_msgq g1_timeslot_api_msgq;
#define TIMESLOT_API_QUEUE ((void *)&g1_timeslot_api_msgq) /*=0x210008e0*/
#else
#define TIMESLOT_API_QUEUE ((void *)0x210008e0u)
#endif

#define G1_ARCH_RUNTIME_EXCEPTION(reason) do { \
    __asm__ volatile("eors.n r0, r0\n\t" \
                     "msr basepri, r0\n\t" \
                     "mov r0, %0\n\t" \
                     "svc 2" \
                     : : "I"(reason) : "r0", "memory"); \
} while (0)

int FUN_0102b900(uint32_t value)
{
    uint8_t byte = (uint8_t)value;
    int status = FUN_01036198(TIMESLOT_API_QUEUE, &byte, 0, 0);
    register unsigned int exception_r1 __asm__("r1");

    if (status == 0)
        return 0;

    if (*(volatile int *)G1N_21000580 > 0)
        FUN_01039722((const void *)0x0103d23bu, status);

    exception_r1 = (unsigned int)status;
    __asm__ volatile("" : : "r"(exception_r1));
    G1_ARCH_RUNTIME_EXCEPTION(3);
    return status;
}
