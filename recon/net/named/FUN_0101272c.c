/* readable reconstruction; identity: FUN_0101272c @ 0x0101272c
 * public-name: FUN_0101272c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_work_submit                          <= FUN_0100ef88 @ 0x0100ef88
 *   sdc_ext_adv_reschedule                   <= FUN_010140ec @ 0x010140ec
 *   sdc_hci_event_suppressed                 <= FUN_0101f888 @ 0x0101f888
 *   sdc_llcp_release_rx_context              <= FUN_0101fca8 @ 0x0101fca8
 *   sdc_llcp_stop_rx_timeout                 <= FUN_010208b0 @ 0x010208b0
 * address symbols (name @ address):
 *   rodata_1011add                           @ 0x01011add
 *   g_net_own_addr_info                      @ 0x21000f20
 */
/* net-core FUN_0101272c @ 0x101272c  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void sdc_work_submit(void *a, unsigned int b, int c);
extern void sdc_ext_adv_reschedule(unsigned char *a, int b, ...);
extern int sdc_hci_event_suppressed(void);
extern void sdc_llcp_release_rx_context(void);
extern void sdc_llcp_stop_rx_timeout(void);

#define DAT_7f0 0x21000f20u
#define LIT_7f4 0x01011addu

unsigned int FUN_0101272c(unsigned char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar3;
    unsigned char cVar4;
    unsigned short uVar5;
    unsigned int uVar2;
    unsigned short uVar1;

    iVar3 = DAT_7f0;
    if (*(volatile char *)(DAT_7f0 + 4) != 1) {
        return 0;
    }
    cVar4 = *(volatile unsigned char *)(DAT_7f0 + 0x12);
    *(volatile unsigned short *)(param_1 + 0x40) = *(volatile unsigned short *)(param_1 + 0x40) + 1;
    if (cVar4 != 0) {
        sdc_llcp_stop_rx_timeout();
        sdc_llcp_release_rx_context();
        *(volatile unsigned char *)(iVar3 + 0x12) = 0;
    }
    *(volatile unsigned char *)(iVar3 + 4) = 0;

    if (param_1[0x79] != 0) {
        sdc_ext_adv_reschedule(param_1, 1);
        return 0;
    }

    uVar5 = (unsigned short)param_1[0xd];
    if (uVar5 == 0 || *(volatile unsigned short *)(param_1 + 0x40) < uVar5) {
        sdc_ext_adv_reschedule(param_1, 0);
        return 0;
    }

    sdc_ext_adv_reschedule(param_1, 1, *(volatile unsigned short *)(param_1 + 0x40), uVar5, param_4);

    if ((int)((unsigned int)*(volatile unsigned short *)(param_1 + 2) << 0x1f) < 0) {
        uVar1 = **(volatile unsigned short **)(param_1 + 0x1c);
        iVar3 = sdc_hci_event_suppressed();
        if (iVar3 != 0) {
            return 0;
        }
        cVar4 = param_1[0xd];
        *(volatile unsigned short *)(param_1 + 0xb1) = uVar1;
        param_1[0xb0] = *param_1;
        param_1[0xaf] = 0x43;
        uVar2 = LIT_7f4;
    } else {
        iVar3 = sdc_hci_event_suppressed();
        if (iVar3 != 0) {
            return 0;
        }
        cVar4 = param_1[0xd];
        param_1[0xb0] = *param_1;
        param_1[0xb1] = 0xff;
        param_1[0xb2] = 0xff;
        param_1[0xaf] = 0x43;
        uVar2 = LIT_7f4;
    }

    if (cVar4 != 0) {
        cVar4 = param_1[0x40];
    }
    param_1[0xb3] = cVar4;
    sdc_work_submit(param_1 + 0xa6, uVar2, 2);
    return 0;
}
