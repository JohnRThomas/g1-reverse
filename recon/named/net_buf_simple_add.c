/* readable reconstruction; identity: FUN_0005f5d0 @ 0x0005f5d0
 * public-name: net_buf_simple_add
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   net_buf_simple_tailroom                  <= FUN_00083730 @ 0x00083730
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f543a                             @ 0x000f543a
 *   rodata_f54a8                             @ 0x000f54a8
 */
/* Reconstructed FUN_0005f5d0 @ 0x5f5d0  (parity: 300/300 trials, PROVEN) */

extern unsigned int net_buf_simple_tailroom(void);
extern void printk(unsigned int a,unsigned int b,unsigned int c,unsigned int d);
extern void assert_post_action(unsigned int a,unsigned int b);

int net_buf_simple_add(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned short uVar1;
    unsigned int uVar2;
    int iVar3;
    volatile unsigned short *hp = (volatile unsigned short *)((char*)param_1 + 4);
    uVar1 = *hp;
    iVar3 = *(volatile int*)param_1;
    uVar2 = net_buf_simple_tailroom();
    if (uVar2 < param_2) {
        printk(0x00099cbdUL, 0x000f54a8UL, 0x000f543aUL, 0x3e);
        assert_post_action(0x000f543aUL, 0x3e);
    }
    *hp = uVar1 + (unsigned short)param_2;
    return iVar3 + (unsigned int)uVar1;
}
