### FUN_0007c1dc  @ 0x0007c1dc  (size=34)

callers (1): ble_process_put_req
callees (2): get_device_info, FUN_0007c176

```c
/* readable reconstruction; identity: FUN_0007c1dc @ 0x0007c1dc
 * public-name: FUN_0007c1dc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 */
/* Reconstructed FUN_0007c1dc @ 0x7c1dc  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern void FUN_0007c176(void);
unsigned int FUN_0007c1dc(unsigned char param_1, unsigned char param_2, int param_3)
{
  int iVar1;
  if (param_3 == 0) {
    iVar1 = get_device_info();
    *(volatile unsigned char *)(iVar1 + 0xcf) = param_2;
    iVar1 = get_device_info();
    *(volatile unsigned char *)(iVar1 + 0xcd) = param_1;
  } else {
    FUN_0007c176();
  }
  return 0;
}
```