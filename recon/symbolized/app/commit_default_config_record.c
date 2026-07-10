#include "g1_app_symbols.h"
/* named: commit_default_config_record */
/* Reconstructed commit_default_config_record @ 0x30710  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int verify_image_checksum(void);
extern int flash_write_and_verify_blob(void *p);
int commit_default_config_record(void)
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
  iVar1 = verify_image_checksum();
  if (iVar1 == 0) {
    volatile uint32_t *src = (volatile uint32_t*)((uintptr_t)&tbl_88340) /*=0x883b8*/;
    local_2c[0]=src[0]; local_2c[1]=src[1]; local_2c[2]=src[2]; local_2c[3]=src[3];
    buf.flag = 1;
    buf.val_18 = ((uintptr_t)&rodata_a49ed) /*=0xa49ed*/;
    buf.val_14 = 0x1b9c;
    buf.val_10 = 0x2000;
    buf.ptr = local_2c;
    uVar2 = flash_write_and_verify_blob(&buf);
  } else {
    uVar2 = -1;
  }
  return uVar2;
}

