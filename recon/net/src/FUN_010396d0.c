/* Zephyr cbprintf is_ptr @ 0x010396d0, exact extent 0x4a.
 * Raw/address backmap: FUN_010396d0@0x010396d0. */
#include <stdbool.h>
#define is_ptr FUN_010396d0

bool is_ptr(const char *format, int argument_index)
{
    char character;
    bool in_conversion = false;
    int index = 0;

    while ((character = *format++) != '\0') {
        if (in_conversion) {
            if (index == argument_index) {
                if (character == 'p') {
                    return true;
                }
                if (character >= 64 && character <= 122) {
                    return false;
                }
            } else if (character >= 64 && character <= 122) {
                ++index;
                in_conversion = false;
            }
        }
        if (character == '%') {
            in_conversion = !in_conversion;
        }
    }
    return false;
}
