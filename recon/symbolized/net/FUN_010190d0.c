#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010190d0 @ 0x010190d0
 * public-name: FUN_010190d0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_llcp_release_rx_context              <= FUN_0101fca8 @ 0x0101fca8
 *   sdc_llcp_stop_rx_timeout                 <= FUN_010208b0 @ 0x010208b0
 * address symbols (name @ address):
 *   g_net_radio_pending_proc_flag            @ 0x2100104a
 */
/* net-core FUN_010190d0 @ 0x10190d0  (parity 300 trials PROVEN) */

extern void FUN_01022a50(unsigned char a);
extern void sdc_llcp_stop_rx_timeout(void);
extern void sdc_llcp_release_rx_context(void);

void FUN_010190d0(void)
{
    unsigned int base = G1N_21000f90;
    if (*(volatile unsigned char*)(base+0x69)==0 && *(volatile int*)(base+0x64)!=0) {
        FUN_01022a50(*(volatile unsigned char*)(base+0x68));
    }
    if (*(volatile unsigned char*)(base+0x7c)!=0) {
        sdc_llcp_stop_rx_timeout();
        sdc_llcp_release_rx_context();
        *(volatile unsigned char*)(base+0x7c)=0;
    }
    *(volatile unsigned short*)(base+0xba)=0;
    *(volatile unsigned char*)(base+0x70)=0;
    *(volatile unsigned char*)(((unsigned long)&g_net_radio_pending_proc_flag) /*=0x2100104a*/+2)=0;
}
