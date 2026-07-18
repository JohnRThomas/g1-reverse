/* readable reconstruction; identity: FUN_01032ad8 @ 0x01032ad8
 * public-name: FUN_01032ad8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e3bf                           @ 0x0103e3bf
 *   g_net_radio_crc_scratch                  @ 0x21000684
 *   g_esb_state                              @ 0x21004a94
 */
/* net-core FUN_01032ad8 @ 0x1032ad8  (parity 300 trials PROVEN) */
extern void FUN_01021920(int a, void *b, int c, int d, int e);
extern int FUN_010218fc(int a);
extern int assert_print(int a, int b, int c);
extern int assert_post_action(int a, int b);

void FUN_01032ad8(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int local_c = param_2;
    unsigned int uStack_8 = param_3;
    (void)uStack_8;

    unsigned char *p13 = (unsigned char *)0x21000684;
    signed char *p10 = (signed char *)0x21004a94;
    int arg0 = (int)p10[10];
    int arg2 = (int)p13[0x13] + 0x960;

    FUN_01021920(arg0, &local_c, arg2, 0, (int)param_1);

    int iVar3 = FUN_010218fc((int)&local_c + 1);
    int r0carry;
    if (iVar3 != 0) {
        assert_print(0x103d2a7, 0x103e3bf, 0x242);
        r0carry = assert_post_action(0x103e3bf, 0x242);
    } else {
        r0carry = 0;
    }

    signed char cl = *(signed char *)&local_c;
    int use_r0 = r0carry;
    if (cl > 0) {
        use_r0 = 1;
        local_c = (unsigned int)(unsigned char)(cl - 3);
    }
    volatile unsigned int *base = (volatile unsigned int *)0x41004000;
    base[0x500 / 4] = (unsigned int)use_r0;
    unsigned char byte_val = *(unsigned char *)&local_c;
    *(volatile unsigned int *)((char *)base + 0x4000 + 0x50c) = (unsigned int)byte_val;
}
