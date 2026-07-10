/* named: check_ancs_inbox_flag_change */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
//   0x20018da5  g_ancs_inbox_flag_cached     
//   0x20018da6  g_ancs_inbox_flag_current    
*/
/* Reconstructed check_ancs_inbox_flag_change @ 0x2eb40  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void debug_print(void);

unsigned int check_ancs_inbox_flag_change(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  (void)param_1; (void)param_2;
  volatile unsigned char *p68 = (volatile unsigned char*)0x20018da6UL;
  volatile unsigned char *p6c = (volatile unsigned char*)0x20018da5UL;
  unsigned char bVar1 = *p68;
  unsigned int uVar3 = bVar1;
  if (*p6c != uVar3) {
    if (*(volatile unsigned int*)0x20007554UL == 0) {
      DEBUG_PRINT(0xa3e80, uVar3, param_3, 0, param_4);
    } else {
      debug_print();
    }
  }
  *p6c = bVar1;
  return uVar3;
}

