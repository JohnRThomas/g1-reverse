/* readable reconstruction; identity: FUN_0000fcf0 @ 0x0000fcf0
 * public-name: FUN_0000fcf0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dcmp_negate_rhs                          <= FUN_0000d588 @ 0x0000d588
 *   __floatsidf                              <= FUN_0000d824 @ 0x0000d824
 *   __truncdfsf2                             <= FUN_0000dee8 @ 0x0000dee8
 *   get_elapsed_ms_since_mark                <= FUN_00024d2c @ 0x00024d2c
 *   set_time_mark                            <= FUN_00024d40 @ 0x00024d40
 *   update_box_presence_flag                 <= FUN_000254a0 @ 0x000254a0
 * address symbols (name @ address):
 *   g_20003023                               @ 0x20003023
 *   g_20007a04                               @ 0x20007a04
 *   g_2000f6e4                               @ 0x2000f6e4
 *   g_20018c66                               @ 0x20018c66
 */
/* Reconstructed FUN_0000fcf0 @ 0xfcf0 */
#include <stdint.h>
#include <math.h>
extern void update_box_presence_flag(void*,void*),FUN_0007c3c2(void*),FUN_00074844(int,int),FUN_000250f8(void*,void*,void*),set_time_mark(void);
extern uint32_t get_elapsed_ms_since_mark(void),__floatsidf(uint32_t); extern double FUN_00075acc(uint32_t,uint32_t),__truncdfsf2(void);
extern void dcmp_negate_rhs(double,double);
void FUN_0000fcf0(uint8_t *s){volatile uint8_t*busy=(uint8_t*)0x20018c66,*flag=(uint8_t*)0x20003023;volatile uint16_t*last=(uint16_t*)0x2000f6e4;volatile float*deadline=(float*)0x20007a04;
 update_box_presence_flag(s,(void*)busy);*busy=1;uint8_t next=s[5];
 switch(next){case 1:FUN_0007c3c2(s);s[5]=2;*busy=1;s[2]=0;return;
 case 2:FUN_00074844(0x667,0);next=3;break;
 case 3:if(!s[2]){if(!s[7]){int d=(int)s[0x13]-(int)*last;if(d<0)d=-d;if(d>20)*last=s[0x13];if(*flag||s[0xb]!=s[0xc]||d>20){s[0xb]=s[0xc];FUN_000250f8(s+7,s+0x11,s+0x1c);*flag=0;}s[5]=4;}if(s[1])s[1]=0;*deadline=150.0f;set_time_mark();return;}next=12;break;
 case 4:if((float)get_elapsed_ms_since_mark()<=*deadline)return;next=s[7]?5:9;break;
 case 5:case 6:case 7:case 9:if(!s[7]){uint32_t x=__floatsidf((uint8_t)(s[0xb]+3));double y=FUN_00075acc(0,x);dcmp_negate_rhs(y,3.140625);*deadline=(float)__truncdfsf2();}set_time_mark();next=10;break;
 case 10:if(!s[1]&&(float)get_elapsed_ms_since_mark()<*deadline)return;next=11;break;
 case 11:if(!s[1]){if(s[7])return;next=3;}else if(s[2]){if(s[7])return;next=12;}else{if(s[7])return;next=2;}break;
 case 12:s[7]=2;s[0xb]=0x13;FUN_000250f8(s+7,s+0x11,s+0x1c);*flag=1;s[1]=0;set_time_mark();next=14;break;
 case 14:set_time_mark();return;default:return;}s[5]=next;}
