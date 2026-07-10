/* Reconstructed FUN_000456fc @ 0x456fc  (parity: 300/300 trials, PROVEN) */
typedef unsigned int u32;

u32 FUN_000456fc(u32 param_1, u32 param_2)
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

