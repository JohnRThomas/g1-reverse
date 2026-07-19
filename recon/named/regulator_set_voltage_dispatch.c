/* readable reconstruction; identity: FUN_00084348 @ 0x00084348
 * public-name: regulator_set_voltage_dispatch
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   regulator_write_voltage_reg              <= FUN_000842cc @ 0x000842cc
 *   regulator_set_voltage_range              <= FUN_00084300 @ 0x00084300
 *   regulator_set_voltage_dispatch           <= FUN_00084348 @ 0x00084348
 */
/* Reconstructed FUN_00084348 @ 0x84348  (parity: 300/300 trials, PROVEN) */

extern int regulator_write_voltage_reg(int,int,int,int);
extern int regulator_set_voltage_range(int,int,int);

int regulator_set_voltage_dispatch(int param_1, int param_2, int param_3)
{
    int iVar1 = *(int*)(param_1+4);
    unsigned char sel = *(unsigned char*)(iVar1+0x20);
    int uVar2;
    switch(sel) {
    case 0: uVar2=0; break;
    case 1: uVar2=1; break;
    case 2: uVar2=0; return regulator_write_voltage_reg(iVar1,uVar2,param_2,param_3);
    case 3: uVar2=1; return regulator_write_voltage_reg(iVar1,uVar2,param_2,param_3);
    default: return 0xffffffed;
    }
    return regulator_set_voltage_range(iVar1,uVar2,param_2);
}
