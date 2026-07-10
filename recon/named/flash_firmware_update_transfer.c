/* named: flash_firmware_update_transfer */
/* Reconstructed flash_firmware_update_transfer @ 0x30754  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4;
extern int verify_image_checksum(int,...);
undefined4 flash_firmware_update_transfer(int param_1)
{
  int iVar3 = verify_image_checksum(0);
  if (iVar3 != 0) return 0xffffffff;
  (void)param_1;
  return 0;
}

