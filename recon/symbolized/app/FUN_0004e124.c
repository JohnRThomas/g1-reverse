#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004e124 @ 0x0004e124
 * public-name: FUN_0004e124
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_get_page_info_by_offs              <= FUN_00083a92 @ 0x00083a92
 * address symbols (name @ address):
 *   rodata_880d8                             @ 0x000880d8
 *   rodata_f1015                             @ 0x000f1015
 *   rodata_f1036                             @ 0x000f1036
 */
/* Reconstructed FUN_0004e124 @ 0x4e124  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0004d944(unsigned int,unsigned int,void*,int);
extern int flash_get_page_info_by_offs(unsigned int,unsigned int,void*);
struct property_result { int selected; unsigned int context, count; };
_Static_assert(sizeof(struct property_result) == 12, "property result layout");
int FUN_0004e124(int param_1,unsigned int param_2){
  int iVar1,iVar2;
  struct {
    unsigned int pad;
    struct property_result result;
  } local;
  struct{unsigned int a,b; int c;} s;
  iVar1=flash_get_page_info_by_offs(*(unsigned int*)(param_1+0xc),param_2,&local.result);
  if(iVar1==0){
    if(*(int*)(param_1+0x20)!=local.result.selected){
      iVar2=(*(int(**)(unsigned int,int,unsigned int))(*(int*)(*(int*)(param_1+0xc)+8)+8))(*(unsigned int*)(param_1+0xc),local.result.selected,local.result.context);
      if(iVar2==0) *(int*)(param_1+0x20)=local.result.selected;
      else{ s.b=((unsigned long)&rodata_f1036) /*=0xf1036*/; s.a=3; s.c=iVar2; FUN_0004d944(((unsigned long)&rodata_880d8) /*=0x880d8*/,0x1840,&s,0); iVar1=iVar2; }
    }
  } else { s.b=((unsigned long)&rodata_f1015) /*=0xf1015*/; s.a=3; s.c=iVar1; FUN_0004d944(((unsigned long)&rodata_880d8) /*=0x880d8*/,0x1840,&s,0); }
  return iVar1;
}
