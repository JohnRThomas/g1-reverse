/* Reconstructed FUN_00083d60 @ 0x83d60  (parity: 300/300 trials, PROVEN) */

typedef void (*fnptr)(int, void*, int, short, void*);
void FUN_00083d60(int *param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  /* struct i2c_msg { uint8_t *buf; uint32_t len; uint8_t flags; }
   * ITERATION-10 DEFECT FIX: the original stores flags = 2
   * (I2C_MSG_WRITE | I2C_MSG_STOP) into the message; the earlier
   * reconstruction dropped that store, because the parity harness compares
   * only NON-STACK writes and this message is a stack object.  Original
   * disassembly (FUN_00083d60 @ 0x83d60, 32 B):
   *     83d62  mov    r3, r0
   *     83d64  strd   r1, r2, [sp, #4]      ; msg.buf, msg.len
   *     83d68  movs   r2, #2
   *     83d6e  strb.w r2, [sp, #0xc]        ; msg.flags = 2   <-- was missing
   *     83d74  add    r1, sp, #4            ; &msg
   *     83d78  movs   r2, #1                ; num_msgs
   *     83d7a  blx    r4                    ; api->transfer
   */
  struct { unsigned int buf; unsigned int len; unsigned char flags; } msg;
  int base;
  int vt;
  fnptr f;
  unsigned short h;
  msg.buf = param_2;
  msg.len = param_3;
  msg.flags = 2;
  base = *param_1;
  vt = *(volatile int*)(base + 8);
  f = (fnptr)(*(volatile int*)(vt + 8));
  h = *(volatile unsigned short*)((char*)param_1 + 4);
  f(base, &msg, 1, (short)h, param_1);
  return;
}

