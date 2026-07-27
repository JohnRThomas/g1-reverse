/* Reconstructed read_sys_settting_from_flash @ 0x232f8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_000225b4(int,void*,int);
extern void FUN_00086c78(void*,int,int);
int read_sys_settting_from_flash(void*param_1) {
  unsigned char record[0x84];
  unsigned char *output = (unsigned char *)param_1;
  unsigned uVar5;
  int iVar1;
  unsigned i;

  FUN_00086c78(record, 0, sizeof(record));
  iVar1 = FUN_000225b4(0x130000, record, sizeof(record));
  if (iVar1 == 0) {
    if (1 < *(int*)0x2000230c) {
      if (*(int*)0x20007554 == 0) DEBUG_PRINT(0x0009e5a6, 0x0009e747);
      else FUN_00019c70(0x0009e5a6, 0x0009e747);
    }
    *(unsigned *)(output + 0x00) = *(unsigned *)(record + 0x00);
    output[0x08] = record[0x08];
    *(unsigned *)(output + 0x0c) = *(unsigned *)(record + 0x0c);
    *(unsigned *)(output + 0x10) = *(unsigned *)(record + 0x10);
    output[0x14] = record[0x14];
    if (record[0x15] != 0xff) {
      for (i = 0; i < 16; i += 4)
        *(unsigned *)(output + 0x15 + i) = *(unsigned *)(record + 0x15 + i);
    }
    if (record[0x35] != 0xff) {
      for (i = 0; i < 16; i += 4)
        *(unsigned *)(output + 0x35 + i) = *(unsigned *)(record + 0x35 + i);
    }
    *(unsigned *)(output + 0x60) = *(unsigned *)(record + 0x60);
    output[0x55] = record[0x55];
    *(unsigned *)(output + 0x64) = *(unsigned *)(record + 0x64);
    output[0x56] = record[0x56];
    *(unsigned *)(output + 0x68) = *(unsigned *)(record + 0x68);
    *(unsigned *)(output + 0x7c) = *(unsigned *)(record + 0x7c);
    *(unsigned *)(output + 0x6c) = *(unsigned *)(record + 0x6c);
    *(unsigned *)(output + 0x80) = *(unsigned *)(record + 0x80);
    *(unsigned *)(output + 0x70) = *(unsigned *)(record + 0x70);
    *(unsigned short *)(output + 0x78) = *(unsigned short *)(record + 0x78);
    *(unsigned *)(output + 0x74) = *(unsigned *)(record + 0x74);
    uVar5 = 0;
  } else {
    if (1 < *(int*)0x2000230c) {
      if (*(int*)0x20007554 == 0) DEBUG_PRINT(0x0009e580, 0x0009e747);
      else FUN_00019c70(0x0009e580, 0x0009e747);
    }
    uVar5 = 0xffffffff;
  }
  return uVar5;
}
