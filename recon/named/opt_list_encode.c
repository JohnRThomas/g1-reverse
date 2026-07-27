/* readable reconstruction; identity: FUN_0007c77e @ 0x0007c77e
 * public-name: opt_list_encode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   opt_node_serialize                       <= FUN_0007c6a0 @ 0x0007c6a0
 *   opt_list_total_len                       <= FUN_0007c754 @ 0x0007c754
 *   opt_list_encode                          <= FUN_0007c77e @ 0x0007c77e
 */
/* Reconstructed FUN_0007c77e @ 0x7c77e  (parity: 300/300 trials, PROVEN)
 *
 * P4 iteration 40 -- STACK-OBJECT LAYOUT.  The shipped body pushes r0..r3 as a
 * spill area and hands out TWO two-word objects from it: sp+0/sp+4 to
 * opt_list_total_len (which writes {total, count}) and sp+8/sp+0xc to
 * opt_node_serialize (which writes the byte count back into sp+0xc and which
 * the caller then reads with `0007c7d0 ldr r3,[sp,#0xc]`).
 *
 * The previous body modelled the second object as TWO SEPARATE LOCALS.
 * Measured in /private/tmp/g1-i40c-app/zephyr/zephyr.elf, GCC therefore kept
 * the length in a register and emitted
 *     78f94 add r1, sp, #4 ; 78f96 str r3,[sp,#4] ; 78f98 bl opt_node_serialize
 * -- the LENGTH WORD OF THE VIEW IS NEVER WRITTEN.  opt_node_serialize then
 * compared its own total against a stale frame word, took its
 * `remaining < total` exit and returned 1 without serializing anything, and
 * the caller wrote the total back into the view; st25dv_build_and_write_ndef_
 * records duly pushed 28 bytes of STALE STACK to the ST25DV mailbox
 * (`000670210020B7F1...` against the oracle's
 * `0006910606574C434341502001091E030A510703574C4353544149056401`).  The same
 * codegen also dropped the written-length read-back: `78faa mov r8, r0` set the
 * running offset to the callee's zero return instead of to sp+0xc.
 */

struct g1_opt_view { int data; int length; };

extern int opt_node_serialize(int, int *);
extern int opt_list_total_len(int *, int *);

int opt_list_encode(int *param_1, int *param_2, int param_3, unsigned param_4){
    struct g1_opt_view total;
    struct g1_opt_view view;
    int status, node, written, remaining;

    if ((param_2 == 0) || (*param_2 == 0)) return 7;
    /* the pushed argument words the two objects start life as */
    total.data = (int)param_1;
    total.length = (int)param_2;
    view.data = param_3;
    view.length = (int)param_4;

    status = opt_list_total_len(param_1, &total);
    if ((status != 0) || ((unsigned)param_2[1] < (unsigned)total.data)) {
        param_2[1] = total.data;
        return 1;
    }
    remaining = param_2[1];
    written = 0;
    if (param_1 != 0) {
        for (node = *param_1; node != 0; node = *(int*)(node + 0x18)) {
            view.data = *param_2 + written;
            view.length = remaining;
            status = opt_node_serialize(node, &view);
            if (status != 0) {
                param_2[1] = total.data;
                return status;
            }
            written += view.length;
            remaining -= view.length;
        }
    }
    param_2[1] = written;
    return 0;
}
