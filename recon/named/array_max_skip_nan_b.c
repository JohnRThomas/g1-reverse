/* readable reconstruction; identity: FUN_0000e9b4 @ 0x0000e9b4
 * public-name: array_max_skip_nan_b
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   float_is_nan                             <= FUN_0000e938 @ 0x0000e938
 *   array_max_skip_nan_b                     <= FUN_0000e9b4 @ 0x0000e9b4
 */
/* Reconstructed FUN_0000e9b4 @ 0xe9b4  (parity: 300/300 trials, PROVEN) */

extern int float_is_nan(float);
float array_max_skip_nan_b(float *param_1){
  int iVar1; float fVar2; float fVar3;
  iVar1=float_is_nan(*param_1);
  if(iVar1==0){ fVar2=*param_1; iVar1=2; }
  else {
    iVar1=float_is_nan(param_1[1]);
    if(iVar1!=0){
      iVar1=float_is_nan(param_1[2]);
      if(iVar1==0){ return param_1[2]; }
      return *param_1;
    }
    fVar2=param_1[1]; iVar1=3;
  }
  param_1 = param_1 + iVar1 + 0x3fffffff;
  while(1){
    fVar3=*param_1; param_1=param_1+1;
    if((int)((unsigned)(fVar3<fVar2)<<0x1f)<0){ fVar2=fVar3; }
    if(iVar1!=2) break;
    iVar1=3;
  }
  return fVar2;
}
