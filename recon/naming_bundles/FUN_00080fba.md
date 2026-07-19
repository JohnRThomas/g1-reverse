### FUN_00080fba  @ 0x00080fba  (size=10)

callers (3): ble_privacy_request_random_address, FUN_000553f8, FUN_000810f2
callees (0): (none)

```c
/* readable reconstruction; identity: FUN_00080fba @ 0x00080fba
 * public-name: FUN_00080fba
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_00080fba @ 0x80fba  (parity: 300/300 trials, PROVEN) */

void FUN_00080fba(unsigned int *param_1, unsigned int *param_2)
{
  *param_1 = *param_2;
  *(unsigned short *)((unsigned char*)param_1 + 4) = *(unsigned short *)((unsigned char*)param_2 + 4);
}
```