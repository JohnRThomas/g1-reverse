#include "g1_app_symbols.h"
/* named: FUN_00052d58 */
/* globals referenced:
//   0x200020d4  g_bt_dev.ncmd_sem            [g_bt_dev (base 0x20002000) + 0xd4: semaphore gating outstanding HCI command credits, taken in bt_send/bt_hci_driver_close]
*/
/* Reconstructed FUN_00052d58 @ 0x52d58  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004d944(int,...);
extern int settings_name_next(int,...);
extern int strncmp(int,...);
typedef int (*codeptr)(int,...);
unsigned int FUN_00052d58(int param_1, int param_2, codeptr param_3, int param_4)
{
  volatile int *g = (volatile int*)((uintptr_t)&g_ble_dev_ncmd_sem) /*=0x200020d4*/;
  int iVar3, uVar2; unsigned int uVar4; unsigned buf[16];
  if ((int)((unsigned)*g << 0x1f) < 0) {
    if (param_1 == 0) {
      buf[0]=2; buf[1]="Insufficient number of arguments" /*=0xf2b65*/;
      FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88178*/,0x1040,buf,0);
      return 0xfffffffe;
    }
    uVar2 = settings_name_next(param_1, buf);
    iVar3 = strncmp(param_1, "id" /*=0x9a1dd*/, uVar2);
    if (iVar3 == 0) {
      int t = *g;
      unsigned uVar5 = (unsigned)t << 0x1c;
      unsigned uVar6 = uVar5 >> 0x1f;
      if ((int)uVar5 < 0) {
        buf[0]=2; buf[1]="Ignoring identities stored in flash" /*=0xf2b86*/;
        FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88178*/,0x1080,buf);
      } else {
        uVar4 = param_3(param_4, (int)(g - 0x35), 7);
        if (uVar4 < 7) {
          buf[0]=2; buf[1]="Invalid length ID address in storage" /*=0xf2baa*/;
          FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88178*/,0x1040,buf,uVar6);
          g[-0x35] = uVar6;
          *(volatile unsigned char*)((int)g - 0xcd) = (unsigned char)(uVar5 >> 0x1f);
          *(volatile unsigned int*)((int)g - 0xd1) = uVar6;
        } else {
          *(volatile unsigned char*)((int)g - 0xcd) = (unsigned char)(uVar4 / 7);
        }
      }
    } else {
      iVar3 = strncmp(param_1, "name" /*=0xf33e4*/, uVar2, iVar3);
      if (iVar3 != 0) return 0xfffffffe;
      int iStack_48 = param_3(param_4, (int)(g + 0x26), 0x1c);
      if (iStack_48 < 0) {
        buf[0]=3; buf[1]="Failed to read device name from storage (err %zd)" /*=0xf2bcf*/;
        FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88178*/,0x1840,buf,0);
      } else {
        *(volatile unsigned char*)((int)g + iStack_48 + 0x98) = 0;
      }
    }
  }
  return 0;
}

