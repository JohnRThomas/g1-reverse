#include "g1_app_symbols.h"
/* named: pixelto4bithex_for_flash */
/* Reconstructed pixelto4bithex_for_flash @ 0x36558  (parity: 300/300 trials, PROVEN) */

extern int malloc(int);
extern void memset_bytes(int,int,int);
extern void DEBUG_PRINT(int,int,int,int);
void pixelto4bithex_for_flash(int param_1,int param_2,int param_3,int param_4){
  if(*(volatile int*)((uintptr_t)&g_pixel4bit_row_buf) /*=0x20009fcc*/==0){
    int iVar4=malloc(0x140);
    *(volatile int*)((uintptr_t)&g_pixel4bit_row_buf) /*=0x20009fcc*/=iVar4;
    if(iVar4==0){ DEBUG_PRINT("[%s-%d]malloc error \n" /*=0xa8d69*/,"pixelto4bithex_for_flash" /*=0xa8e48*/,0x28,param_4); return; }
    memset_bytes(iVar4,0,0x140);
  }
  unsigned uVar5=0;
  do{
    int iVar4=*(volatile int*)((uintptr_t)&g_pixel4bit_bitpos) /*=0x20009fc4*/;
    if(param_2<=iVar4) return;
    *(volatile int*)((uintptr_t)&g_pixel4bit_bitpos) /*=0x20009fc4*/=iVar4+2;
    unsigned uVar7=((unsigned)param_1<<(uVar5&0xff))&0xc0;
    unsigned char uVar6=(unsigned char)uVar7;
    if(uVar7==0xc0) uVar6=0xff;
    else if(uVar7==0x80) uVar6=0xf0;
    else if(uVar7==0x40) uVar6=0xf;
    else if(uVar7!=0) uVar6=0x99;
    *(volatile unsigned char*)((unsigned)(*(volatile int*)((uintptr_t)&g_pixel4bit_row_buf) /*=0x20009fcc*/)+(unsigned)(*(volatile int*)((uintptr_t)&g_pixel4bit_row_buf_off) /*=0x20009fc8*/))=uVar6;
    uVar5+=2;
    *(volatile int*)((uintptr_t)&g_pixel4bit_row_buf_off) /*=0x20009fc8*/=(*(volatile int*)((uintptr_t)&g_pixel4bit_row_buf_off) /*=0x20009fc8*/)+1;
  }while(uVar5!=8);
}

