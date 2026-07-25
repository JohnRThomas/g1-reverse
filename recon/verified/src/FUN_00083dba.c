/* Reconstructed FUN_00083dba @ 0x83dba  (CFG-directed candidate) */
/* Reconstructed FUN_00083dba @ 0x83dba  (dev_ctrl_read1)
 *
 * ITERATION-13 DEFECT FIX, same class as iteration 12's k_thread_create
 * veneer (0x7cb66): the previous reconstruction declared both this function
 * and its callee as taking NO arguments and simply calling through, which GCC
 * compiled to a bare `b.w` tail branch.  That forwarded the caller's register
 * arguments by accident and left the fifth (stack) argument -- the message
 * length -- as whatever the caller happened to have below its own frame.
 *
 * Original (14 B):
 *     83dba  push {r0,r1,r4,lr}
 *     83dbc  movs r4,#1
 *     83dbe  str  r4,[sp,#0]      ; 5th argument = 1
 *     83dc0  bl   0x83d80         ; dev_ctrl_write2(dev,b1,b2,buf,1)
 *     83dc4  add  sp,#8
 *     83dc6  pop  {r4,pc}         ; returns dev_ctrl_write2's result
 */

extern int FUN_00083d80(int param_1, unsigned char param_2,
                        unsigned char param_3, unsigned int param_4,
                        unsigned int param_5);

int FUN_00083dba(int param_1, unsigned char param_2, unsigned char param_3,
                 unsigned int param_4)
{
    return FUN_00083d80(param_1, param_2, param_3, param_4, 1);
}
