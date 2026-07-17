/* readable reconstruction; identity: FUN_0008149a @ 0x0008149a
 * public-name: bt_conn_set_security
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   atomic_and_2                             <= FUN_000813b4 @ 0x000813b4
 *   bt_conn_set_security                     <= FUN_0008149a @ 0x0008149a
 */
/* Reconstructed FUN_0008149a @ 0x8149a  (parity: 300/300 trials, PROVEN) */

extern void atomic_and_2(void*, unsigned int, unsigned int, unsigned int, unsigned int);
extern int FUN_0005d964(int);

int bt_conn_set_security(int param_1, unsigned char param_2, unsigned int param_3, unsigned int param_4)
{
  volatile unsigned int *puVar1;
  int iVar2;

  if (*(char*)(param_1+0xd) == 7) {
    puVar1 = (volatile unsigned int*)(param_1+4);
    if ((int)((unsigned int)param_2 << 0x18) < 0) {
      *puVar1 = *puVar1 | 0x800;
    } else {
      atomic_and_2((void*)puVar1, 0xfffff7ff, param_3, (unsigned int)param_2 << 0x18, param_4);
    }
    *(unsigned char*)(param_1+10) = param_2 & 0x7f;
    iVar2 = FUN_0005d964(param_1);
    if (iVar2 != 0) {
      *(unsigned char*)(param_1+10) = *(unsigned char*)(param_1+9);
    }
  } else {
    iVar2 = -0x80;
  }
  return iVar2;
}
