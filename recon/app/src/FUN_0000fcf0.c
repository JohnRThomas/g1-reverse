/* Reconstructed FUN_0000fcf0 @ 0xfcf0 */
#include <stdint.h>
extern void FUN_000254a0(void*,void*),FUN_0007c3c2(void*),FUN_00074844(int,int),FUN_000250f8(void*,void*,void*),FUN_00024d40(void);
extern uint32_t FUN_00024d2c(void),FUN_0000d824(uint32_t); extern double FUN_00075acc(uint32_t,uint32_t),FUN_0000dee8(void);
extern void FUN_0000d588(double,double);
void FUN_0000fcf0(uint8_t *s){volatile uint8_t*busy=(uint8_t*)0x20018c66,*flag=(uint8_t*)0x20003023;volatile uint16_t*last=(uint16_t*)0x2000f6e4;volatile float*deadline=(float*)0x20007a04;
 FUN_000254a0(s,(void*)busy);*busy=1;uint8_t next=s[5];
 switch(next){case 1:FUN_0007c3c2(s);s[5]=2;*busy=1;s[2]=0;return;
 case 2:FUN_00074844(0x667,0);next=3;break;
 case 3:if(!s[2]){if(!s[7]){int d=(int)s[0x13]-(int)*last;if(d<0)d=-d;if(d>20)*last=s[0x13];if(*flag||s[0xb]!=s[0xc]||d>20){s[0xb]=s[0xc];FUN_000250f8(s+7,s+0x11,s+0x1c);*flag=0;}s[5]=4;}if(s[1])s[1]=0;*deadline=150.0f;FUN_00024d40();return;}next=12;break;
 case 4:if((float)FUN_00024d2c()<=*deadline)return;next=s[7]?5:9;break;
 case 5:case 6:case 7:case 9:if(!s[7]){uint32_t x=FUN_0000d824((uint8_t)(s[0xb]+3));double y=FUN_00075acc(0,x);FUN_0000d588(y,3.140625);*deadline=(float)FUN_0000dee8();}FUN_00024d40();next=10;break;
 case 10:if(!s[1]&&(float)FUN_00024d2c()<*deadline)return;next=11;break;
 case 11:if(!s[1]){if(s[7])return;next=3;}else if(s[2]){if(s[7])return;next=12;}else{if(s[7])return;next=2;}break;
 case 12:s[7]=2;s[0xb]=0x13;FUN_000250f8(s+7,s+0x11,s+0x1c);*flag=1;s[1]=0;FUN_00024d40();next=14;break;
 case 14:FUN_00024d40();return;default:return;}s[5]=next;}
