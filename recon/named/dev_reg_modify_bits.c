#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083e0e @ 0x00083e0e
 * public-name: dev_reg_modify_bits
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 *   dev_ctrl_read1                           <= FUN_00083dba @ 0x00083dba
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 *   dev_reg_modify_bits                      <= FUN_00083e0e @ 0x00083e0e
 */
/* Reconstructed dev_reg_modify_bits @ 0x83e0e  (CFG-directed candidate) */
/* Reconstructed dev_reg_modify_bits @ 0x83e0e  (dev_reg_modify_bits)
 *
 * ITERATION-13 DEFECT FIX: the previous reconstruction declared THREE
 * parameters and called dev_write_reg3 with three arguments, so the value to
 * be written and the bit mask were both dropped and the read-modify-write
 * body was missing entirely.  Original (98 B), five parameters -- four in
 * registers plus an 8-bit mask at sp+0x28:
 *     83e1a  ldrb.w r9,[sp,#0x28]     ; mask (5th arg)
 *     83e1e  ldr.w  r8,[r0,#0x10]     ; mutex
 *     83e22  mov.w  r2,#-1 ; r3,#-1   ; K_FOREVER (64-bit k_timeout_t)
 *     83e2c  bl     0x723b8           ; k_mutex_lock
 *     83e36  add.w  r3,sp,#7          ; &scratch byte
 *     83e3a  bl     0x83dba           ; dev_ctrl_read1(dev,r1,r2,&scratch)
 *     83e40  cbnz   r0,0x83e62
 *     83e42  ldrb.w r3,[sp,#7]
 *     83e48  bic.w  r3,r3,r9          ; value &= ~mask
 *     83e4c  and.w  r9,r9,sl          ; mask  &= new
 *     83e50  orr.w  r3,r3,r9
 *     83e58  strb.w r3,[sp,#7]
 *     83e5c  bl     0x83dc8           ; dev_write_reg3(dev,r1,r2,merged)
 *     83e64  bl     0x72558           ; k_mutex_unlock
 */

typedef struct { long long ticks; } g1_k_timeout_t;

extern int k_mutex_lock(unsigned int mutex, g1_k_timeout_t timeout);
extern int k_mutex_unlock(unsigned int mutex);
extern int dev_ctrl_read1(int dev, unsigned int a, unsigned int b, void *out);
extern int dev_write_reg3(unsigned int, unsigned int, unsigned int, unsigned int);

int dev_reg_modify_bits(int param_1, unsigned int param_2, unsigned int param_3,
                 unsigned int param_4, unsigned char param_5)
{
    unsigned char scratch;
    unsigned int mutex;
    int rc;

    mutex = *(volatile unsigned int *)(param_1 + 0x10);
    k_mutex_lock(mutex, (g1_k_timeout_t){ .ticks = -1 });
    rc = dev_ctrl_read1(param_1, param_2, param_3, &scratch);
    if (rc == 0) {
        unsigned char merged =
            (unsigned char)((scratch & (unsigned char)~param_5) |
                            (param_5 & (unsigned char)param_4));
        scratch = merged;
        rc = dev_write_reg3(param_1, param_2, param_3, merged);
    }
    k_mutex_unlock(mutex);
    return rc;
}
