/* readable reconstruction; identity: FUN_00018ff8 @ 0x00018ff8
 * public-name: dequeue_uid
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 * address symbols (name @ address):
 *   rodata_9aafd                             @ 0x0009aafd   [INLINED -- G6 literal batch]
 *   rodata_9b16a                             @ 0x0009b16a   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_uid_pipe                               @ 0x20006a38
 *   g_log_use_alt_sink                       @ 0x20007554
 */
#include "../headers/g1_log.h"
/* Reconstructed dequeue_uid @ 0x18ff8  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_get(unsigned int a, void *b, unsigned int c, unsigned int d);

int dequeue_uid(unsigned int *param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar1;
  struct uid_record {
    unsigned int first;
    unsigned int second;
  } record;

  record.first = 0;
  record.second = 0;
  (void)param_2;
  (void)param_3;
  if (*(volatile int *)(0x20006a38UL + 0x10) == 0) {
    iVar1 = 1;
  } else {
    iVar1 = k_msgq_get(0x20006a38UL, &record, 0, 0);
    if (iVar1 == 0) {
      *param_1 = record.first;
      param_1[1] = record.second;
    } else if (0 < *(volatile int *)0x2000230cUL) {
      if (*(volatile int *)0x20007554UL == 0) {
        log_message(((unsigned long)"%s(): D uid F\n"), ((unsigned long)"dequeue_uid"));
      } else {
        debug_print(((unsigned long)"%s(): D uid F\n"), ((unsigned long)"dequeue_uid"));
      }
    }
  }
  return iVar1;
}
