/* readable reconstruction; identity: FUN_00077a28 @ 0x00077a28
 * public-name: strtol_r
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strtol_r                                 <= FUN_00077a28 @ 0x00077a28
 *   thunk_FUN_00071678                       <= FUN_000807f2 @ 0x000807f2
 * address symbols (name @ address):
 *   rodata_f8a6b                             @ 0x000f8a6b
 */
/* Reconstructed FUN_00077a28 @ 0x00077a28 (_strtol_r).
 * Exact configured newlib owner; extent 0x000000f8.
 */
#include <stdint.h>
extern int *thunk_FUN_00071678(void); /* __errno */

long strtol_r(int *reent, const char *text, char **end, int base)
{
    const uint8_t *classes = (const uint8_t *)0x000f8a6bU;
    const uint8_t *scan = (const uint8_t *)text;
    uint32_t value = 0;
    int any = 0;
    int negative = 0;
    int character;
    if ((unsigned)base > 36U || base == 1) {
        *thunk_FUN_00071678() = 22;
        return 0;
    }
    do character = *scan++; while ((classes[character] & 8U) != 0U);
    if (character == '-') {
        negative = 1;
        character = *scan++;
    } else if (character == '+') {
        character = *scan++;
    }
    if ((base == 0 || base == 16) && character == '0' &&
        ((*scan & 0xdfU) == 'X')) {
        character = scan[1];
        scan += 2;
        base = 16;
    }
    if (base == 0) base = character == '0' ? 8 : 10;
    uint32_t limit = negative ? 0x80000000U : 0x7fffffffU;
    uint32_t cutoff = limit / (uint32_t)base;
    uint32_t cutlim = limit % (uint32_t)base;
    for (;;) {
        int digit;
        if (character >= '0' && character <= '9') digit = character - '0';
        else if (character >= 'A' && character <= 'Z') digit = character - 'A' + 10;
        else if (character >= 'a' && character <= 'z') digit = character - 'a' + 10;
        else break;
        if (digit >= base) break;
        if (any < 0 || value > cutoff ||
            (value == cutoff && (uint32_t)digit > cutlim)) any = -1;
        else { any = 1; value = value * (uint32_t)base + (uint32_t)digit; }
        character = *scan++;
    }
    if (any < 0) {
        value = limit;
        *reent = 34;
    } else if (negative) {
        value = 0U - value;
    }
    if (end != 0)
        *end = (char *)(any != 0 ? scan - 1 : (const uint8_t *)text);
    return (long)value;
}
