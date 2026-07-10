/* named: dequeue_debug */
/* globals referenced:
//   0x2000751c  g_debug_msg_pipe             
*/
/* Reconstructed dequeue_debug @ 0x19c44  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_get(unsigned int a0, void *a1, unsigned int a2, unsigned int a3);
extern void memcpy(unsigned int a0, void *a1, unsigned int a2);

int dequeue_debug(unsigned int param_1)
{
  int iVar1;
  unsigned char auStack_d8[204];
  iVar1 = k_msgq_get(0x2000751c, auStack_d8, 0, 0);
  if (iVar1 == 0) {
    memcpy(param_1, auStack_d8, 200);
  }
  return iVar1;
}

