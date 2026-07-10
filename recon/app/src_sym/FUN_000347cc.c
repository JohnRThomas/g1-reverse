/* Reconstructed FUN_000347cc @ 0x347cc  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern unsigned int get_timestamp(void);

int FUN_000347cc(void)
{
  int iVar2;
  unsigned int uVar3;
  int r0;
  unsigned char b;
  unsigned int val;

  r0 = get_device_info();
  b = *(volatile unsigned char*)(long)(r0 + 0xdd);
  iVar2 = *(volatile int*)(long)(0x20007dacUL /* device_info_t+0x13B0  (message/display region) */ + (unsigned int)(b - 1) * 0x1b4);
  if (iVar2 != 0) {
    uVar3 = get_timestamp();
    r0 = get_device_info();
    b = *(volatile unsigned char*)(long)(r0 + 0xdd);
    val = *(volatile unsigned int*)(long)(0x20007dacUL /* device_info_t+0x13B0  (message/display region) */ + (unsigned int)(b - 1) * 0x1b4);
    if ((unsigned int)(val + 0xf) < uVar3) iVar2 = 2; else iVar2 = 1;
  }
  return iVar2;
}

