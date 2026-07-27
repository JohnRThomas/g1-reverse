/* Reconstructed FUN_000332dc @ 0x332dc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern int z_device_is_ready(void*);
extern int FUN_000336a0(void*);
extern void assert_post_action(void*, int);
extern void printk(unsigned long, ...);

unsigned int FUN_000332dc(void)
{
  volatile unsigned char *pcVar1 = (volatile unsigned char*)0x2001a127UL;
  int iVar2;

  if (*pcVar1 == 0) {
    iVar2 = z_device_is_ready((void*)0x87bc0UL);
    if (iVar2 == 0) {
      printk((unsigned long)0x99cbdUL, (void*)0xa78b9UL, (void*)0xa7892UL, 0x2e, 0);
      printk((unsigned long)0xa78d1UL, 0, 0, 0, 0);
      assert_post_action((void*)0xa7892UL, 0x2e);
    }
    iVar2 = FUN_000336a0((void*)0x87bc0UL);
    if (iVar2 != 0) {
      *pcVar1 = 0;
      DEBUG_PRINT((unsigned long)0xa78ebUL);
      return 0xffffffff;
    }
    *pcVar1 = 1;
  }
  return 0;
}

