/* readable reconstruction; identity: FUN_00030710 @ 0x00030710
 * public-name: commit_default_config_record
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   verify_image_checksum                    <= FUN_000302cc @ 0x000302cc
 *   flash_write_and_verify_blob              <= FUN_00030528 @ 0x00030528
 *   commit_default_config_record             <= FUN_00030710 @ 0x00030710
 * address symbols (name @ address):
 *   rodata_883b8                             @ 0x000883b8
 *   rodata_a49ed                             @ 0x000a49ed
 */
/* Reconstructed FUN_00030710 @ 0x30710  (parity: 300/300 trials, PROVEN) */

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
    volatile uint32_t *src = (volatile uint32_t*)0x883b8UL;
    local_2c[0]=src[0]; local_2c[1]=src[1]; local_2c[2]=src[2]; local_2c[3]=src[3];
    buf.flag = 1;
    buf.val_18 = 0xa49ed;
    buf.val_14 = 0x1b9c;
    buf.val_10 = 0x2000;
    buf.ptr = local_2c;
    uVar2 = flash_write_and_verify_blob(&buf);
  } else {
    uVar2 = -1;
  }
  return uVar2;
}
