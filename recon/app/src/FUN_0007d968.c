/* Reconstructed FUN_0007d968 @ 0x7d968 */
#include <stdint.h>
extern void FUN_00049aa0(void *workspace,uint32_t a,uint32_t b);
extern void FUN_0007d8f4(void);
extern void FUN_0004a16c(int *, void *);
uint32_t FUN_0007d968(uint32_t a,uint32_t b,uint32_t *out){
  uint32_t result[4]; uint32_t workspace[22];
  FUN_00049aa0(workspace,a,b); FUN_0007d8f4(); FUN_0004a16c(workspace,result);
  for(unsigned i=0;i<4;i++)out[i]=result[i];
  return 0;
}
