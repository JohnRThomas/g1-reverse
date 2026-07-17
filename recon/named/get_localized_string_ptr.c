/* readable reconstruction; identity: FUN_000456fc @ 0x000456fc
 * public-name: get_localized_string_ptr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_localized_string_ptr                 <= FUN_000456fc @ 0x000456fc
 * address symbols (name @ address):
 *   rodata_8a3e0                             @ 0x0008a3e0
 *   rodata_8a4e8                             @ 0x0008a4e8
 *   rodata_8a5f0                             @ 0x0008a5f0
 *   rodata_8a6f8                             @ 0x0008a6f8
 *   rodata_8a800                             @ 0x0008a800
 *   rodata_8a908                             @ 0x0008a908
 *   rodata_8aa10                             @ 0x0008aa10
 *   rodata_8ab18                             @ 0x0008ab18
 *   rodata_bb220                             @ 0x000bb220
 */
/* Reconstructed FUN_000456fc @ 0x456fc  (parity: 300/300 trials, PROVEN) */
typedef unsigned int u32;

u32 get_localized_string_ptr(u32 param_1, u32 param_2)
{
  u32 iVar1;

  if (param_2 < 0x42) {
    switch (param_1) {
    case 1:
      iVar1 = 0x0008aa10UL;
      break;
    default:
      iVar1 = 0x0008ab18UL;
      break;
    case 3:
      iVar1 = 0x0008a4e8UL;
      break;
    case 4:
      iVar1 = 0x0008a3e0UL;
      break;
    case 5:
      iVar1 = 0x0008a6f8UL;
      break;
    case 6:
      iVar1 = 0x0008a908UL;
      break;
    case 7:
      iVar1 = 0x0008a800UL;
      break;
    case 0xe:
      iVar1 = 0x0008a5f0UL;
      break;
    }
    return *(volatile u32*)(iVar1 + param_2 * 4);
  }
  return 0x000bb220UL;
}
