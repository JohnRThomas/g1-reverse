/* readable reconstruction; identity: FUN_01008d00 @ 0x01008d00
 * public-name: sdc_assertion_fail
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   g_21000a58                               @ 0x21000a58
 */
/* net-core FUN_01008d00 @ 0x01008d00
 *
 * Internal controller assertion endpoint.  The closed controller passes a
 * compact numeric module id in r0 and the source line in r1.  Before invoking
 * the registered two-argument fault handler, it expands the module id to the
 * decimal "file" string expected by sdc_fault_handler_t.  The raw FUN name is
 * retained as the address-stable back mapping.
 */
#include <stdint.h>
#include <cmsis_gcc.h>

typedef void (*controller_fault_handler_t)(const char *module,
                                           uint32_t line);

__attribute__((noreturn))
void sdc_assertion_fail(uint32_t module_id, uint32_t line)
{
    controller_fault_handler_t fault_handler =
        *(controller_fault_handler_t volatile *)0x21000a58U;

    __disable_irq();

    if (fault_handler != 0) {
        char module_text[12];
        uint8_t digit_count = 0;
        uint32_t quotient = module_id;

        /* The controller's zero id intentionally produces an empty string.
         * For nonzero ids, count first so digits can be emitted backwards. */
        while (quotient != 0U) {
            quotient /= 10U;
            ++digit_count;
        }
        module_text[digit_count] = '\0';

        quotient = module_id;
        while (digit_count != 0U) {
            --digit_count;
            module_text[digit_count] =
                (char)('0' + ((uint8_t)quotient % 10U));
            quotient /= 10U;
        }

        fault_handler(module_text, line);
    }

    __DSB();
    volatile uint32_t *const aircr = (volatile uint32_t *)0xe000ed0cU;
    *aircr = UINT32_C(0x05fa0004) | (*aircr & UINT32_C(0x00000700));
    __DSB();

    for (;;) { }
}
