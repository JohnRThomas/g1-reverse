/* readable reconstruction; identity: FUN_00075c90 @ 0x00075c90
 * public-name: expf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   expf                                     <= FUN_00075c90 @ 0x00075c90
 *   isfinitef                                <= FUN_000869f2 @ 0x000869f2
 * address symbols (name @ address):
 *   g_libm_ieee_mode_flag                    @ 0x200035af
 */
/* Reconstructed FUN_00075c90 @ 0x75c90  (parity: 300/300 trials, PROVEN) */

extern float FUN_00076290(void);
extern unsigned* thunk_FUN_00071678(void);
extern int isfinitef(float);
float expf(float param_1){
  float uVar3 = FUN_00076290();
  union U{ unsigned u; float f; } a,b,c;
  a.u=0x42b17180; b.u=0xc2cff1b5; c.u=0x7f800000;
  if((*(signed char*)0x200035afUL != -1) && (isfinitef(param_1)!=0)){
    if(param_1 > a.f){
      unsigned* p = thunk_FUN_00071678(); uVar3 = c.f; *p = 0x22;
    } else if(param_1 < b.f){
      unsigned* p = thunk_FUN_00071678(); uVar3 = 0.0f; *p = 0x22;
    }
  }
  return uVar3;
}
