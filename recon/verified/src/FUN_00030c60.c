/* Reconstructed FUN_00030c60 @ 0x30c60  (uncatalogued: Ghidra folded it into
 * the tail of misc_dev_api_transfer_op12, 0x30c24, whose declared extent runs
 * to 0x30c90).  Code 0x30c60..0x30c8a, literal pool 0x30c8c (= 0x20002418).
 *
 * Slot 1 of the ops table the shipped `.data` places at 0x20002408, the table
 * `pt_nfc_eeprom_link_init` (0x30b3c) requires to be all-non-zero.
 *
 * Single-message form of 0x30c24: one { buf, len, flags = 2 } descriptor
 * (I2C_MSG_WRITE | I2C_MSG_STOP) handed to `api->transfer` (offset +8 of the
 * device's api pointer) with num_msgs = 1 and addr = 0x12.
 */

struct g1_i2c_msg { unsigned char *buf; unsigned int len; unsigned char flags; };
typedef int (*fnptr)(unsigned int, struct g1_i2c_msg *, int, int);

int FUN_00030c60(unsigned char *param_1, unsigned int param_2)
{
  struct g1_i2c_msg msg;
  int iVar1;
  unsigned int base;
  fnptr fp;
  msg.buf = param_1;
  msg.len = param_2;
  msg.flags = 2;
  base = *(volatile unsigned int *)0x20002418UL;
  fp = *(fnptr *)(*(unsigned int *)(base + 8) + 8);
  iVar1 = fp(base, &msg, 1, 0x12);
  if (iVar1 != 0) iVar1 = 1;
  return -iVar1;
}
