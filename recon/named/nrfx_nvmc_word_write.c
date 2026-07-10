/* named: nrfx_nvmc_word_write */
/* globals referenced:
//   0x50039000  NRF_NVMC_S                   
*/
/* Reconstructed nrfx_nvmc_word_write @ 0x65f80  (parity: 300/300 trials, PROVEN) */
extern void printk(unsigned,unsigned,unsigned,unsigned,unsigned);
extern long long assert_post_action(unsigned,unsigned);
extern void nvmc_word_write(void);
extern void nvmc_readonly_mode_set(void);
void nrfx_nvmc_word_write(unsigned param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    unsigned r0v = param_1;
    if (param_1 < 0x100000) goto L_fae;
    if ((param_1 - 0xff8000) < 0x1000) goto L_fae;
    printk(0x99cbd,0xf6ca8,0xf6c32,0x195,param_4);
    { long long r = assert_post_action(0xf6c32,0x195); r0v=(unsigned)r; }
L_fae:
    if ((r0v & 3) == 0) goto L_fc6;
    printk(0x99cbd,0xf6cc2,0xf6c32,0x196,param_4);
    { long long r = assert_post_action(0xf6c32,0x196); r0v=(unsigned)r; }
    goto L_fae;
L_fc6:
    *(volatile unsigned*)(0x50039000UL + 0x584) = 1;
    *(volatile unsigned*)(0x50039000UL + 0x504) = 1;
    nvmc_word_write();
    nvmc_readonly_mode_set();
}

