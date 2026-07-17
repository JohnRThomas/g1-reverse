/* readable reconstruction; identity: FUN_0101e828 @ 0x0101e828
 * public-name: FUN_0101e828
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_status_defaults_reset         <= FUN_0100bc1c @ 0x0100bc1c
 * address symbols (name @ address):
 *   g_net_ble_conn_create_ctx                @ 0x21000eac
 *   g_net_ble_conn_role_cfg                  @ 0x21001208
 */
/* net-core FUN_0101e828 @ 0x101e828  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_0100a9d0(void);
extern void controller_status_defaults_reset(void);
extern void FUN_0101f8f4(void);
extern void FUN_0100ebf4(void);
extern void FUN_0100d7ac(void);
extern void FUN_010107a0(void);
extern void FUN_0100d808(void);
extern void FUN_0101f87c(uint32_t a);

#define W32(a) (*(volatile uint32_t *)(a))
#define W16(a) (*(volatile uint16_t *)(a))
#define W8(a)  (*(volatile uint8_t  *)(a))

void FUN_0101e828(void)
{
    const uint32_t p1 = 0x21000eac;
    const uint32_t p2 = 0x21001208;

    FUN_0100a9d0();
    controller_status_defaults_reset();
    FUN_0101f8f4();
    FUN_0100ebf4();
    FUN_0100d7ac();
    FUN_010107a0();
    FUN_0100d808();
    FUN_0101f87c(1);

    W32(p1)      = 0x001b0203;
    W16(p1+0x12) = 0;
    W16(p1+4)    = 0x1b;
    W16(p1+0x16) = 0;
    W16(p2+0x18) = 0xf9;
    W16(p2+4)    = 0;
    W8(p2+0x1a)  = 1;
    W8(p2+0x16)  = 0;
    W32(p2)      = 0x0148001b;
    W16(p1+0x18) = 0;
    W8(p1+0x10)  = 0;
    W8(p2+0x1d)  = 0;
}
