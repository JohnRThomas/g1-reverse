/* net-core FUN_01008d00 @ 0x1008d00 */
#include <stdint.h>

typedef void (*panic_print_fn)(const char *);

__attribute__((noreturn)) void FUN_01008d00(uint32_t reason)
{
    panic_print_fn print = *(panic_print_fn volatile *)0x21000a58U;
    if (print != 0) {
        char text[12];
        unsigned length = 0;
        uint32_t n = reason;
        do {
            ++length;
            n /= 10U;
        } while (n != 0);
        text[length] = '\0';
        n = reason;
        while (length != 0) {
            text[--length] = (char)('0' + n % 10U);
            n /= 10U;
        }
        print(text);
    }

    volatile uint32_t *aircr = (volatile uint32_t *)0xe000ed0cU;
    *aircr = 0x05fa0004U | (*aircr & 0x700U);
    for (;;) { }
}
