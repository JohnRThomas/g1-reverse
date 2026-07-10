/* named: FUN_00066b24 */
/* globals referenced:
//   0x2000b348  g_qspi_cb                    
//   0x5002b000  NRF_QSPI_BASE                
*/
/* Reconstructed FUN_00066b24 @ 0x66b24  (parity: 300/300 trials, PROVEN) */

extern void arch_irq_disable(int a);
extern void qspi_deactivate(void);
extern void FUN_000851fa(unsigned a);
extern void printk(unsigned a,unsigned b,unsigned c,unsigned d,unsigned e);
extern void assert_post_action(unsigned a,unsigned b);
void FUN_00066b24(void){
    volatile unsigned char *g = (volatile unsigned char*)0x2000b348;
    if (g[0x30] == 0){
        printk(0x00099cbd,0x000f6d9a,0x000f6d5e,0x2b1,0);
        assert_post_action(0x000f6d5e,0x2b1);
    }
    arch_irq_disable(0x2b);
    qspi_deactivate();
    if (g[0x3a] == 0){
        volatile unsigned *b = (volatile unsigned*)0x5002b000;
        unsigned v524 = b[0x524/4];
        unsigned v528 = b[0x528/4];
        unsigned v530 = b[0x530/4];
        unsigned v534 = b[0x534/4];
        unsigned v538 = b[0x538/4];
        unsigned v53c = b[0x53c/4];
        FUN_000851fa(v524 & 0xff);
        FUN_000851fa(v528 & 0xff);
        FUN_000851fa(v530 & 0xff);
        unsigned r5 = v538 & 0xff;
        FUN_000851fa(v534 & 0xff);
        unsigned r4 = v53c & 0xff;
        if (r5 != 0xff) FUN_000851fa(r5);
        if (r4 != 0xff) FUN_000851fa(r4);
    }
    g[0x30] = 0;
}

