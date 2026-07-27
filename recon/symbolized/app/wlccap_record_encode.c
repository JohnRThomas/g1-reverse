#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00025020 @ 0x00025020
 * public-name: wlccap_record_encode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   opt_field1_set                           <= FUN_0007c430 @ 0x0007c430
 *   opt_record_bind_value                    <= FUN_0007c61e @ 0x0007c61e
 *   opt_record_init                          <= FUN_0007c4b6 @ 0x0007c4b6
 *   wlccap_record_encode                     <= FUN_00025020 @ 0x00025020
 * address symbols (name @ address):
 *   g_wlccap_record_type                     @ 0x200023c4
 */
/* Reconstructed FUN_00025020 @ 0x25020  (exact extent 50 bytes)
 *
 * P4 iteration 40.  Catalog-missing.  Installed as the literal 0x00025021 at
 * offset +12 of the type-7 (WLCCAP) NDEF record by event_record_init
 * (0x25090), and reached only through invoke_optional_op_offset12 (0x7c3da),
 * which does `ldr r3,[r0,#0xc]; bx r3` — so r0 is the record and r1 is the
 * caller's out node, both passed straight through.
 *
 * Shipped bytes:
 *     00025020  push  {r3, r4, r5, lr}
 *     00025022  mov   r4, r1
 *     00025024  mov   r5, r0
 *     00025026  cbz   r0, #0x25030
 *     00025028  ldrb  r3, [r0]
 *     0002502a  cmp   r3, #7
 *     0002502c  bne   #0x25030
 *     0002502e  cbnz  r1, #0x25034
 *     00025030  movs  r0, #7                 ; EINVAL
 *     00025032  pop   {r3, r4, r5, pc}
 *     00025034  mov   r0, r1
 *     00025036  bl    #0x7c4b6               ; opt_record_init(node)
 *     0002503a  movs  r1, #1
 *     0002503c  mov   r0, r4
 *     0002503e  ldr   r2, [pc, #0x14]        ; @0x25054 = 0x200023c4
 *     00025040  bl    #0x7c430               ; opt_field1_set(node, 1, type)
 *     00025044  mov   r1, r5
 *     00025046  mov   r0, r4
 *     00025048  bl    #0x7c61e               ; opt_record_bind_value(node, rec)
 *     0002504c  cmp   r0, #0
 *     0002504e  beq   #0x25032               ; success -> return 0
 *     00025050  b     #0x25030               ; failure -> return 7
 *
 * 0x200023c4 is the shipped `.data` descriptor { 0x0009f1e4, 6 } and
 * 0x0009f1e4 is the ASCII "WLCCAP" — the NFC Forum Wireless Charging
 * Capability record type name.  Type field 1 is the NDEF TNF "well known"
 * class that opt_field1_set ORs into the node header.
 */

extern unsigned int opt_record_init(unsigned char *);
extern unsigned int opt_field1_set(unsigned char *param_1, unsigned int param_2,
                                 int *param_3);
extern unsigned int opt_record_bind_value(unsigned char *param_1, unsigned char *param_2);

unsigned int wlccap_record_encode(unsigned char *param_1, unsigned char *param_2)
{
  if (param_1 == 0 || *param_1 != 7 || param_2 == 0) {
    return 7;
  }
  opt_record_init(param_2);
  opt_field1_set(param_2, 1, (int *)((unsigned long)&g_wlccap_record_type) /*=0x200023c4*/);
  return (opt_record_bind_value(param_2, param_1) == 0) ? 0 : 7;
}
