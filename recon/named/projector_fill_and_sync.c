/* named: projector_fill_and_sync */
/* Reconstructed projector_fill_and_sync @ 0x7d6f4  (parity: 300/300 trials, PROVEN) */

extern void projector_fill_framebuffer(void);
extern unsigned long long projector_send_cmd_immediate(unsigned int);
extern void delay_ms(unsigned int, unsigned int, unsigned int, unsigned int);

void projector_fill_and_sync(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned long long ret;
    projector_fill_framebuffer();
    ret = projector_send_cmd_immediate(0x97);
    delay_ms(1, (unsigned int)(ret >> 32), param_3, param_4);
}

