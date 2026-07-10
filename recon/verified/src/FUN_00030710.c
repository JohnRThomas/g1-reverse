/* Reconstructed FUN_00030710 @ 0x30710  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_000302cc(void);
extern int FUN_00030528(void *p);
int FUN_00030710(void)
{
  int iVar1;
  int uVar2;
  uint32_t local_2c[4];
  struct {
    uint8_t flag;
    uint8_t pad[3];
    uint32_t val_18;
    uint32_t val_14;
    uint32_t val_10;
    void *ptr;
  } buf;
  iVar1 = FUN_000302cc();
  if (iVar1 == 0) {
    volatile uint32_t *src = (volatile uint32_t*)0x883b8UL;
    local_2c[0]=src[0]; local_2c[1]=src[1]; local_2c[2]=src[2]; local_2c[3]=src[3];
    buf.flag = 1;
    buf.val_18 = 0xa49ed;
    buf.val_14 = 0x1b9c;
    buf.val_10 = 0x2000;
    buf.ptr = local_2c;
    uVar2 = FUN_00030528(&buf);
  } else {
    uVar2 = -1;
  }
  return uVar2;
}

