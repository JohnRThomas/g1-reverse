#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102b15c @ 0x0102b15c
 * public-name: FUN_0102b15c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   printk                                   <= FUN_01039722 @ 0x01039722
 * address symbols (name @ address):
 *   rodata_103d11b                           @ 0x0103d11b
 *   g_zephyr_log_level                       @ 0x21000580
 *   g_net_ctrl_rx_ready_flag                 @ 0x21004c9c
 */
/* net-core FUN_0102b15c @ 0x102b15c  (parity 300 trials PROVEN) */
extern void FUN_0103b62e(void *dst, int val, int len);
extern void FUN_0103b53a(void *dst, unsigned int a, unsigned int b, int len);
extern int FUN_0102a498(void);
extern int FUN_0102a468(void);
extern void FUN_0102a448(void *a, unsigned int b);
extern void printk(int a, unsigned int b, int c);

unsigned int FUN_0102b15c(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    struct {
        unsigned int header;
        unsigned char payload[248];
    } packet;
    unsigned int uVar2;

    packet.header = 0;
    FUN_0103b62e(packet.payload, 0, sizeof(packet.payload));
    FUN_0103b53a(&packet, param_2, param_3, sizeof(packet));
    int iVar1 = FUN_0102a498();
    if (iVar1 == 1) {
        return 0;
    }
    if (param_3 < 0xfc) {
        iVar1 = FUN_0102a468();
        if (iVar1 == 0) {
            FUN_0102a448(&packet, param_3);
            *(volatile unsigned char *)((unsigned long)&g_net_ctrl_rx_ready_flag) /*=0x21004c9c*/ = 1;
            return 0;
        }
    } else if (0 < *(volatile int *)((unsigned long)&g_zephyr_log_level) /*=0x21000580*/) {
        printk(((unsigned long)&rodata_103d11b) /*=0x103d11b*/, param_3, 0xfb);
    }
    uVar2 = 0xffffffff;
    return uVar2;
}
