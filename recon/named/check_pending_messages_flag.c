/* readable reconstruction; identity: FUN_0002c1fc @ 0x0002c1fc
 * public-name: check_pending_messages_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   check_pending_messages_flag              <= FUN_0002c1fc @ 0x0002c1fc
 *   msg_content_recalc_unread                <= FUN_00033cf8 @ 0x00033cf8
 *   k_uptime_get_2                           <= FUN_0007ce40 @ 0x0007ce40
 * address symbols (name @ address):
 *   g_pending_message_flag                   @ 0x20018d9e
 */
/* Reconstructed FUN_0002c1fc @ 0x2c1fc  (parity: 300/300 trials, PROVEN) */

extern void k_uptime_get_2(void);
extern int msg_content_recalc_unread(void);

void check_pending_messages_flag(void)
{
    k_uptime_get_2();
    int iVar1 = msg_content_recalc_unread();
    if (iVar1 != 0) {
        *(volatile unsigned char*)0x20018d9eUL = 1;
    }
}
