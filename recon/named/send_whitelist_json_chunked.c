/* named: send_whitelist_json_chunked */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed send_whitelist_json_chunked @ 0x35498  (parity: 228/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int debug_print(int,...);
extern int convert_app_whitelist_to_json(int,...);
extern int malloc(int,...);
extern int heap_free(int,...);
extern int memcpy(int,...);
extern int memset_bytes(int,...);
typedef int (*codeptr)(int,...);
void send_whitelist_json_chunked(int param_1,int param_2)
{
  volatile int *E = (volatile int*)0x20007554UL;
  int iVar1 = malloc(0x15e3);
  if (iVar1 == 0) {
    if (*E != 0) { debug_print(0xa893c,0xa8a33,0x237); return; }
    DEBUG_PRINT(0xa893c,0xa8a33,0x237); return;
  }
  *(volatile unsigned char*)(param_2+1) = 0x6a;
  memset_bytes(iVar1,0,0x15e3,0x6a,param_1);
  unsigned int uVar2 = convert_app_whitelist_to_json(iVar1);
  if (uVar2 != 0) {
    unsigned int uVar11 = 0;
    unsigned int uVar10 = uVar2 % 0x11;
    unsigned int uVar12 = (0x11 - uVar10) & 0xff;
    *(volatile char*)(param_2+1) = (char)(uVar2/0x11) + 1;
    int *puVar13 = (int*)(param_2+3);
    int *puVar3;
    while (1) {
      puVar3 = (int*)(uVar11*0x11 + iVar1);
      if (uVar11 == uVar2/0x11) break;
      *(volatile char*)(param_2+2) = (char)uVar11;
      int *puVar5 = puVar3;
      int *puVar8 = puVar13;
      do { *puVar8 = *puVar5; puVar5++; puVar8++; } while (puVar5 != puVar3+4);
      *(char*)puVar8 = *(char*)puVar5;
      (*(codeptr)(*(int*)(param_1+0xc)))(param_2,0x14);
      uVar11++;
    }
    *(volatile char*)(param_2+2) = (char)uVar11;
    int iVar4;
    codeptr pcVar7;
    if (uVar10 == 0) {
      memset_bytes((int)puVar13,0,uVar12,uVar11&0xff,param_1);
      iVar4 = 3;
      pcVar7 = (codeptr)(*(int*)(param_1+0xc));
    } else {
      iVar4 = uVar10 + 3;
      memcpy((int)puVar13,(int)puVar3,uVar10);
      memset_bytes(param_2+iVar4,0,uVar12);
      pcVar7 = (codeptr)(*(int*)(param_1+0xc));
    }
    pcVar7(param_2,iVar4);
    heap_free(iVar1);
    return;
  }
  if (*E != 0) { debug_print(0xa8952,0xa8a33,0x23f,0); return; }
  DEBUG_PRINT(0xa8952,0xa8a33,0x23f);
}

