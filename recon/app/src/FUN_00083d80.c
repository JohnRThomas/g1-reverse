/* Reconstructed FUN_00083d80 @ 0x83d80  (CFG-directed candidate) */
/* Reconstructed FUN_00083d80 @ 0x83d80  (dev_ctrl_write2)
 *
 * ITERATION-13 DEFECT FIX, same class as iteration 10's fix to
 * dev_ctrl_write1 (0x83d60): the message array is a STACK object, and the
 * parity harness compares only NON-stack writes, so a body that never
 * materialises it still reported "300/300 PROVEN".  The previous
 * reconstruction declared six unrelated locals and passed `&local_28`,
 * relying on GCC laying them out contiguously.  GCC instead dropped every
 * store except the one whose address escapes, and the linked code was
 *     push {r0,r1,r4,lr} ; add r2,sp,#3 ; str r2,[sp,#4] ; strb r1,[sp,#3]
 *     add r1,sp,#4 ; movs r2,#2 ; blx r4
 * i.e. a two-element i2c_msg array of which only msgs[0].buf was written.
 * nrfx_twim then asserted on an uninitialised 16-bit-overflowing length
 * (nrfx_twim.c:593) and the boot reset at 0.0466 s.
 *
 * Original (58 B):
 *     83d84  strb.w r1,[sp,#4]        ; data[0]
 *     83d98  strb.w r2,[sp,#5]        ; data[1]
 *     83d9c  add    r2,sp,#4
 *     83d9e  str    r2,[sp,#8]        ; msgs[0].buf  = data
 *     83da6  str    r2,[sp,#12]       ; msgs[0].len  = 2
 *     83d92  strb.w r1,[sp,#16]       ; msgs[0].flags= 0
 *     83da8  str    r5,[sp,#20]       ; msgs[1].buf  = param_4
 *     83da0  str    r1,[sp,#24]       ; msgs[1].len  = param_5 (stack arg)
 *     83daa  strb.w r1,[sp,#28]       ; msgs[1].flags= 7
 *     83db2  add    r1,sp,#8          ; msgs
 *     83da2  movs   r2,#2             ; num_msgs
 *     83db4  blx    r4                ; api->transfer(bus, msgs, 2, addr)
 * The result of the transfer is returned (the original does not touch r0
 * between `blx` and `pop`), which dev_reg_modify_bits relies on.
 */

typedef int (*g1_i2c_transfer_fn)(int bus, void *msgs, int num_msgs,
                                  unsigned short addr);

struct g1_i2c_msg {
    unsigned int buf;
    unsigned int len;
    unsigned char flags;
};

int FUN_00083d80(int param_1, unsigned char param_2, unsigned char param_3,
                 unsigned int param_4, unsigned int param_5)
{
    struct g1_i2c_msg msgs[2];
    unsigned char data[2];
    int *spec;
    int base;
    g1_i2c_transfer_fn f;

    spec = *(int **)(param_1 + 4);
    base = *spec;
    data[0] = param_2;
    data[1] = param_3;
    msgs[0].buf = (unsigned int)(unsigned long)&data[0];
    msgs[0].len = 2;
    msgs[0].flags = 0;
    msgs[1].buf = param_4;
    msgs[1].len = param_5;
    msgs[1].flags = 7;
    f = (g1_i2c_transfer_fn)(*(volatile int *)(*(volatile int *)(base + 8) + 8));
    return f(base, msgs, 2, *(volatile unsigned short *)((char *)spec + 4));
}
