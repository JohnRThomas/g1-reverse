/* readable reconstruction; identity: FUN_010380d8 @ 0x010380d8
 * public-name: FUN_010380d8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 */
/* net-core FUN_010380d8 @ 0x10380d8 */
#include <stdint.h>

extern int FUN_0103610c(void *lock);
extern void FUN_01036144(void *lock);
extern int FUN_01036128(void *lock);
extern void FUN_01037f54(void *timer);
extern void FUN_01039bbe(const void *module, const void *file, unsigned line);
extern void FUN_01039bb0(const void *file, unsigned line);

int FUN_010380d8(uint32_t *timer)
{
    /* Original body uses BASEPRI=0x40 around the scheduler lock operation. */
    void *const lock = (void *)0x21004b70u;
    int result;

    if (FUN_0103610c(lock) == 0) {
        FUN_01039bbe((const void *)0x0103d2a7u,
                     (const void *)0x0103d3b6u, 0x72);
        FUN_01039bb0((const void *)0x0103d3b6u, 0x72);
        return -1;
    }

    FUN_01036144(lock);
    if (*timer == 0) {
        result = -22;
    } else {
        FUN_01037f54(timer);
        result = 0;
    }

    if (FUN_01036128(lock) == 0) {
        FUN_01039bbe((const void *)0x0103d2a7u,
                     (const void *)0x0103d3b6u, 0xf0);
        FUN_01039bb0((const void *)0x0103d3b6u, 0xf0);
    }
    return result;
}
