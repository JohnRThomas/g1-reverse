/* readable reconstruction; identity: FUN_01033354 @ 0x01033354
 * public-name: FUN_01033354
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_log_msg_ctx                        @ 0x21000698
 *   g_esb_pipe_pid_cnt                       @ 0x21006256
 *   g_net_radio_busy_flag                    @ 0x21006458
 *   g_esb_enabled_flag                       @ 0x21006459
 *   REG_41008650                             @ 0x41008650
 */
/* net-core FUN_01033354 @ 0x1033354 */
#include <stdint.h>

extern void FUN_01033ee4(void);
extern void FUN_01032908(void);
extern void FUN_01035068(uint32_t);
extern void FUN_01033f38(void);
extern uint64_t FUN_010327a0(uint32_t, uint32_t);
extern uint64_t FUN_0103b62e(uint32_t, uint32_t, uint32_t);
extern void FUN_0103a83e(uint32_t, uint32_t, uint32_t,
                         volatile uint32_t *);

void FUN_01033354(void)
{
    FUN_01033ee4();
    FUN_01032908();
    FUN_01035068(0x21000698u);
    FUN_01033f38();
    volatile uint32_t *radio = (volatile uint32_t *)0x41008650u;
    *radio &= 0x300u;
    *(volatile uint8_t *)0x21006458u = 0;
    *(volatile uint8_t *)0x21006459u = 0;
    uint64_t value = FUN_010327a0(0x21004b7cu, 0);
    uint64_t completion = FUN_0103b62e((uint32_t)value,
                                       (uint32_t)(value >> 32), 0x20u);
    volatile uint32_t *state = (volatile uint32_t *)0x21006256u;
    state[0] = 0;
    state[1] = 0;
    FUN_0103a83e((uint32_t)completion, (uint32_t)(completion >> 32),
                 0x20u, state);
}
