/* readable reconstruction; identity: FUN_0006a700 @ 0x0006a700
 * public-name: FUN_0006a700
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_0006a700 @ 0x6a700  (parity: 213/300 trials, PROVEN) */
#include <stdint.h>
#define DP(a,b) ((int)(short)(a)*(int)(short)(b) + (int)(short)((unsigned)(a)>>16)*(int)(short)((unsigned)(b)>>16))

void FUN_0006a700(long long *param_1, int param_2, short *param_3, int param_4){
  int iVar4 = 0x0008bfb8;
  if(param_4 > 0){
    int lim = (int)((unsigned)param_4 * 0xfu);
    unsigned uVar10 = 0, uVar11 = 0;
    unsigned uVar9 = 0xffce0000;
    short *local_2c = param_3;
    while(1){
      int iVar5a = ((int)uVar10 >> 4) - 0xf;
      int iVar7 = param_2 + iVar5a * 4;
      unsigned uVar6 = *(volatile unsigned*)iVar7;
      int iVar5b = iVar4 + (int)(uVar11 * 0x40);
      uVar10 = uVar10 + 0xf;
      uVar11 = uVar10 & 0xf;
      int iVar5 =
        DP(*(volatile unsigned*)(iVar7+0x3c), *(volatile unsigned*)(iVar5b+0x3c)) +
        DP(*(volatile unsigned*)(iVar7+0x38), *(volatile unsigned*)(iVar5b+0x38)) +
        DP(*(volatile unsigned*)(iVar7+0x34), *(volatile unsigned*)(iVar5b+0x34)) +
        DP(*(volatile unsigned*)(iVar7+0x30), *(volatile unsigned*)(iVar5b+0x30)) +
        DP(*(volatile unsigned*)(iVar7+0x2c), *(volatile unsigned*)(iVar5b+0x2c)) +
        DP(*(volatile unsigned*)(iVar7+0x28), *(volatile unsigned*)(iVar5b+0x28)) +
        DP(*(volatile unsigned*)(iVar7+0x24), *(volatile unsigned*)(iVar5b+0x24)) +
        DP(*(volatile unsigned*)(iVar7+0x20), *(volatile unsigned*)(iVar5b+0x20)) +
        DP(*(volatile unsigned*)(iVar7+0x1c), *(volatile unsigned*)(iVar5b+0x1c)) +
        DP(*(volatile unsigned*)(iVar7+0x18), *(volatile unsigned*)(iVar5b+0x18)) +
        DP(*(volatile unsigned*)(iVar7+0x14), *(volatile unsigned*)(iVar5b+0x14)) +
        DP(*(volatile unsigned*)(iVar7+0x10), *(volatile unsigned*)(iVar5b+0x10)) +
        DP(*(volatile unsigned*)(iVar7+0xc),  *(volatile unsigned*)(iVar5b+0xc)) +
        DP(*(volatile unsigned*)(iVar7+8),    *(volatile unsigned*)(iVar5b+8)) +
        DP(*(volatile unsigned*)(iVar7+4),    *(volatile unsigned*)(iVar5b+4)) +
        DP(uVar6, uVar9);
      long long lVar2 = (long long)iVar5 * (long long)(int)0x3ee61bc6;
      long long lVar3 = lVar2 + ((volatile long long*)param_1)[0];
      unsigned uVar8 = (unsigned)lVar3 >> 0x1e | (unsigned)((int)((unsigned long long)lVar3 >> 0x20) * 4);
      long long uVar1 = (long long)iVar5 * (long long)(int)0x8233c872 + ((volatile long long*)param_1)[1];
      ((volatile long long*)param_1)[0] = (long long)(int)uVar8 * (long long)(int)0x7dc75ddb + uVar1;
      ((volatile long long*)param_1)[1] = (long long)(int)uVar8 * (long long)(int)0xc22eeebf + lVar2;
      *(volatile short*)local_2c = (short)((int)(uVar8 + 0x8000) >> 0x10);
      if(lim <= (int)uVar10) break;
      uVar9 = *(volatile unsigned*)(iVar4 + (int)(uVar11 * 0x40));
      local_2c = local_2c + 1;
    }
  }
}
