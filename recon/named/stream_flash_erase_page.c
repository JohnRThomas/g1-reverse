/* readable reconstruction; identity: FUN_0004e124 @ 0x0004e124
 * public-name: stream_flash_erase_page
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   stream_flash_erase_page                  <= FUN_0004e124 @ 0x0004e124
 *   flash_get_page_info_by_offs              <= FUN_00083a92 @ 0x00083a92
 * address symbols (name @ address):
 *   rodata_880d8                             @ 0x000880d8
 *   rodata_f1015                             @ 0x000f1015
 *   rodata_f1036                             @ 0x000f1036
 */
/* Reconstructed FUN_0004e124 @ 0x4e124  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);
extern int flash_get_page_info_by_offs(unsigned int,unsigned int,void*);
struct property_result { int selected; unsigned int context, count; };
_Static_assert(sizeof(struct property_result) == 12, "property result layout");
int stream_flash_erase_page(int param_1,unsigned int param_2){
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
      else{ s.b=0x000f1036; s.a=3; s.c=iVar2; z_log_msg_runtime_create(0x000880d8,0x1840,&s,0); iVar1=iVar2; }
    }
  } else { s.b=0x000f1015; s.a=3; s.c=iVar1; z_log_msg_runtime_create(0x000880d8,0x1840,&s,0); }
  return iVar1;
}
