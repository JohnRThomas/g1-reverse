/* readable reconstruction; identity: FUN_0004ff6c @ 0x0004ff6c
 * public-name: arm_fault_dump_esf_registers
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   arm_fault_dump_esf_registers             <= FUN_0004ff6c @ 0x0004ff6c
 *   z_fatal_error                            <= FUN_00071684 @ 0x00071684
 * address symbols (name @ address):
 *   rodata_88258                             @ 0x00088258
 *   rodata_f1abb                             @ 0x000f1abb
 *   rodata_f1aea                             @ 0x000f1aea
 *   rodata_f1b19                             @ 0x000f1b19
 *   rodata_f1b28                             @ 0x000f1b28
 *   rodata_f1b6b                             @ 0x000f1b6b
 *   rodata_f1b7a                             @ 0x000f1b7a
 */
/* Reconstructed FUN_0004ff6c @ 0x4ff6c  (parity: 300/300 trials, PROVEN) */

extern int z_log_msg_runtime_create(int,int,void*,int);
extern int z_fatal_error(int,int*);

void arm_fault_dump_esf_registers(int param_1, int *param_2, int param_3, int param_4)
{
  int uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  struct { int count, format, value0, value1, value2; } log5;
  struct { int count, format, value; } log3;
  struct {
    int count, format;
    int index0, value0;
    int index1, value1;
    int index2, value2;
    int index3, value3;
  } log10;
  if (param_2 != 0) {
    log5.count = 5;
    log5.format = 0xf1abb;
    log5.value0 = param_2[0];
    log5.value1 = param_2[1];
    log5.value2 = param_2[2];
    z_log_msg_runtime_create(0x88258, 0x2840, &log5, 0);
    log5.format = 0xf1aea;
    log5.value0 = param_2[3];
    log5.value1 = param_2[4];
    log5.value2 = param_2[5];
    z_log_msg_runtime_create(0x88258, 0x2840, &log5, 0);
    log3.count = 3;
    log3.format = 0xf1b19;
    log3.value = param_2[7];
    z_log_msg_runtime_create(0x88258, 0x1840, &log3, 0);
    uVar1 = 0xf1b28;
    iVar2 = 0;
    piVar4 = param_2;
    do {
      log10.count = 10;
      log10.format = uVar1;
      log10.index0 = iVar2;
      log10.value0 = piVar4[8];
      log10.index1 = iVar2 + 1;
      log10.value1 = piVar4[9];
      log10.index2 = iVar2 + 2;
      log10.value2 = piVar4[10];
      log10.index3 = iVar2 + 3;
      log10.value3 = piVar4[11];
      iVar3 = iVar2 + 4;
      z_log_msg_runtime_create(0x88258, 0x5040, &log10, 0);
      piVar4 = piVar4 + 4;
      iVar2 = iVar3;
    } while (iVar3 != 0x10);
    log3.format = 0xf1b6b;
    log3.value = param_2[0x18];
    z_log_msg_runtime_create(0x88258, 0x1840, &log3, 0);
    log3.format = 0xf1b7a;
    log3.value = param_2[6];
    z_log_msg_runtime_create(0x88258, 0x1840, &log3, 0);
  }
  z_fatal_error(param_1, param_2);
}
