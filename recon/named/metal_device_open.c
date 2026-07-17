/* readable reconstruction; identity: FUN_00085406 @ 0x00085406
 * public-name: metal_device_open
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   metal_bus_find                           <= FUN_00068134 @ 0x00068134
 *   metal_device_open                        <= FUN_00085406 @ 0x00085406
 */
/* Reconstructed FUN_00085406 @ 0x85406  (parity: 300/300 trials, PROVEN) */

extern int metal_bus_find(char *a, char **b, int c, char d, char *e);

int metal_device_open(char *param_1, char *param_2, int param_3)
{
  int iVar1;
  char *local_14;
  int iStack_10;

  if (param_1==0 || *param_1==0 || param_2==0 || *param_2==0 || param_3==0) {
    return -0x16;
  }
  local_14 = param_2;
  iStack_10 = param_3;
  iVar1 = metal_bus_find(param_1, &local_14, param_3, *param_2, param_1);
  if (iVar1 == 0) {
    void *fn = *(void**)(local_14+8);
    if (fn != 0) {
      return ((int(*)(char*,char*,int))fn)(local_14, param_2, param_3);
    }
    return -0x13;
  }
  return iVar1;
}
