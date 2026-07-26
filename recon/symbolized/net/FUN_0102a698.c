#include "g1_net_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0102a698 @ 0x0102a698
 * public-name: FUN_0102a698
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_k_msgq_put                        <= FUN_01036198 @ 0x01036198
 *   printk                                   <= FUN_01039722 @ 0x01039722
 * address symbols (name @ address):
 *   rodata_103cd46                           @ 0x0103cd46
 *   g_zephyr_log_level                       @ 0x21000580
 */
/* net-core FUN_0102a698 @ 0x102a698  (parity 300 trials PROVEN) */

extern void FUN_0103b614(void *dst, void *src, unsigned int n);
extern int z_impl_k_msgq_put(unsigned int a, void *b, int c, int d);

int FUN_0102a698(void *param_1)
{
    unsigned char buf[256];
    int iVar1;
    if (*(volatile int*)(G1N_210045b0 + 0x10) == 0) {
        iVar1 = 1;
    } else {
        FUN_0103b614(buf, param_1, 0xfb);
        iVar1 = z_impl_k_msgq_put(G1N_210045b0, buf, 0, 0);
        if (iVar1 != 0 && 0 < *(volatile int*)((unsigned long)&g_zephyr_log_level) /*=0x21000580*/) {
            printk(((unsigned long)&rodata_103cd46) /*=0x103cd46*/);
        }
    }
    return iVar1;
}
