#include "g1_app_symbols.h"
/* named: get_demo_image_source_from_flash */
/* Reconstructed get_demo_image_source_from_flash @ 0x365ec  (parity: 300/300 trials, PROVEN) */
extern void DEBUG_PRINT(int,...);
extern int  get_device_info(void);
extern void pixelto4bithex_for_flash(int,int);
extern int  malloc(int);
extern void heap_free(int);
extern void printf(int);
extern int  FUN_0007d1c8(void*);
extern void memcpy(int,int,int);
extern void memset_bytes(void*,int,int);
extern int  strncmp(void*,int,int);
#define VI(a) (*(volatile int*)(a))
#define VB(a) (*(volatile unsigned char*)(a))
typedef int (*fp_t)(int,int,void*,int);

void get_demo_image_source_from_flash(void){
  int iVar3,iVar5,iVar6,iVar7,iVar10,iVar11,iVar14; int uVar4;
  int puVar2, pcVar12;
  int local_60[3]; short local_54v;
  int local_50[2]; unsigned char auStack_48[8]; short local_42;
  puVar2 = malloc(0x50);
  if (puVar2 == 0) { DEBUG_PRINT("[%s-%d]malloc error \n" /*=0xa8d69*/,"get_demo_image_source_from_flash" /*=0xa8e27*/,0x54); return; }
  memset_bytes((void*)puVar2,0,0x50);
  iVar3 = get_device_info();
  pcVar12 = VI(iVar3+0x1030);
  uVar4 = get_device_info();
  iVar3 = ((fp_t)pcVar12)(uVar4,0x1c0000,(void*)puVar2,0x50);
  if (iVar3 != 0) { DEBUG_PRINT("[%s-%d] read pic from flash failed !\n" /*=0xa8d7f*/,"get_demo_image_source_from_flash" /*=0xa8e27*/,0x5a); goto END; }
  local_60[0]=VI(puVar2); local_60[1]=VI(puVar2+4); local_60[2]=VI(puVar2+8);
  local_54v=(short)VI(puVar2+0xc);
  iVar3 = strncmp(local_60,"BM" /*=0xa8da5*/,2);
  if (iVar3 != 0) { DEBUG_PRINT("File is not BMP format \n" /*=0xa8da8*/); goto END; }
  { int s=puVar2+0xe; int d=0;
    do { local_50[d]=VI(s); local_50[d+1]=VI(s+4); s+=8; d+=2; } while (s != puVar2+0x36); }
  iVar3 = FUN_0007d1c8((void*)((int)&local_60[0]+ ( (int)&local_60[2] - (int)&local_60[0]) +2)); /* uStack_58+2 */
  iVar5 = FUN_0007d1c8(&local_50[1]);
  iVar6 = FUN_0007d1c8(auStack_48);
  if (local_42 == 1) {
    iVar10 = iVar5 + 7;
    VI(((uintptr_t)&g_pixel4bit_bitpos) /*=0x20009fc4*/) = 0;
    if (iVar10 < 0) iVar10 = iVar5 + 0xe;
    VI(((uintptr_t)&g_pixel4bit_row_buf_off) /*=0x20009fc8*/) = 0;
    iVar11 = iVar5 + 0x1f;
    if (iVar11 < 0) iVar11 = iVar5 + 0x3e;
    iVar14 = iVar3 + 0x1c0000 + (iVar6 + -1) * (iVar11 >> 5) * 4;
    for (iVar3 = 0; iVar3 < iVar6; iVar3 = iVar3 + 1) {
      VI(((uintptr_t)&g_pixel4bit_bitpos) /*=0x20009fc4*/) = 0;
      memset_bytes((void*)puVar2,0,0x50);
      iVar7 = get_device_info();
      pcVar12 = VI(iVar7+0x1030);
      uVar4 = get_device_info();
      iVar7 = ((fp_t)pcVar12)(uVar4,iVar14,(void*)puVar2,iVar10>>3);
      if (iVar7 != 0) { DEBUG_PRINT("[%s-%d] read pic from flash failed !\n" /*=0xa8d7f*/,"get_demo_image_source_from_flash" /*=0xa8e27*/,0x7e); goto END; }
      for (iVar7 = 0; iVar7 < iVar10>>3; iVar7 = iVar7 + 1) {
        pixelto4bithex_for_flash((int)(unsigned char)~VB(puVar2+iVar7), iVar5);
      }
      if (VI(((uintptr_t)&g_pixel4bit_row_buf) /*=0x20009fcc*/) != 0) {
        VI(((uintptr_t)&g_pixel4bit_row_buf_off) /*=0x20009fc8*/) = 0;
        iVar7 = get_device_info();
        memcpy(VI(iVar7 + iVar3*4 + 0xb90), VI(((uintptr_t)&g_pixel4bit_row_buf) /*=0x20009fcc*/), 0x140);
      }
      iVar14 = iVar14 + (iVar11 >> 5) * -4;
    }
  } else {
    printf("Unsupported bit depth - %d\r\n" /*=0xa8dc1*/);
  }
END:
  heap_free(puVar2);
}

