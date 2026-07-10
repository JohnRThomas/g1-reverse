/* named: bt_conn_le_param_update */
/* Reconstructed bt_conn_le_param_update @ 0x8157a  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int send_conn_le_param_update(int);
extern void atomic_and_2(void*,int);
unsigned bt_conn_le_param_update(int param_1, uint16_t *param_2){
  volatile unsigned *puVar1=(volatile unsigned*)(param_1+4);
  unsigned uVar2;
  if( *(uint16_t*)(param_1+0xa6) < param_2[0] || param_2[1] < *(uint16_t*)(param_1+0xa6)
      || *(uint16_t*)(param_1+0xac) != param_2[2] || *(uint16_t*)(param_1+0xae) != param_2[3]){
    uVar2 = (*puVar1 << 0x18) >> 0x1f;
    if((int)(*puVar1<<0x18) < 0){ return send_conn_le_param_update(param_1); }
    *(uint16_t*)(param_1+0xa8)=param_2[0];
    *(uint16_t*)(param_1+0xaa)=param_2[1];
    *(uint16_t*)(param_1+0xb0)=param_2[2];
    *(uint16_t*)(param_1+0xb2)=param_2[3];
    *puVar1 |= 0x200;
  } else { atomic_and_2((void*)puVar1, 0xfffffdff); uVar2 = 0xffffff88; }
  return uVar2;
}

