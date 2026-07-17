#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004b17c @ 0x0004b17c
 * public-name: lseek
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fd_table_lookup                          <= FUN_0004b01c @ 0x0004b01c
 *   lseek                                    <= FUN_0004b17c @ 0x0004b17c
 *   z_fdtable_call_ioctl                     <= FUN_0007dcb8 @ 0x0007dcb8
 * address symbols (name @ address):
 *   g_posix_fd_table                         @ 0x20002548
 */
/* Reconstructed FUN_0004b17c @ 0x4b17c  (parity: 300/300 trials, PROVEN) */

extern int fd_table_lookup(void);
extern unsigned int z_fdtable_call_ioctl(unsigned int, unsigned int, int, unsigned int, unsigned int, unsigned int);

unsigned int lseek(int param_1, unsigned int param_2, unsigned int param_3)
{
    int iVar1 = fd_table_lookup();
    if (iVar1 < 0) {
        return 0xffffffff;
    }
    unsigned int base = ((unsigned long)&g_posix_fd_table) /*=0x20002548*/ + (unsigned int)param_1 * 0x28U;
    unsigned int v0 = *(volatile unsigned int*)base;
    unsigned int v4 = *(volatile unsigned int*)(base + 4);
    return z_fdtable_call_ioctl(v4, v0, 0x101, param_2, param_3, param_2);
}
