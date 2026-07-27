
/* Full reconstruction FUN_0007c3da @ 0x7c3da (exact extent 16 bytes).
 *
 * P4 iteration 40.  The shipped body is a pure tail dispatch
 *     0007c3da  cbz  r0, #0x7c3e2
 *     0007c3dc  ldr  r3, [r0, #0xc]
 *     0007c3de  cbz  r3, #0x7c3e6
 *     0007c3e0  bx   r3
 * so EVERY argument register the caller set is forwarded untouched.  The only
 * caller, st25dv_build_and_write_ndef_records (0x250f8), passes two: the record
 * and the out node that FUN_00025020 / FUN_00025058 bind.  The previous body
 * declared a single parameter and happened to keep r1 alive; that is a property
 * of this codegen, not of the source, so the second argument is now explicit.
 */
#include <stdint.h>
uint32_t invoke_optional_op_offset12(uint8_t *object, void *out_node)
{
    if (object == 0) return 7;
    uint32_t (*callback)(uint8_t *, void *) =
        *(uint32_t (**)(uint8_t *, void *))(object + 12);
    return callback != 0 ? callback(object, out_node) : 15;
}
