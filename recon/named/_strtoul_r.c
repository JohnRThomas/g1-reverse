/* readable reconstruction; identity: FUN_00077b38 @ 0x00077b38
 * public-name: _strtoul_r
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_f8a6b                             @ 0x000f8a6b
 */
/* _strtoul_r @ 0x00077b38; raw FUN_00077b38 */
#include <stdint.h>

unsigned long _strtoul_r(int *reent, const char *text, char **end, int base)
{
    const uint8_t *class_table = (const uint8_t *)0x000f8a6bu;
    const uint8_t *scan = (const uint8_t *)text;
    uint32_t value;
    uint32_t cutoff;
    int cutlim;
    int any;
    int negative = 0;
    int character;

    do {
        character = *scan++;
    } while ((class_table[character] & 8u) != 0u);

    if (character == '-') {
        negative = 1;
        character = *scan++;
    } else if (character == '+') {
        character = *scan++;
    }
    if ((base == 0 || base == 16) && character == '0' &&
        ((*scan & 0xdfu) == 'X')) {
        character = scan[1];
        scan += 2;
        base = 16;
    }
    if (base == 0) {
        base = character == '0' ? 8 : 10;
    }

    cutoff = UINT32_MAX / (uint32_t)base;
    cutlim = (int)(UINT32_MAX % (uint32_t)base);
    value = 0;
    any = 0;
    for (;;) {
        int digit;

        if (character >= '0' && character <= '9') {
            digit = character - '0';
        } else if (character >= 'A' && character <= 'Z') {
            digit = character - 'A' + 10;
        } else if (character >= 'a' && character <= 'z') {
            digit = character - 'a' + 10;
        } else {
            break;
        }
        if (digit >= base) {
            break;
        }
        if (any < 0 || value > cutoff ||
            (value == cutoff && digit > cutlim)) {
            any = -1;
        } else {
            any = 1;
            value = value * (uint32_t)base + (uint32_t)digit;
        }
        character = *scan++;
    }

    if (any < 0) {
        value = UINT32_MAX;
        *reent = 34;
    } else if (negative) {
        value = 0u - value;
    }
    if (end != 0) {
        *end = (char *)(any != 0 ? scan - 1 : (const uint8_t *)text);
    }
    return value;
}
