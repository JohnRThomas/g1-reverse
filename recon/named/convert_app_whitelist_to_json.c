/* readable reconstruction; identity: FUN_000352e8 @ 0x000352e8
 * public-name: convert_app_whitelist_to_json
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   cjson_delete                             <= FUN_00064b1c @ 0x00064b1c
 *   cjson_create_array                       <= FUN_00064c8c @ 0x00064c8c
 *   cjson_create_object                      <= FUN_00064ca4 @ 0x00064ca4
 *   free                                     <= FUN_00076d7c @ 0x00076d7c
 *   cjson_print_unformatted                  <= FUN_0008501a @ 0x0008501a
 *   cjson_add_item_to_object_thunk           <= FUN_00085046 @ 0x00085046
 *   cjson_add_bool_to_object                 <= FUN_0008504c @ 0x0008504c
 *   cjson_add_string_to_object               <= FUN_0008509e @ 0x0008509e
 *   strcpy                                   <= FUN_00086fee @ 0x00086fee
 * address symbols (name @ address):
 *   rodata_9a1dd                             @ 0x0009a1dd
 *   rodata_9e1b6                             @ 0x0009e1b6
 *   rodata_9e235                             @ 0x0009e235
 *   rodata_a862c                             @ 0x000a862c
 *   rodata_a864e                             @ 0x000a864e
 *   rodata_a866e                             @ 0x000a866e
 *   rodata_a869b                             @ 0x000a869b
 *   rodata_a88a9                             @ 0x000a88a9
 *   rodata_a88d8                             @ 0x000a88d8
 *   rodata_a892b                             @ 0x000a892b   [INLINED -- G6 literal batch]
 *   rodata_a8a51                             @ 0x000a8a51   [INLINED -- G6 literal batch]
 *   rodata_f33e4                             @ 0x000f33e4
 *   rodata_f3630                             @ 0x000f3630
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_whitelist_buffer                   @ 0x2001a22c
 */
/* Reconstructed convert_app_whitelist_to_json @ 0x352e8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
extern int  strlen(int);
extern void cjson_delete(volatile int*);
extern int  cjson_create_array(void);
extern int  cjson_create_object(void);
extern void free(int);
extern int  cjson_print_unformatted(int);
extern void cjson_add_item_to_object_thunk(int,int,int);
extern void cjson_add_bool_to_object(int,int,int);
extern void cjson_add_string_to_object(int,int,void*);
extern void strcpy(int,int);
extern void thunk_FUN_00084f2e(int,int,const void *,unsigned int);

int convert_app_whitelist_to_json(int param_1,int param_2,int param_3){
  volatile int *g50 = (volatile int*)0x20007554UL;
  volatile unsigned char *pbVar1 = (volatile unsigned char*)0x2001a22cUL;
  int iVar3,iVar9=0,iVar4,iVar5; unsigned int uVar10,uVar8; int uVar6=0,uVar7=0,uVar2;
  iVar3 = param_1;
  if (param_1 == 0) { uVar6=0x1f1; iVar9=*g50; uVar7=0x000a88a9; goto final; }
  iVar9 = cjson_create_object();
  if (iVar9 == 0) { uVar6=0x1fa; iVar9=*g50; uVar7=0x000a88be; goto final; }
  cjson_add_bool_to_object(iVar9,0x000a862c,(*pbVar1)&1);
  cjson_add_bool_to_object(iVar9,0x000a864e,((unsigned int)*pbVar1<<0x1e)>>0x1f);
  cjson_add_bool_to_object(iVar9,0x000a869b,((unsigned int)*pbVar1<<0x1d)>>0x1f);
  cjson_add_bool_to_object(iVar9,0x000a866e,((unsigned int)*pbVar1<<0x1c)>>0x1f);
  iVar3 = cjson_create_object();
  if (iVar3 == 0) { uVar7=0x206; iVar3=*g50; uVar6=0x000a88d8; goto inner; }
  cjson_add_bool_to_object(iVar3,0x0009e235,((unsigned int)*pbVar1<<0x1b)>>0x1f);
  iVar4 = cjson_create_array();
  if (iVar4 == 0) { uVar7=0x20e; iVar3=*g50; uVar6=0x000a88f1; goto inner; }
  uVar10 = 0;
  for(;;){
    uVar8 = uVar10 & 0xff;
    if (pbVar1[1] <= uVar8) {
      cjson_add_item_to_object_thunk(iVar3,0x000f3630,iVar4);
      cjson_add_item_to_object_thunk(iVar9,0x0009e1b6,iVar3);
      uVar6 = cjson_print_unformatted(iVar9);
      if (*g50==0) log_message(((unsigned long)"cJsonStr is %s \n"),uVar6); else debug_print(((unsigned long)"cJsonStr is %s \n"),uVar6);
      strcpy(param_1,uVar6);
      uVar2 = strlen(uVar6);
      free(uVar6);
      cjson_delete(iVar9);
      return (unsigned short)uVar2;
    }
    iVar5 = cjson_create_object();
    uVar10 = uVar10 + 1;
    if (iVar5 == 0) break;
    cjson_add_string_to_object(iVar5,0x0009a1dd,(void*)(pbVar1 + uVar8*0x38 + 2));
    cjson_add_string_to_object(iVar5,0x000f33e4,(void*)(pbVar1 + uVar8*0x38 + 0x2a));
    thunk_FUN_00084f2e(iVar4,iVar5,
                       (const void *)(pbVar1 + uVar8*0x38 + 0x2a),uVar10);
  }
  uVar7=0x219; iVar3=*g50; uVar6=0x000a8912;
inner:
  if (iVar3 == 0) log_message(uVar6,((unsigned long)"convert_app_whitelist_to_json"),uVar7); else debug_print(uVar6,((unsigned long)"convert_app_whitelist_to_json"),uVar7);
  cjson_delete(iVar9);
  return 0;
final:
  if (iVar9 == 0) log_message(uVar7,((unsigned long)"convert_app_whitelist_to_json"),uVar6,iVar9,iVar3,param_2,param_3); else debug_print(uVar7,((unsigned long)"convert_app_whitelist_to_json"),uVar6,iVar9,iVar3,param_2,param_3);
  return 0;
}
