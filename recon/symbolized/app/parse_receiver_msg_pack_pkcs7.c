#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00019da4 @ 0x00019da4
 * public-name: parse_receiver_msg_pack_pkcs7
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   parse_receiver_msg_pack_pkcs7            <= FUN_00019da4 @ 0x00019da4
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_9b371                             @ 0x0009b371   [INLINED -- G6 literal batch]
 *   rodata_9b3b5                             @ 0x0009b3b5   [INLINED -- G6 literal batch]
 *   rodata_9b3e0                             @ 0x0009b3e0   [INLINED -- G6 literal batch]
 *   rodata_9b413                             @ 0x0009b413   [INLINED -- G6 literal batch]
 *   rodata_9b44a                             @ 0x0009b44a   [INLINED -- G6 literal batch]
 *   rodata_9e0b2                             @ 0x0009e0b2   [INLINED -- G6 literal batch]
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_pkcs7_rx_msg_id                        @ 0x2000d6f0
 *   g_pkcs7_rx_offset                        @ 0x2000d6f2
 *   g_pkcs7_rx_cmd_id                        @ 0x2001031f
 */
/* Reconstructed FUN_00019da4 @ 0x19da4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_log.h"
extern int memcpy(int,...);
unsigned int parse_receiver_msg_pack_pkcs7(int param_1, unsigned char *param_2, unsigned int param_3)
{
  volatile int *E = (volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
  volatile unsigned char *P = (volatile unsigned char*)((unsigned long)&g_pkcs7_rx_cmd_id) /*=0x2001031f*/;
  volatile unsigned short *H6f2 = (volatile unsigned short*)((unsigned long)&g_pkcs7_rx_offset) /*=0x2000d6f2*/;
  volatile unsigned short *H6f0 = (volatile unsigned short*)((unsigned long)&g_pkcs7_rx_msg_id) /*=0x2000d6f0*/;
  if (param_2 == 0) {
    if (*E == 0) log_message(((unsigned long)"[%s-%d]error, req is NULL ! \n") /*=0x9b371*/,((unsigned long)"parse_receiver_msg_pack_pkcs7") /*=0x9e0b2*/,0xe4);
    else debug_print(((unsigned long)"[%s-%d]error, req is NULL ! \n") /*=0x9b371*/,((unsigned long)"parse_receiver_msg_pack_pkcs7") /*=0x9e0b2*/,0xe4);
    return 0xca;
  }
  if (param_1 == 0) {
    if (*E == 0) log_message(0x9b38f,((unsigned long)"parse_receiver_msg_pack_pkcs7") /*=0x9e0b2*/,0xe9);
    else debug_print(0);
    return 0xca;
  }
  if (param_3 < 4) {
    if (*E != 0) { debug_print(((unsigned long)"[%s-%d]error, req_len is %d, too short ! \n") /*=0x9b3b5*/,((unsigned long)"parse_receiver_msg_pack_pkcs7") /*=0x9e0b2*/,0xef,param_3); return 0xca; }
    log_message(((unsigned long)"[%s-%d]error, req_len is %d, too short ! \n") /*=0x9b3b5*/,((unsigned long)"parse_receiver_msg_pack_pkcs7") /*=0x9e0b2*/,0xef,param_3);
    return 0xca;
  }
  {
    unsigned char bVar3 = param_2[3];
    unsigned char b0 = param_2[0];
    unsigned char bVar1 = param_2[1];
    unsigned char bVar2 = param_2[2];
    if (bVar3 == 0) {
      *P = b0;
      *H6f2 = (unsigned short)bVar3;
      *H6f0 = (unsigned short)bVar1;
    }
    unsigned int pb = *P;
    if (pb != b0) {
      if (*E != 0) debug_print(((unsigned long)"[%s-%d]error, curCmd is %d, but parseCmd is %d ! \n") /*=0x9b3e0*/,((unsigned long)"parse_receiver_msg_pack_pkcs7") /*=0x9e0b2*/,0x109,b0);
      else log_message(((unsigned long)"[%s-%d]error, curCmd is %d, but parseCmd is %d ! \n") /*=0x9b3e0*/,((unsigned long)"parse_receiver_msg_pack_pkcs7") /*=0x9e0b2*/,0x109,b0,pb);
      return 0xca;
    }
    unsigned int h0 = *H6f0;
    if (bVar1 != h0) {
      if (*E != 0) debug_print(((unsigned long)"[%s-%d]error, curMsgId is %d, but parseMsgId is %d ! \n") /*=0x9b413*/,((unsigned long)"parse_receiver_msg_pack_pkcs7") /*=0x9e0b2*/,0x10f,bVar1);
      else log_message(((unsigned long)"[%s-%d]error, curMsgId is %d, but parseMsgId is %d ! \n") /*=0x9b413*/,((unsigned long)"parse_receiver_msg_pack_pkcs7") /*=0x9e0b2*/,0x10f,bVar1,h0);
      return 0xca;
    }
    {
      unsigned short uVar4 = *H6f2;
      memcpy(param_1 + uVar4, (int)(param_2 + 4), param_3 - 4, bVar1);
      *H6f2 = (unsigned short)(param_3 + (uVar4 - 4));
      if ((int)bVar3 != (int)bVar2 - 1) return 0xcb;
      if (*E == 0) log_message(((unsigned long)"origin_data is %s \n") /*=0x9b44a*/, param_1);
      else debug_print(0);
      return 0xc9;
    }
  }
}
