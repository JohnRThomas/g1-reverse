#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007de82 @ 0x0007de82
 * public-name: FUN_0007de82
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_0007de82 @ 0x7de82  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007de70(int a,int b,int c,int d,int e);
static int clz32(unsigned int x){
    if (x==0) return 32;
    int n=0;
    while(!(x & 0x80000000u)){x<<=1;n++;}
    return n;
}
int FUN_0007de82(int param_1, int param_2, int param_3, int param_4) {
    int iVar1 = FUN_0007de70(param_1, 1, param_2, param_4, param_4);
    int v = (param_2 + 1) - iVar1;
    return 0x1f - clz32((unsigned int)v);
}
