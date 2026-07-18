#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01036c2c @ 0x01036c2c
 * public-name: z_work_submit_to_queue
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   submit_to_queue_locked                   <= FUN_01036b18 @ 0x01036b18
 *   z_work_submit_to_queue                   <= FUN_01036c2c @ 0x01036c2c
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103eaed                           @ 0x0103eaed
 */
/* net-core FUN_01036c2c @ 0x1036c2c */
#include <stdint.h>

extern void assert_print(uintptr_t file, uintptr_t message, unsigned line);
extern void assert_post_action(uintptr_t message, unsigned line);
extern int FUN_0103610c(void *lock);
extern void FUN_01036144(void *lock);
extern int FUN_01036128(void *lock);
extern int submit_to_queue_locked(void *object, unsigned int *values,
                        unsigned int third, unsigned int priority);

int z_work_submit_to_queue(unsigned int value, void *object,
                 unsigned int third, unsigned int fourth)
{
    void *lock = (void *)0x21004b58;
    unsigned int values[2] = { value, third };
    int result;

    (void)fourth;

    if (object == 0) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eaed) /*=0x103eaed*/, 0x174);
        assert_post_action(((unsigned long)&rodata_103eaed) /*=0x103eaed*/, 0x174);
    }
    if (!FUN_0103610c(lock)) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
        assert_post_action(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
    }
    FUN_01036144(lock);
    result = submit_to_queue_locked(object, values, third, 0x40);
    if (!FUN_01036128(lock)) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
        assert_post_action(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
    }
    return result;
}
