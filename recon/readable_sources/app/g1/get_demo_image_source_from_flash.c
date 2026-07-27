#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_000365ec @ 0x000365ec
 * public-name: get_demo_image_source_from_flash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   pixelto4bithex_for_flash                 <= FUN_00036558 @ 0x00036558
 *   get_demo_image_source_from_flash         <= FUN_000365ec @ 0x000365ec
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   free                                     <= FUN_00076d7c @ 0x00076d7c
 *   printf                                   <= FUN_000777f0 @ 0x000777f0
 *   ptr_load_u32                             <= FUN_0007d1c8 @ 0x0007d1c8
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   strncmp                                  <= FUN_00087036 @ 0x00087036
 * address symbols (name @ address):
 *   rodata_a8d69                             @ 0x000a8d69   [INLINED -- G6 literal batch]
 *   rodata_a8d7f                             @ 0x000a8d7f   [INLINED -- G6 literal batch]
 *   rodata_a8da5                             @ 0x000a8da5
 *   rodata_a8da8                             @ 0x000a8da8   [INLINED -- G6 literal batch]
 *   rodata_a8dc1                             @ 0x000a8dc1
 *   rodata_a8e27                             @ 0x000a8e27   [INLINED -- G6 literal batch]
 *   g_pixel4bit_bitpos                       @ 0x20009fc4
 *   g_pixel4bit_row_buf_off                  @ 0x20009fc8
 *   g_pixel4bit_row_buf                      @ 0x20009fcc
 */
/* Reconstructed FUN_000365ec @ 0x365ec  (parity: 300/300 trials, PROVEN) */
extern int  get_device_info(void);
extern void pixelto4bithex_for_flash(int,int);
extern int  malloc(int);
extern void free(int);
extern void printf(int);
extern unsigned int ptr_load_u32(unsigned int *);
extern void memcpy(int, int, int);
extern void memset_bytes(void*,int,int);
extern int strncmp(const void*, unsigned long, unsigned int);
#define VI(a) (*(volatile int*)(a))
#define VB(a) (*(volatile unsigned char*)(a))
typedef int (*fp_t)(int,int,void*,int);

void get_demo_image_source_from_flash(void){
  int iVar3,iVar5,iVar6,iVar7,iVar10,iVar11,iVar14; int uVar4;
  int puVar2, pcVar12;
  int local_60[3]; short local_54v;
  int local_50[2]; unsigned char auStack_48[8]; short local_42;
  puVar2 = malloc(0x50);
  if (puVar2 == 0) { log_message(((unsigned long)"[%s-%d]malloc error \n") /*=0xa8d69*/,((unsigned long)"get_demo_image_source_from_flash") /*=0xa8e27*/,0x54); return; }
  memset_bytes((void*)puVar2,0,0x50);
  iVar3 = get_device_info();
  pcVar12 = VI(iVar3+0x1030);
  uVar4 = get_device_info();
  iVar3 = ((fp_t)pcVar12)(uVar4,0x1c0000,(void*)puVar2,0x50);
  if (iVar3 != 0) { log_message(((unsigned long)"[%s-%d] read pic from flash failed !\n") /*=0xa8d7f*/,((unsigned long)"get_demo_image_source_from_flash") /*=0xa8e27*/,0x5a); goto END; }
  local_60[0]=VI(puVar2); local_60[1]=VI(puVar2+4); local_60[2]=VI(puVar2+8);
  local_54v=(short)VI(puVar2+0xc);
  iVar3 = strncmp(local_60,((unsigned long)&rodata_a8da5) /*=0xa8da5*/,2);
  if (iVar3 != 0) { log_message(((unsigned long)"File is not BMP format \n") /*=0xa8da8*/); goto END; }
  { int s=puVar2+0xe; int d=0;
    do { local_50[d]=VI(s); local_50[d+1]=VI(s+4); s+=8; d+=2; } while (s != puVar2+0x36); }
  iVar3 = ptr_load_u32((void*)((int)&local_60[0]+ ( (int)&local_60[2] - (int)&local_60[0]) +2)); /* uStack_58+2 */
  iVar5 = ptr_load_u32(&local_50[1]);
  iVar6 = ptr_load_u32(auStack_48);
  if (local_42 == 1) {
    iVar10 = iVar5 + 7;
    VI(((unsigned long)&g_pixel4bit_bitpos) /*=0x20009fc4*/) = 0;
    if (iVar10 < 0) iVar10 = iVar5 + 0xe;
    VI(((unsigned long)&g_pixel4bit_row_buf_off) /*=0x20009fc8*/) = 0;
    iVar11 = iVar5 + 0x1f;
    if (iVar11 < 0) iVar11 = iVar5 + 0x3e;
    iVar14 = iVar3 + 0x1c0000 + (iVar6 + -1) * (iVar11 >> 5) * 4;
    for (iVar3 = 0; iVar3 < iVar6; iVar3 = iVar3 + 1) {
      VI(((unsigned long)&g_pixel4bit_bitpos) /*=0x20009fc4*/) = 0;
      memset_bytes((void*)puVar2,0,0x50);
      iVar7 = get_device_info();
      pcVar12 = VI(iVar7+0x1030);
      uVar4 = get_device_info();
      iVar7 = ((fp_t)pcVar12)(uVar4,iVar14,(void*)puVar2,iVar10>>3);
      if (iVar7 != 0) { log_message(((unsigned long)"[%s-%d] read pic from flash failed !\n") /*=0xa8d7f*/,((unsigned long)"get_demo_image_source_from_flash") /*=0xa8e27*/,0x7e); goto END; }
      for (iVar7 = 0; iVar7 < iVar10>>3; iVar7 = iVar7 + 1) {
        pixelto4bithex_for_flash((int)(unsigned char)~VB(puVar2+iVar7), iVar5);
      }
      if (VI(((unsigned long)&g_pixel4bit_row_buf) /*=0x20009fcc*/) != 0) {
        VI(((unsigned long)&g_pixel4bit_row_buf_off) /*=0x20009fc8*/) = 0;
        iVar7 = get_device_info();
        memcpy(VI(iVar7 + iVar3*4 + 0xb90), VI(((unsigned long)&g_pixel4bit_row_buf) /*=0x20009fcc*/), 0x140);
      }
      iVar14 = iVar14 + (iVar11 >> 5) * -4;
    }
  } else {
    printf(((unsigned long)&rodata_a8dc1) /*=0xa8dc1*/);
  }
END:
  free(puVar2);
}
