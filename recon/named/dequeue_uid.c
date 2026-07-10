/* named: dequeue_uid */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006a38  g_uid_pipe                   
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed dequeue_uid @ 0x18ff8  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_get(unsigned int a, void *b, unsigned int c, unsigned int d);
extern void DEBUG_PRINT(unsigned int a, unsigned int b);
extern void debug_print(void);

int dequeue_uid(unsigned int *param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar1;
  unsigned int local_18;
  unsigned int uStack_14;
  unsigned int uStack_10;

  local_18 = 0;
  uStack_14 = 0;
  if (*(volatile int *)(0x20006a38UL + 0x10) == 0) {
    iVar1 = 1;
  } else {
    uStack_10 = param_3;
    iVar1 = k_msgq_get(0x20006a38UL, &local_18, 0, 0);
    if (iVar1 == 0) {
      *param_1 = local_18;
      param_1[1] = uStack_14;
    } else if (0 < *(volatile int *)0x2000230cUL) {
      if (*(volatile int *)0x20007554UL == 0) {
        DEBUG_PRINT(0x9aafd, 0x9b16a);
      } else {
        debug_print();
      }
    }
  }
  return iVar1;
}

