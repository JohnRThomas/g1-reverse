/* named: gpiote_in_event_enable */
/* globals referenced:
//   0x20002bc0  g_gpiote_cb                  
*/
/* Reconstructed gpiote_in_event_enable @ 0x659e4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int get_pin_idx(uint32_t);
extern int pin_in_use_by_te(uint32_t);
extern int gpiote_pin_sense_is_enabled(void);
extern int pin_is_output(uint32_t);
extern int pin_te_get(uint32_t);
extern int FUN_00065584(void*);
extern int gpiote_in_event_reg_offset(void);
extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,...);
extern void nrf_gpio_cfg_sense_set(uint32_t,int);

void gpiote_in_event_enable(uint32_t param_1, uint32_t param_2){
    int iVar1;
    uint32_t uVar2 = param_1;
    iVar1 = gpiote_pin_sense_is_enabled();
    if (iVar1 == 0){
        printk(0x00099cbd,0x000f6b87,0x000f6b00,0x364,uVar2);
        goto Lec_364;
    }
  L_a08:
    iVar1 = pin_in_use_by_te(param_1);
    if (iVar1 != 0 && (iVar1 = pin_is_output(param_1)) == 0){
        uVar2 = pin_te_get(param_1);
        iVar1 = gpiote_in_event_reg_offset();
        *(volatile uint32_t*)((uint32_t)iVar1 + 0x5000d000UL) = 0;
        int t = (int)(int16_t)uVar2 * 4;
        *(volatile uint32_t*)((uint32_t)t + 0x5000d510UL) |= 1;
        if (param_2 != 0){
            *(volatile int*)(0x5000d000UL + 0x304) = 1 << (uVar2 & 0xff);
        }
        return;
    }
    if (param_2 != 0){
        int r = get_pin_idx(param_1);
        uint32_t s = ((uint32_t)*(volatile uint16_t*)(0x20002bc0UL + (uint32_t)(r + 8) * 2) << 0x1b) >> 0x1d;
        int iv;
        if (s == 4) iv = 3;
        else if (s == 5) iv = 2;
        else {
            uint32_t local_14 = param_1;
            int q = FUN_00065584(&local_14);
            iv = (int)((*(volatile uint32_t*)(q + 0x10) >> (local_14 & 0xff)) & 1) + 2;
        }
        nrf_gpio_cfg_sense_set(param_1, iv);
        return;
    }
    printk(0x00099cbd,0x000f6b9c,0x000f6b00,0x373,uVar2);
    assert_post_action(0x000f6b00,0x373);
    goto L_a08;
  Lec_364:
    assert_post_action(0x000f6b00,0x364);
    goto L_a08;
}

