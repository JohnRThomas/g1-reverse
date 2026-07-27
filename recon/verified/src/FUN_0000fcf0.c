/* Reconstructed FUN_0000fcf0 @ 0xfcf0 */
#include <stdint.h>
extern void FUN_000254a0(void*,void*),FUN_0007c3c2(void*),FUN_00074844(int,int),FUN_000250f8(void*,void*,void*),FUN_00024d40(void);
extern uint32_t FUN_00024d2c(void);
extern uint64_t FUN_0000d824(int);            /* __floatsidf : soft, r0 -> r0:r1 */
extern double   FUN_00075acc(double,double);  /* pow         : hard, d0,d1 -> d0 */
extern uint64_t FUN_0000d588(uint64_t,uint64_t); /* __aeabi_dsub: soft, r0:r1,r2:r3 */
extern uint32_t FUN_0000dee8(uint64_t);       /* __truncdfsf2: soft, r0:r1 -> r0 */
void FUN_0000fcf0(uint8_t *s){volatile uint8_t*busy=(uint8_t*)0x20018c66,*flag=(uint8_t*)0x20003023;volatile uint16_t*last=(uint16_t*)0x2000f6e4;volatile float*deadline=(float*)0x20007a04;
 FUN_000254a0(s,(void*)busy);*busy=1;uint8_t next=s[5];
 switch(next){case 1:FUN_0007c3c2(s);s[5]=2;*busy=1;s[2]=0;return;
 case 2:FUN_00074844(0x667,0);next=3;break;
 case 3:if(!s[2]){if(!s[7]){
   /* shipped 0xfd4e (`cbnz *flag`) and 0xfd54 (`bne s[0xb]!=s[0xc]`)
    * jump to 0xfd68, SKIPPING the `strh r3,[r0]` at 0xfd66: *last is
    * refreshed ONLY when the write is reached through the d>20 test. */
   if(*flag||s[0xb]!=s[0xc])goto st25dv_write_3;
   {int d=(int)s[0x13]-(int)*last;if(d<0)d=-d;if(d<=20)goto no_write_3;}
   *last=s[0x13];
  st25dv_write_3:s[0xb]=s[0xc];FUN_000250f8(s+7,s+0x11,s+0x1c);*flag=0;
  no_write_3:s[5]=4;}if(s[1])s[1]=0;*deadline=150.0f;FUN_00024d40();return;}next=12;break;
 case 4:if((float)FUN_00024d2c()<=*deadline)return;next=s[7]?5:9;break;
 case 5:case 6:case 7:case 9:if(!s[7]){union{double d;uint64_t u;}n,p,r;union{float f;uint32_t u;}o;n.u=FUN_0000d824((int)s[0xb]+3);p.d=FUN_00075acc(2.0,n.d);r.u=FUN_0000d588(p.u,0x4049000000000000ULL);o.u=FUN_0000dee8(r.u);*deadline=o.f;}FUN_00024d40();next=10;break;
 case 10:if(!s[1]&&(float)FUN_00024d2c()<*deadline)return;next=11;break;
 case 11:if(!s[1]){if(s[7])return;next=3;}else if(s[2]){if(s[7])return;next=12;}else{if(s[7])return;next=2;}break;
 case 12:s[7]=2;s[0xb]=0x13;FUN_000250f8(s+7,s+0x11,s+0x1c);*flag=1;s[1]=0;FUN_00024d40();next=14;break;
 case 14:FUN_00024d40();return;default:return;}s[5]=next;}
