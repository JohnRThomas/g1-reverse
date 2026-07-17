/* readable reconstruction; identity: FUN_01036c2c @ 0x01036c2c
 * public-name: FUN_01036c2c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103eaed                           @ 0x0103eaed
 */
/* net-core FUN_01036c2c @ 0x1036c2c */
#include <stdint.h>

extern void assert_print(uintptr_t file, uintptr_t message, unsigned line);
extern void FUN_01039bb0(uintptr_t message, unsigned line);
extern int FUN_0103610c(void *lock);
extern void FUN_01036144(void *lock);
extern int FUN_01036128(void *lock);
extern int FUN_01036b18(void *object, unsigned int *values,
                        unsigned int third, unsigned int priority);

int FUN_01036c2c(unsigned int value, void *object,
                 unsigned int third, unsigned int fourth)
{
    void *lock = (void *)0x21004b58;
    unsigned int values[2] = { value, third };
    int result;

    (void)fourth;

    if (object == 0) {
        assert_print(0x0103d2a7, 0x0103eaed, 0x174);
        FUN_01039bb0(0x0103eaed, 0x174);
    }
    if (!FUN_0103610c(lock)) {
        assert_print(0x0103d2a7, 0x0103d3b6, 0x72);
        FUN_01039bb0(0x0103d3b6, 0x72);
    }
    FUN_01036144(lock);
    result = FUN_01036b18(object, values, third, 0x40);
    if (!FUN_01036128(lock)) {
        assert_print(0x0103d2a7, 0x0103d3b6, 0xf0);
        FUN_01039bb0(0x0103d3b6, 0xf0);
    }
    return result;
}
