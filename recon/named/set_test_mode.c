/* named: set_test_mode */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
//   0x20019ef3  g_test_mode_flag             
*/
/* Reconstructed set_test_mode @ 0x32ef0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int, unsigned int);
extern void debug_print(void);

void set_test_mode(unsigned int param_1)
{
  if (*(volatile unsigned int*)0x20007554UL == 0) {
    DEBUG_PRINT(0x000a756aUL, param_1);
  }
  else {
    debug_print();
  }
  *(volatile unsigned char*)0x20019ef3UL = (unsigned char)param_1;
  return;
}

