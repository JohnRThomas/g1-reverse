#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01019588 @ 0x01019588
 * public-name: FUN_01019588
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_ll_conn_default_ctx                    @ 0x21001058
 */
/* Reconstructed net-core state initializer @ 0x01019588. */
#include <stdint.h>

extern void *FUN_0100a5a0(void);
extern void FUN_0102714a(void *, void *, void *);
extern uint8_t *FUN_010270d2(void *);

void FUN_01019588(void)
{
    uint16_t auxiliary;
    void *handle;
    volatile uint8_t *entry;
    volatile uint8_t *global = (volatile uint8_t *)((unsigned long)&g_ll_conn_default_ctx) /*=0x21001058*/;

    FUN_0102714a(FUN_0100a5a0(), &handle, &auxiliary);
    entry = FUN_010270d2(handle);

    *(volatile uint32_t *)(entry + 0x1a) = 0;
    *(volatile uint32_t *)(entry + 0x12) = 0;
    *(volatile uint32_t *)(entry + 0x1e) = 0;
    *(volatile uint32_t *)(entry + 0x22) = 0;
    entry[0x20] = 0xff;
    entry[0x13] = 0xff;
    entry[0x25] = 0xff;
    *(volatile uint32_t *)(entry + 0x2a) = 0;
    *(volatile uint32_t *)(entry + 0x16) = 0;
    entry[0x2c] = 0x7f;
    *(volatile uint32_t *)(entry + 0x26) = 0;

    *(volatile uint32_t *)(global + 0x40) = 0;
    *(volatile uint16_t *)(global + 0x44) = 0;
    global[0] = 0;
    global[0x46] = 0;
    entry[0x1c] = (uint8_t)((entry[0x1c] & 0x9f) | 0x20);
}
