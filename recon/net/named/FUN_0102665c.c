/* readable reconstruction; identity: FUN_0102665c @ 0x0102665c
 * public-name: FUN_0102665c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* CPUNET private byte producer wrapper @ 0x0102665c.
 * True executable extent [0x0102665c,0x0102667c).
 * Raw back-map: FUN_0102665c@0x0102665c. */
#include <stdint.h>

extern unsigned FUN_01009224(void *source);

int FUN_0102665c(void *source, uint8_t *destination)
{
    unsigned value;
    if (source == 0 || destination == 0)
        return -22;
    value = FUN_01009224(source);
    if (value == 0)
        return -35;
    *destination = (uint8_t)value;
    return 0;
}
