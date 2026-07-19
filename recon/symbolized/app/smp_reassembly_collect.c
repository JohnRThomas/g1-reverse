#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00080b42 @ 0x00080b42
 * public-name: smp_reassembly_collect
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_packet_alloc                         <= FUN_000526e4 @ 0x000526e4
 *   smp_reassembly_collect                   <= FUN_00080b42 @ 0x00080b42
 *   net_buf_simple_add_mem                   <= FUN_00083740 @ 0x00083740
 */
/* Reconstructed FUN_00080b42 @ 0x80b42  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern int smp_packet_alloc(void);
extern void net_buf_simple_add_mem(int,int,uint);
uint smp_reassembly_collect(int param_1,int param_2,uint param_3){
  int iVar1;
  if(*(volatile int*)(param_1+0x40)==0){
    if(param_3<8) return 0xffffffc3;
    uint16_t h=*(volatile uint16_t*)(param_2+2);
    uint uVar2=(((h&0xff)<<8)|(h>>8))+8;
    uint uVar3=uVar2&0xffff;
    if(param_3>0x9ab || uVar3>0x9ab) return 0xffffffc1;
    if(uVar3<param_3) return 0xffffff75;
    iVar1=smp_packet_alloc();
    *(volatile int*)(param_1+0x40)=iVar1;
    if(iVar1==0) return 0xfffffff4;
    *(volatile int16_t*)(param_1+0x44)=(int16_t)uVar2;
  } else if(*(volatile uint16_t*)(param_1+0x44)<param_3){
    return 0xffffff75;
  }
  net_buf_simple_add_mem(*(volatile int*)(param_1+0x40)+0xc,param_2,param_3);
  param_3=*(volatile uint16_t*)(param_1+0x44)-param_3;
  *(volatile int16_t*)(param_1+0x44)=(int16_t)param_3;
  return param_3&0xffff;
}
