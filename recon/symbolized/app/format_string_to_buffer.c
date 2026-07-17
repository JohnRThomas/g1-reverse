#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007797c @ 0x0007797c
 * public-name: format_string_to_buffer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   format_string_to_buffer                  <= FUN_0007797c @ 0x0007797c
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* Reconstructed FUN_0007797c @ 0x7797c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00078d90(int, void*, int);

void format_string_to_buffer(unsigned char *param_1, int param_2, int param_3, int param_4)
{
  struct writer_frame {
    unsigned reserved[2];
    struct {
      unsigned char *start;
      unsigned unused;
      int capacity;
      unsigned flags;
      unsigned char *cursor;
      int remaining;
    } writer;
    unsigned char tail[80];
  } frame;
  frame.writer.start = param_1;
  frame.writer.capacity = 0x7fffffff;
  frame.writer.flags = 0xffff0208u;
  frame.writer.cursor = param_1;
  frame.writer.remaining = 0x7fffffff;
  (void)param_3;
  (void)param_4;
  FUN_00078d90(*(volatile int*)((unsigned long)&g_libc_heap_ctrl) /*=0x20002d20*/, &frame.writer, param_2);
  *frame.writer.start = 0;
}
