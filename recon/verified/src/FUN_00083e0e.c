/* Reconstructed FUN_00083e0e @ 0x83e0e  (CFG-directed candidate) */
/* Reconstructed FUN_00083e0e @ 0x83e0e  (dev_reg_modify_bits)
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

extern int FUN_000723b8(unsigned int mutex, g1_k_timeout_t timeout);
extern int FUN_00072558(unsigned int mutex);
extern int FUN_00083dba(int dev, unsigned int a, unsigned int b, void *out);
extern int FUN_00083dc8(int dev, unsigned int a, unsigned int b,
                        unsigned int value);

int FUN_00083e0e(int param_1, unsigned int param_2, unsigned int param_3,
                 unsigned int param_4, unsigned char param_5)
{
    unsigned char scratch;
    unsigned int mutex;
    int rc;

    mutex = *(volatile unsigned int *)(param_1 + 0x10);
    FUN_000723b8(mutex, (g1_k_timeout_t){ .ticks = -1 });
    rc = FUN_00083dba(param_1, param_2, param_3, &scratch);
    if (rc == 0) {
        unsigned char merged =
            (unsigned char)((scratch & (unsigned char)~param_5) |
                            (param_5 & (unsigned char)param_4));
        scratch = merged;
        rc = FUN_00083dc8(param_1, param_2, param_3, merged);
    }
    FUN_00072558(mutex);
    return rc;
}
