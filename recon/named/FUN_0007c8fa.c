/* named: FUN_0007c8fa */
/* Reconstructed FUN_0007c8fa @ 0x7c8fa  (parity: 300/300 trials, PROVEN) */

extern int ipc_ept_op_b_locked_retry(int, int, void*, int, int, int);
extern void ipc_ept_op_c_locked_retry(int, int, void*);

void FUN_0007c8fa(int param_1, int param_2)
{
  int iVar1;
  unsigned char local;
  iVar1 = ipc_ept_op_b_locked_retry(param_1, 1, &local, 1, param_1, param_2);
  if (iVar1 == 0) {
    local = (local & ~0x1f) | (param_2 & 0x1f);
    ipc_ept_op_c_locked_retry(param_1, 1, &local);
  }
}

