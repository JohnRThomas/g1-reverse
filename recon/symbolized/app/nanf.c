#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00076a88 @ 0x00076a88
 * public-name: nanf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nanf                                     <= FUN_00076a88 @ 0x00076a88
 */
/* Reconstructed FUN_00076a88 @ 0x76a88 (CFG-directed: 80/80 PASS).
 *
 * This is newlib's nanf(const char *tagp) leaf.  The tag is accepted for the
 * public ABI but this implementation returns the canonical quiet-NaN bits.
 */
#include <stdint.h>

float nanf(const char *tagp)
{
    union {
        uint32_t bits;
        float value;
    } result = { 0x7fc00000u };

    (void)tagp;
    return result.value;
}
