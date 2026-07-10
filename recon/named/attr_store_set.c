/* named: attr_store_set */
/* globals referenced:
//   0x20007bc0  g_pt_nfc_link_cfg            
*/
/* Reconstructed attr_store_set @ 0x30178  (parity: 300/300 trials, PROVEN) */

extern void attr_store_retry_delay(int a);
typedef int (*fp_t)(void*,int);

unsigned int attr_store_set(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned char buf[12];
  unsigned char cVar3 = 3;
  int iVar2;

  *(unsigned short*)(buf+0) = (unsigned short)(((param_1 & 0xff) << 8) | ((param_1 >> 8) & 0xff));
  buf[2] = (unsigned char)(param_2 >> 24);
  buf[3] = (unsigned char)(param_2 >> 16);
  *(unsigned short*)(buf+4) = (unsigned short)(((param_2 & 0xff) << 8) | ((param_2 >> 8) & 0xff));
  *(unsigned int*)(buf+8) = param_3;

  do {
    int *piVar1 = *(volatile int **)0x20007bc0UL;
    fp_t fn = *(volatile fp_t*)((char*)piVar1 + 4);
    iVar2 = fn(buf, 6);
    if (iVar2 == 0) return 0;
    cVar3 = cVar3 - 1;
    attr_store_retry_delay(1);
  } while (cVar3 != 0);
  return 0xffffffff;
}

