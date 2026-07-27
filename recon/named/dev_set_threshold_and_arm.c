/* readable reconstruction; identity: FUN_00083e70 @ 0x00083e70
 * public-name: dev_set_threshold_and_arm
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_ctrl_write1                          <= FUN_00083d60 @ 0x00083d60
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 *   dev_set_threshold_and_arm                <= FUN_00083e70 @ 0x00083e70
 */
/* Reconstructed FUN_00083e70 @ 0x83e70  (parity: 300/300 trials, PROVEN) */

extern int dev_ctrl_write1(unsigned int, void*, int, unsigned int);
extern int dev_write_reg3(unsigned int, unsigned int, unsigned int, unsigned int);

int dev_set_threshold_and_arm(int param_1, unsigned int param_2)
{
  unsigned char buf[5];
  int iVar1;
  unsigned int r3;

  if (param_2 < 0x10000000) {
    buf[0] = 0x07;
    buf[1] = 0x08;
    buf[2] = (unsigned char)(param_2 >> 0x14);
    r3 = param_2 >> 4;
    buf[3] = (unsigned char)(r3 >> 8);
    buf[4] = (unsigned char)r3;
    iVar1 = dev_ctrl_write1(*(unsigned int*)(param_1+4), buf, 5, r3);
    if (iVar1 == 0) {
      iVar1 = dev_write_reg3(param_1, 7, 3, 1);
    }
  } else {
    iVar1 = -0x16;
  }
  return iVar1;
}
