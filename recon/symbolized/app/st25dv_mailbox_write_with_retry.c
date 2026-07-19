#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00024fe8 @ 0x00024fe8
 * public-name: st25dv_mailbox_write_with_retry
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   st25dv_mailbox_send_message              <= FUN_00024f78 @ 0x00024f78
 *   st25dv_mailbox_write_with_retry          <= FUN_00024fe8 @ 0x00024fe8
 *   pt_write_frame_type3                     <= FUN_0007c3d0 @ 0x0007c3d0
 * address symbols (name @ address):
 *   g_st25dv_mailbox_msg                     @ 0x20007a14
 */
/* Reconstructed FUN_00024fe8 @ 0x24fe8  (parity: 300/300 trials, PROVEN) */

extern int pt_write_frame_type3(unsigned short, unsigned int);
extern unsigned int st25dv_mailbox_send_message(void);

unsigned int st25dv_mailbox_write_with_retry(unsigned int param_1, unsigned int param_2)
{
    int iVar1;
    unsigned int uVar2;
    unsigned short selector = (unsigned short)param_2;

    iVar1 = pt_write_frame_type3(selector, param_1);
    if (iVar1 == -1) {
        *(volatile unsigned int*)((unsigned long)&g_st25dv_mailbox_msg) /*=0x20007a14*/ = 0x014040e1U;
        uVar2 = st25dv_mailbox_send_message();
        pt_write_frame_type3(selector, param_1);
    } else {
        uVar2 = 0;
    }
    return uVar2;
}
