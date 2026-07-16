/* Reconstructed FUN_00019718 @ 0x19718 CFG_VERIFY_PREFIX_FIRST */
#include <stdint.h>
extern void FUN_00086534(void*,int,int),FUN_00018b6c(void),FUN_00018e04(void),thunk_FUN_00074844(int,int);
extern uint8_t *FUN_000167a8(void); extern void FUN_0007c0a8(int),FUN_00072908(void*);
extern int FUN_00018ff8(void*); extern void FUN_000191e4(void),FUN_00018bb4(void*),FUN_00086c78(void*,int,int),FUN_0001965c(void*);
extern void DEBUG_PRINT(uint32_t,...),FUN_00019c70(void);
void FUN_00019718(uint8_t *c,uint32_t p2,uint32_t p3,uint32_t p4){
 volatile int *lv=(int*)0x2000230c,*sink=(int*)0x20007554; volatile uint32_t *ev=(uint32_t*)0x20006aac;
 if(*lv>2){if(!*sink)DEBUG_PRINT(0x99969,0x9b0d8,p3,0,p4);else FUN_00019c70();}
 FUN_00086534(c+0x200,0,10);FUN_00086534(c+0x1e8,0,10);FUN_00018b6c();FUN_00018e04();thunk_FUN_00074844(0x28000,0);
 for(;;){uint8_t*g=FUN_000167a8();if(g[1]==1){thunk_FUN_00074844(0x28000,0);continue;}g=FUN_000167a8();if(g[1]==8){thunk_FUN_00074844(0x28000,0);continue;}g=FUN_000167a8();
  if((*(uint16_t*)(g+0x105c)&0x80)==0){FUN_0007c0a8(1000);continue;}
  if(*lv>0){if(!*sink)DEBUG_PRINT(0x9adc7,0x9b0d8);else FUN_00019c70();}FUN_00072908(c+0x200);
  if(FUN_00018ff8((void*)ev)==0){if(*lv>0){if(!*sink)DEBUG_PRINT(0x9adf5,0x9b0d8,*ev,((uint8_t*)ev)[4]);else FUN_00019c70();}
   if(((uint8_t*)ev)[4]<2){FUN_000191e4();if(*lv>0){if(!*sink)DEBUG_PRINT(0x9ae34,0x9b0d8);else FUN_00019c70();}FUN_00072908(c+0x1e8);}
   else{*(uint32_t*)(c+0x1e4)=2;*(uint32_t*)(c+0x3c)=*ev;c[0x41]=0;c[0x44]=0x30;c[0x64]=0x30;c[0x42]=0;FUN_00018bb4(c+0x34);FUN_00086c78(c+0x34,0,0x1b4);if(*lv>0){if(!*sink)DEBUG_PRINT(0x9ae92,0x9b0d8);else FUN_00019c70();}}
   FUN_0001965c(c);if(*lv>0){if(!*sink)DEBUG_PRINT(0x9aef3,0x9b0d8);else FUN_00019c70();}}
 }}
