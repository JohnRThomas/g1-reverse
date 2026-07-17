/* readable reconstruction; identity: FUN_01029d34 @ 0x01029d34
 * public-name: FUN_01029d34
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01029d34 @ 0x1029d34  (parity 300 trials PROVEN) */

extern int FUN_01022ebc(unsigned char);
extern void FUN_010256dc(int,int) __attribute__((noreturn));
typedef char* (*fp_t)(unsigned int,int,unsigned int,void*,unsigned int);
void FUN_01029d34(unsigned int param_1, char *param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1 = FUN_01022ebc(*(unsigned char*)(param_2+0x27));
  unsigned int uVar3;
  if (iVar1 == 0) {
    uVar3 = 0xd8;
  } else {
    *(unsigned short*)(param_2+0x24) = 0;
    *(unsigned char*)(param_2+0x26) = 0;
    fp_t f = *(fp_t*)(param_2+0x20);
    char *pcVar2 = f(param_1,9,param_3,(void*)f,param_4);
    if (pcVar2 == 0 || *pcVar2 == 0) return;
    uVar3 = 0xdc;
  }
  FUN_010256dc(0x6a, uVar3);
  __builtin_unreachable();
}
