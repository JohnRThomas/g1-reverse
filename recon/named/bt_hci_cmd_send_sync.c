/* readable reconstruction; identity: FUN_00053d70 @ 0x00053d70
 * public-name: bt_hci_cmd_send_sync
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_create                        <= FUN_00053cd4 @ 0x00053cd4
 *   bt_hci_cmd_send_sync                     <= FUN_00053d70 @ 0x00053d70
 *   net_buf_id                               <= FUN_0005ee18 @ 0x0005ee18
 *   net_buf_put                              <= FUN_0005f200 @ 0x0005f200
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_ref                              <= FUN_0005f2d4 @ 0x0005f2d4
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 *   z_impl_k_sem_init                        <= FUN_00086534 @ 0x00086534
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_a7a10                             @ 0x000a7a10   [INLINED -- G6 literal batch]
 *   rodata_f2e84                             @ 0x000f2e84
 *   rodata_f301e                             @ 0x000f301e   [INLINED -- G6 literal batch]
 *   rodata_f304a                             @ 0x000f304a
 *   hci_cmd_pool                             @ 0x2000214c
 *   bt_hci_cmd_data                          @ 0x2000abf4
 */
/* Full reconstruction FUN_00053d70 @ 0x00053d70 (226-byte exact extent). */
#include <stdint.h>

extern void *bt_hci_cmd_create(uint32_t opcode, uint32_t reserve);
extern void z_impl_k_sem_init(void *, uint32_t, uint32_t);
extern uint64_t net_buf_id(void *);
extern uintptr_t net_buf_ref(void *, uint32_t, uint32_t, uint32_t);
extern uint64_t net_buf_put(uintptr_t, uintptr_t, uint32_t, uint32_t);
extern int z_impl_k_sem_take(void *, uint32_t, uint32_t, uint32_t);
extern void printk(uintptr_t, ...);
extern void bt_log_forward_3arg(uintptr_t, uint32_t, const void *);
extern void net_buf_unref(void *);
extern void assert_post_action(uintptr_t, uint32_t) __attribute__((noreturn));

struct log_record4 { uint32_t count, format, opcode, status; };

int bt_hci_cmd_send_sync(uint32_t opcode, void *command, void **result)
{
    /* Reserve the complete aligned event object.  The firmware uses 28 bytes
     * of payload in a 32-byte stack slot. */
    uint8_t completion[32];
    uint8_t status;

    if (command == 0) {
        command = bt_hci_cmd_create(opcode, 0);
        if (command == 0)
            return -105;
    }
    z_impl_k_sem_init(completion, 0, 1);
    uint64_t indexed = net_buf_id(command);
    int slot = (int)indexed;
    *(void **)(0x2000abf4u + (uint32_t)slot * 12u + 8u) = completion;
    uintptr_t token = net_buf_ref(command, (uint32_t)(indexed >> 32), 1, 12);
    uint64_t inherited = net_buf_put(0x2000214cu, token, 1, 12);
    int wait_error = z_impl_k_sem_take(completion, (uint32_t)(inherited >> 32), 0x50000u, 0);
    if (wait_error != 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"err == 0"), 0x000f2e84u, 0x152u);
        printk(0x000f301eu, opcode, wait_error);
        assert_post_action(0x00099cbdu, 0x152u);
    }
    status = *(volatile uint8_t *)(0x2000abf4u + (uint32_t)net_buf_id(command) * 12u);
    if (status == 0) {
        if (result != 0) *result = command;
        else net_buf_unref(command);
        return 0;
    }
    struct log_record4 record = {4, 0x000f304au, opcode, status};
    bt_log_forward_3arg(0x00088138u, 0x2080u, &record);
    net_buf_unref(command);
    return status == 9 ? -111 : status == 13 ? -12 : -5;
}
