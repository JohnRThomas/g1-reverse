/* readable reconstruction; identity: FUN_0005edac @ 0x0005edac
 * public-name: bt_crypto_g2
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sys_memcpy_swap                          <= FUN_0005ec84 @ 0x0005ec84
 *   bt_crypto_g2                             <= FUN_0005edac @ 0x0005edac
 *   bt_crypto_aes_cmac                       <= FUN_000835ae @ 0x000835ae
 * address symbols (name @ address):
 *   rodata_f4240                             @ 0x000f4240
 */
/* Reconstructed FUN_0005edac @ 0x5edac  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int sys_memcpy_swap(void*,int,int);
extern int bt_crypto_aes_cmac(void*,void*,int);
void bt_crypto_g2(int param_1,int param_2,int param_3,int param_4,int *param_5){
  uint8_t buf[0x60];
  sys_memcpy_swap(buf+0x10, param_1, 0x20);
  sys_memcpy_swap(buf+0x30, param_2, 0x20);
  sys_memcpy_swap(buf+0x50, param_4, 0x10);
  sys_memcpy_swap(buf, param_3, 0x10);
  int iVar1 = bt_crypto_aes_cmac(buf, buf+0x10, 0x50);
  if(iVar1 == 0){
    uint32_t local_64 = *(volatile uint32_t*)(buf+0xc);
    uint32_t uVar2 = __builtin_bswap32(local_64);
    uint32_t d = 0x000f4240;
    uint32_t rem = uVar2 - d*(uVar2/d);
    *param_5 = rem;
  }
}
