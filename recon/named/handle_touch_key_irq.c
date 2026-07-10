/* named: handle_touch_key_irq */
/* globals referenced:
//   0x20019dac  g_touch_key_irq_line_status  
*/
/* Reconstructed handle_touch_key_irq @ 0x30af0  (parity: 300/300 trials, PROVEN) */

extern int attr_store_get(int,unsigned int*,int,int,int);
extern void flash_apply_config_table(void);

void handle_touch_key_irq(int param_1, int param_2, int param_3)
{
    unsigned int local_c = 0;
    int iVar1 = attr_store_get(0x4410, &local_c, param_3, 0, param_1);
    if (iVar1 >= 0) {
        if ((int)(local_c << 0x1d) < 0) {
            *(volatile unsigned char*)0x20019dacUL = 2;
        }
        if ((local_c & 2) != 0) {
            *(volatile unsigned char*)0x20019dacUL = 1;
        }
        if ((local_c & 1) != 0) {
            flash_apply_config_table();
            return;
        }
    }
}

