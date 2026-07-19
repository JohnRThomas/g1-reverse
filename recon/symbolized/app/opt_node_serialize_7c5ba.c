#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c5ba @ 0x0007c5ba
 * public-name: opt_node_serialize_7c5ba
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   opt_node_value_len                       <= FUN_0007c408 @ 0x0007c408
 *   opt_node_serialize_7c5ba                 <= FUN_0007c5ba @ 0x0007c5ba
 */
/* Reconstructed FUN_0007c5ba @ 0x7c5ba  (parity: 300/300 trials, PROVEN) */

extern unsigned opt_node_value_len(void);
unsigned opt_node_serialize_7c5ba(unsigned char* param_1, int* param_2){
  unsigned uVar3; int iVar4,iVar5;
  if(param_1==0) return 7;
  if(param_2==0) return 7;
  if(*param_2==0) return 7;
  if((unsigned)param_2[1] < 7){ param_2[1]=7; return 1; }
  *(unsigned char*)(*param_2) = *param_1;
  *(unsigned char*)(*param_2 + 1) = param_1[1];
  uVar3 = opt_node_value_len();
  if(uVar3 <= 0xff){
    *(unsigned char*)(*param_2 + 2) = (unsigned char)uVar3;
    iVar5 = 3;
  } else {
    *(unsigned char*)(*param_2+2)=(unsigned char)(uVar3>>0x18);
    *(unsigned char*)(*param_2+3)=(unsigned char)(uVar3>>0x10);
    *(unsigned char*)(*param_2+4)=(unsigned char)(uVar3>>8);
    *(unsigned char*)(*param_2+5)=(unsigned char)uVar3;
    iVar5=6;
  }
  iVar4 = (int)((unsigned)*param_1 << 0x1c);
  if(iVar4 < 0){
    *(unsigned char*)(*param_2 + iVar5) = param_1[2];
    iVar5 = iVar5+1;
  }
  param_2[1] = iVar5;
  return 0;
}
