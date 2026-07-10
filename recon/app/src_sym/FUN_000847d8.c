/* Reconstructed FUN_000847d8 @ 0x847d8  (parity: 300/300 trials, PROVEN) */

typedef int (*vfn847d8)(int, void*, int, short);
int FUN_000847d8(int *param_1, unsigned char param_2, unsigned short *param_3)
{
  int iVar1;
  int uVar2;
  unsigned char local_2d;
  unsigned short local_2c[2];
  unsigned char *local_28;
  unsigned int local_24;
  unsigned char local_20;
  unsigned short *local_1c;
  unsigned int local_18;
  unsigned char local_14;

  local_28 = &local_2d;
  local_24 = 1;
  local_20 = 0;
  local_1c = local_2c;
  local_18 = 2;
  local_14 = 7;
  local_2d = param_2;
  /* Zephyr driver-vtable dispatch: dev = param_1[0]; api = *(dev+8);
     method = *(api+8); equivalent to dev->api->transfer(dev, &msg, 2, addr).
     Byte-swaps the 16-bit result (big-endian sensor register). */
  iVar1 = ((vfn847d8)(*(int *)(*(int *)(*param_1 + 8) + 8)))(*param_1, &local_28, 2, (short)param_1[1]);
  if (iVar1 == 0) {
    *param_3 = (unsigned short)(((local_2c[0] & 0xff) << 8) | (local_2c[0] >> 8));
    uVar2 = 0;
  } else {
    uVar2 = 0xfffffffb;
  }
  return uVar2;
}

