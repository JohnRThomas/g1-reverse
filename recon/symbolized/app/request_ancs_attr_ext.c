#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000191e4 @ 0x000191e4
 * public-name: request_ancs_attr_ext
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   ancs_get_conn_ctx                        <= FUN_000181fc @ 0x000181fc
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   bt_ancs_request_attrs                    <= FUN_0007f6b6 @ 0x0007f6b6
 *   thunk_FUN_0007f7d2                       <= FUN_0007f7c4 @ 0x0007f7c4
 * address symbols (name @ address):
 *   rodata_1827d                             @ 0x0001827d
 *   rodata_9ab1e                             @ 0x0009ab1e   [INLINED -- G6 literal batch]
 *   rodata_9abbd                             @ 0x0009abbd   [INLINED -- G6 literal batch]
 *   rodata_9abdc                             @ 0x0009abdc   [INLINED -- G6 literal batch]
 *   rodata_9ac14                             @ 0x0009ac14   [INLINED -- G6 literal batch]
 *   rodata_9b148                             @ 0x0009b148   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_ancs_notif_attr_id_latest              @ 0x20006aa0
 *   g_ancs_notif_evt_id_latest               @ 0x20006aac
 *   g_ancs_client                            @ 0x20006ae8
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed request_ancs_attr_ext @ 0x191e4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void log_message(unsigned,...);
extern unsigned strlen(unsigned);
extern int ancs_get_conn_ctx(void);
extern void debug_print(unsigned,...);
extern int bt_ancs_request_attrs(unsigned,unsigned,unsigned);
extern void FUN_0007c0a4(int,int);
extern int thunk_FUN_0007f7d2(unsigned,unsigned,unsigned,unsigned);
int request_ancs_attr_ext(unsigned param_1, unsigned param_2, unsigned param_3)
{
  unsigned uVar1, uVar2; unsigned short *puVar3; int iVar4, iVar5; unsigned uVar6;
  iVar4 = ancs_get_conn_ctx();
  iVar5 = bt_ancs_request_attrs(((unsigned long)&g_ancs_client) /*=0x20006ae8*/, ((unsigned long)&g_ancs_notif_evt_id_latest) /*=0x20006aac*/, ((unsigned long)&rodata_1827d) /*=0x1827d*/);
  puVar3 = (unsigned short*)((unsigned long)&g_ancs_notif_attr_id_latest) /*=0x20006aa0*/;
  uVar6 = 0;
  do {
    if ((((*(int*)(puVar3+2) == 0) && (*puVar3 != 0)) && (**(char**)(puVar3+4) != 0)) &&
        (*(char*)(iVar4+0x44) != 0)) goto LAB_5a;
    FUN_0007c0a4(0x21, 0);
    uVar6 = uVar6 + 1 & 0xffff;
  } while (uVar6 != 0x3e9);
  if (0 < *(int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
    param_1 = strlen(*(unsigned*)(puVar3+4));
    param_2 = (unsigned)*(unsigned char*)(iVar4+0x44);
    unsigned sink = *(int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    if (sink == 0)
      log_message(((unsigned long)"%s(): notif_attr_app_id_latest.attr_id %d notif_attr_app_id_latest.attr_len %d strlen(notif_attr_app_id_latest.attr_data) %d c->notifi_data.app_identifier %d\n") /*=0x9ab1e*/, ((unsigned long)"request_ancs_attr_ext") /*=0x9b148*/, *(unsigned*)(puVar3+2), (unsigned)*puVar3, param_1, param_2);
    else
      debug_print(((unsigned long)"%s(): notif_attr_app_id_latest.attr_id %d notif_attr_app_id_latest.attr_len %d strlen(notif_attr_app_id_latest.attr_data) %d c->notifi_data.app_identifier %d\n") /*=0x9ab1e*/, ((unsigned long)"request_ancs_attr_ext") /*=0x9b148*/,
                   *(unsigned*)(puVar3+2), (unsigned)*puVar3,
                   param_1, param_2);
  }
  if (*(int*)(puVar3+2) == 0) {
LAB_5a:
    if ((*puVar3 != 0) && (**(char**)(puVar3+4) != 0)) {
      unsigned sink = *(int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
      if (sink == 0) {
        log_message(((unsigned long)"Request for %s: retry_time %d\n") /*=0x9abbd*/, *(char**)(puVar3+4), uVar6, sink, param_1, param_2, param_3);
        uVar1 = ((unsigned long)&g_ancs_client) /*=0x20006ae8*/; uVar2 = ((unsigned long)&rodata_1827d) /*=0x1827d*/;
      } else {
        debug_print(((unsigned long)"Request for %s: retry_time %d\n") /*=0x9abbd*/, *(char**)(puVar3+4), uVar6,
                     sink, param_1, param_2, param_3);
        uVar1 = ((unsigned long)&g_ancs_client) /*=0x20006ae8*/; uVar2 = ((unsigned long)&rodata_1827d) /*=0x1827d*/;
      }
      for (; uVar6 < 200; uVar6 = uVar6 + 1 & 0xffff) {
        iVar5 = thunk_FUN_0007f7d2(uVar1, *(unsigned*)(puVar3+4), *puVar3, uVar2);
        if (iVar5 == 0) goto LAB_86;
        FUN_0007c0a4(0xa4, 0);
      }
      if (iVar5 != 0) log_message(((unsigned long)"Failed requesting attributes for a given app (err: %d)\n") /*=0x9abdc*/, iVar5);
    }
  }
LAB_86:
  if (*(int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
    log_message(((unsigned long)"notif_attr_app_id_latest.attr_id (%d/%d) retry_time %d\n") /*=0x9ac14*/, *(unsigned*)(puVar3+2), (unsigned)*puVar3, uVar6, param_1, param_2);
  else
    debug_print(((unsigned long)"notif_attr_app_id_latest.attr_id (%d/%d) retry_time %d\n") /*=0x9ac14*/, *(unsigned*)(puVar3+2),
                 (unsigned)*puVar3, uVar6, param_1, param_2, param_3);
  return iVar5;
}
