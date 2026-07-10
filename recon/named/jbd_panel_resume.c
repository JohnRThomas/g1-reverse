/* named: jbd_panel_resume */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed jbd_panel_resume @ 0x47638  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void*, void*, unsigned int, int, unsigned int);
extern int debug_print(void);
extern void set_brightness_to_panel_reg(unsigned int);
extern void panel_init(void);

unsigned int jbd_panel_resume(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  volatile int *piVar1 = (volatile int*)0x2000230cUL;

  if (*piVar1 > 2) {
    if (*(volatile unsigned int*)0x20007554UL == 0) {
      DEBUG_PRINT((void*)0xd73bcUL, (void*)0xd73f8UL, param_3, 0, param_4);
    } else {
      debug_print();
    }
  }
  panel_init();
  set_brightness_to_panel_reg(*(unsigned char*)(param_1+0x369));
  if (*piVar1 > 2) {
    if (*(volatile unsigned int*)0x20007554UL == 0) {
      DEBUG_PRINT((void*)0xd73e0UL, (void*)0xd73f8UL, param_3, 0, param_4);
    } else {
      debug_print();
    }
  }
  return 0;
}

