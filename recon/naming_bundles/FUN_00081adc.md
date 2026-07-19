### FUN_00081adc  @ 0x00081adc  (size=84)

callers (2): FUN_00053bd8, send_conn_le_param_update
callees (5): FUN_00057394, FUN_000573f4, net_buf_unref, net_buf_simple_add, bt_conn_create_pdu

```c
/* readable reconstruction; identity: FUN_00081adc @ 0x00081adc
 * public-name: FUN_00081adc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   bt_conn_create_pdu                       <= FUN_00081820 @ 0x00081820
 */
/* Reconstructed FUN_00081adc @ 0x81adc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern long long FUN_00057394(void);
extern int FUN_000573f4(int,int,int);
extern int net_buf_unref(int);
extern void* net_buf_simple_add(int,int);
extern int bt_conn_create_pdu(int,int,int,int,int,int);
int FUN_00081adc(int param_1, int param_2){
  unsigned long long uVar5 = (unsigned long long)FUN_00057394();
  volatile uint16_t *puVar4 = (volatile uint16_t*)(uintptr_t)(uint32_t)(uVar5 >> 32);
  int iVar1 = FUN_000573f4(0x12, (int)(uint32_t)uVar5, 8);
  if(iVar1 == 0){
    return -0xc;
  }
  volatile uint16_t *puVar2 = (volatile uint16_t*)net_buf_simple_add(iVar1+0xc, 8);
  puVar2[0] = puVar4[0];
  puVar2[1] = puVar4[1];
  puVar2[2] = puVar4[2];
  puVar2[3] = puVar4[3];
  int iVar3 = bt_conn_create_pdu(param_1, 5, iVar1, 0, 0, param_2);
  if(iVar3 != 0){
    net_buf_unref(iVar1);
  }
  return iVar3;
}
```