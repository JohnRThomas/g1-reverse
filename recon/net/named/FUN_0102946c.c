/* readable reconstruction; identity: FUN_0102946c @ 0x0102946c
 * public-name: FUN_0102946c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* Reconstructed internal net function FUN_0102946c @ 0x0102946c.
 * Exact owned extent is [0x0102946c,0x010294a2), 54 bytes; the caller wrapper
 * begins immediately at 0x010294a2. */
#include <stdint.h>

extern unsigned FUN_0101f8cc(void);
extern void *FUN_01009d18(uint16_t handle, unsigned type);
extern void *FUN_0101e090(void);
extern unsigned FUN_0101e15c(void *context, void *entry, uint8_t value);

unsigned FUN_0102946c(uint16_t handle, uint8_t value)
{
    if ((int32_t)(FUN_0101f8cc() << 2) >= 0)
        return 0x0c;

    void *entry = FUN_01009d18(handle, 8);
    if (entry == 0)
        return 2;

    void *context = FUN_0101e090();
    if (context == 0)
        return 0x0c;

    return FUN_0101e15c(context, entry, value);
}
