/* readable reconstruction; identity: FUN_00024f40 @ 0x00024f40
 * public-name: st25dv_write_control_and_ack
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   st25dv_write_control_and_ack             <= FUN_00024f40 @ 0x00024f40
 *   st25dv_ipc_send_byte                     <= FUN_0007c8d0 @ 0x0007c8d0
 *   ipc_ept_op_b_guarded                     <= FUN_0007c8e8 @ 0x0007c8e8
 *   st25dv_reg_modify_low5                   <= FUN_0007c8fa @ 0x0007c8fa
 * address symbols (name @ address):
 *   g_st25dv_dev                             @ 0x20007a44
 */
/* Reconstructed FUN_00024f40 @ 0x24f40  (parity: 300/300 trials, PROVEN) */

extern int st25dv_ipc_send_byte(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern unsigned int ipc_ept_op_b_guarded(unsigned int, int);
extern void st25dv_reg_modify_low5(int, int);

void st25dv_write_control_and_ack(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile unsigned int *puVar1 = (volatile unsigned int*)0x20007a44UL;
    unsigned char localbuf[8];
    unsigned int val = *puVar1;
    int iVar2 = st25dv_ipc_send_byte(val, param_1 & 0xff, param_3, param_4);
    if (iVar2 == 0) {
        val = *puVar1;
        iVar2 = ipc_ept_op_b_guarded(val, localbuf);
        if (iVar2 == 0) {
            unsigned char b = ((param_1 >> 8) & 3) | 0xc;
            localbuf[0] = b;
            val = *puVar1;
            /* 0x24f5c `ubfx r1,r4,#8,#2` / 0x24f60 `orr r1,r1,#0xc` /
     * 0x24f66 `strb.w r1,[sp,#7]` / 0x24f6a `bl 0x7c8fa` -- TWO register
     * arguments; 0x7c8fa consumes r1 (`mov r4,r1` ... `and r4,r4,#0x1f`). */
            st25dv_reg_modify_low5(val, b);
        }
    }
}
