/* readable reconstruction; identity: FUN_0103966e @ 0x0103966e
 * public-name: FUN_0103966e
 * durable-map: recon/catalogs/function_names_net.json
 */
/* cbpprintf_external @ 0x0103966e; raw FUN_0103966e
 * Exact NCS 2.5.1 Zephyr cbprintf packaged-output helper.
 */
#include <stdint.h>

#define cbpprintf_external FUN_0103966e

typedef int (*cbprintf_formatter)(void *, void *, const char *, void *);

extern unsigned int strlen(const char *); /* FUN_0102a268 */

int cbpprintf_external(void *output, cbprintf_formatter formatter,
                       void *context, uint8_t *package)
{
    if (!package) {
        return -22;
    }

    unsigned int string_count = package[1];
    uint8_t *text = package + package[0] * 4u +
                    package[2] + package[3] * 2u;

    for (unsigned int index = 0; index < string_count; ++index) {
        unsigned int argument_index = *text++;

        *(uint8_t **)(package + argument_index * 4u) = text;
        text += strlen((const char *)text) + 1u;
    }

    return formatter(output, context, *(const char **)(package + 4),
                     package + 8);
}
