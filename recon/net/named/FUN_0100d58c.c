/* readable reconstruction; identity: FUN_0100d58c @ 0x0100d58c
 * public-name: FUN_0100d58c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* FUN_0100d58c @ 0x0100d58c: select an operation timing constant. */
#include <stdnoreturn.h>
#include <stdint.h>

extern noreturn void FUN_01008d00(unsigned int module, unsigned int line);

uint32_t FUN_0100d58c(int short_interval, uint32_t operation)
{
    switch (operation) {
    case 1:
        return short_interval == 0 ? 0x4e2u : 0x9c4u;
    case 2:
        return 0x9c4u;
    case 4:
    case 8:
        return 0xea6u;
    default:
        FUN_01008d00(0x29u, 0x270u);
    }
}
