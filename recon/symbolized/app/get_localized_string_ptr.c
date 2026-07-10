#include "g1_app_symbols.h"
/* named: get_localized_string_ptr */
/* Reconstructed get_localized_string_ptr @ 0x456fc  (parity: 300/300 trials, PROVEN) */
typedef unsigned int u32;

u32 get_localized_string_ptr(u32 param_1, u32 param_2)
{
  u32 iVar1;

  if (param_2 < 0x42) {
    switch (param_1) {
    case 1:
      iVar1 = ((uintptr_t)&rodata_8aa10) /*=0x8aa10*/;
      break;
    default:
      iVar1 = ((uintptr_t)&rodata_8ab18) /*=0x8ab18*/;
      break;
    case 3:
      iVar1 = ((uintptr_t)&rodata_8a4e8) /*=0x8a4e8*/;
      break;
    case 4:
      iVar1 = ((uintptr_t)&rodata_8a3e0) /*=0x8a3e0*/;
      break;
    case 5:
      iVar1 = ((uintptr_t)&rodata_8a6f8) /*=0x8a6f8*/;
      break;
    case 6:
      iVar1 = ((uintptr_t)&rodata_8a908) /*=0x8a908*/;
      break;
    case 7:
      iVar1 = ((uintptr_t)&rodata_8a800) /*=0x8a800*/;
      break;
    case 0xe:
      iVar1 = ((uintptr_t)&rodata_8a5f0) /*=0x8a5f0*/;
      break;
    }
    return *(volatile u32*)(iVar1 + param_2 * 4);
  }
  return "ERR_STRING" /*=0xbb220*/;
}

