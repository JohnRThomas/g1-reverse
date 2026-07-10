/* named: request_ancs_attr_ext */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006ae8  g_ancs_client                
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed request_ancs_attr_ext @ 0x191e4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern unsigned strlen(unsigned);
extern int ancs_get_conn_ctx(void);
extern void debug_print(unsigned,...);
extern int bt_ancs_request_attrs(unsigned,unsigned,unsigned);
extern void thunk_FUN_00074844(int,int);
extern int thunk_FUN_0007f7d2(unsigned,unsigned,unsigned,unsigned);
int request_ancs_attr_ext(unsigned param_1, unsigned param_2, unsigned param_3)
{
  unsigned uVar1, uVar2; unsigned short *puVar3; int iVar4, iVar5; unsigned uVar6;
  iVar4 = ancs_get_conn_ctx();
  iVar5 = bt_ancs_request_attrs(0x20006ae8, 0x20006aac, 0x0001827d);
  puVar3 = (unsigned short*)0x20006aa0;
  uVar6 = 0;
  do {
    if ((((*(int*)(puVar3+2) == 0) && (*puVar3 != 0)) && (**(char**)(puVar3+4) != 0)) &&
        (*(char*)(iVar4+0x44) != 0)) goto LAB_5a;
    thunk_FUN_00074844(0x21, 0);
    uVar6 = uVar6 + 1 & 0xffff;
  } while (uVar6 != 0x3e9);
  if (0 < *(int*)0x2000230c) {
    param_1 = strlen(*(unsigned*)(puVar3+4));
    param_2 = (unsigned)*(unsigned char*)(iVar4+0x44);
    if (*(int*)0x20007554 == 0)
      DEBUG_PRINT(0x0009ab1e, 0x0009b148, *(unsigned*)(puVar3+2), (unsigned)*puVar3, param_1, param_2);
    else
      debug_print(0x0009ab1e, 0x0009b148, *(unsigned*)(puVar3+2));
  }
  if (*(int*)(puVar3+2) == 0) {
LAB_5a:
    if ((*puVar3 != 0) && (**(char**)(puVar3+4) != 0)) {
      if (*(int*)0x20007554 == 0) {
        DEBUG_PRINT(0x0009abbd, *(char**)(puVar3+4), uVar6, 0, param_1, param_2, param_3);
        uVar1 = 0x20006ae8; uVar2 = 0x0001827d;
      } else {
        debug_print(0x0009abbd);
        uVar1 = 0x20006ae8; uVar2 = 0x0001827d;
      }
      for (; uVar6 < 200; uVar6 = uVar6 + 1 & 0xffff) {
        iVar5 = thunk_FUN_0007f7d2(uVar1, *(unsigned*)(puVar3+4), *puVar3, uVar2);
        if (iVar5 == 0) goto LAB_86;
        thunk_FUN_00074844(0xa4, 0);
      }
      if (iVar5 != 0) DEBUG_PRINT(0x0009abdc, iVar5);
    }
  }
LAB_86:
  if (*(int*)0x20007554 == 0)
    DEBUG_PRINT(0x0009ac14, *(unsigned*)(puVar3+2), (unsigned)*puVar3, uVar6, param_1, param_2);
  else
    debug_print(0x0009ac14, *(unsigned*)(puVar3+2), (unsigned)*puVar3, uVar6);
  return iVar5;
}

