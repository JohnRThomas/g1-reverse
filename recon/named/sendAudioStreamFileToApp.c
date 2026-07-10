/* named: sendAudioStreamFileToApp */
/* globals referenced:
//   0x2000392c  g_dashboard_response_msgq    
*/
/* Reconstructed sendAudioStreamFileToApp @ 0x47bf8  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern int k_msgq_put(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int);

int sendAudioStreamFileToApp(unsigned char param_1, unsigned char param_2)
{
  unsigned char buf[6];
  buf[4] = param_1;
  buf[5] = param_2;
  memset_bytes(buf+1, 0, 0x17);
  int iVar1 = k_msgq_put(0x2000392c, buf, 0, 0);
  if (iVar1 != 0) {
    DEBUG_PRINT(0xef058, 0xef71d);
    iVar1 = -1;
  }
  return iVar1;
}

