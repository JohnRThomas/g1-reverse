#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00035498 @ 0x00035498
 * public-name: send_whitelist_json_chunked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   convert_app_whitelist_to_json            <= FUN_000352e8 @ 0x000352e8
 *   send_whitelist_json_chunked              <= FUN_00035498 @ 0x00035498
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   free                                     <= FUN_00076d7c @ 0x00076d7c
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a893c                             @ 0x000a893c   [INLINED -- G6 literal batch]
 *   rodata_a8952                             @ 0x000a8952   [INLINED -- G6 literal batch]
 *   rodata_a8a33                             @ 0x000a8a33   [INLINED -- G6 literal batch]
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full reconstruction FUN_00035498 @ 0x35498 (268-byte extent; CFG PASS). */
#include <stdint.h>
#include "../../../headers/g1_log.h"
extern int convert_app_whitelist_to_json(int,...);
extern void *malloc(size_t);
extern void free(void *);
extern int memcpy(int,...);
extern int memset_bytes(int,...);
typedef int (*codeptr)(int,...);
void send_whitelist_json_chunked(int param_1,int param_2)
{
  volatile int *E = (volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
  int iVar1 = malloc(0x15e3);
  if (iVar1 == 0) {
    if (*E != 0) { debug_print(((unsigned long)"[%s-%d] buf is NULL \n") /*=0xa893c*/,((unsigned long)"get_whitelist_app_from_device") /*=0xa8a33*/,0x237); return; }
    log_message(((unsigned long)"[%s-%d] buf is NULL \n") /*=0xa893c*/,((unsigned long)"get_whitelist_app_from_device") /*=0xa8a33*/,0x237); return;
  }
  *(volatile unsigned char *)(param_2+1) = 0x6a;
  memset_bytes(iVar1,0,0x15e3,0x6a,param_1);
  unsigned int uVar2 = convert_app_whitelist_to_json(iVar1);
  if (uVar2 != 0) {
    unsigned int uVar11 = 0;
    unsigned int uVar10 = uVar2 % 0x11;
    unsigned int uVar12 = (0x11 - uVar10) & 0xff;
    *(volatile char *)(param_2+1) = (char)(uVar2/0x11) + 1;
    int *puVar13 = (int*)(param_2+3);
    int *puVar3;
    while (1) {
      puVar3 = (int*)(uVar11*0x11 + iVar1);
      if (uVar11 == uVar2/0x11) break;
      *(volatile char *)(param_2+2) = (char)uVar11;
      int *puVar5 = puVar3;
      int *puVar8 = puVar13;
      do { *puVar8 = *puVar5; puVar5++; puVar8++; } while (puVar5 != puVar3+4);
      *(char*)puVar8 = *(char*)puVar5;
      (*(codeptr)(*(int*)(param_1+0xc)))(param_2,0x14);
      uVar11++;
    }
    *(volatile char *)(param_2+2) = (char)uVar11;
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
    free(iVar1);
    return;
  }
  if (*E != 0) { debug_print(((unsigned long)"[%s-%d] total_len is %d \n") /*=0xa8952*/,((unsigned long)"get_whitelist_app_from_device") /*=0xa8a33*/,0x23f,0); return; }
  log_message(((unsigned long)"[%s-%d] total_len is %d \n") /*=0xa8952*/,((unsigned long)"get_whitelist_app_from_device") /*=0xa8a33*/,0x23f,0);
}
