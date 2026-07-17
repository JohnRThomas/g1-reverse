/* Zephyr onoff validate_args @ 0x01039b16, exact extent 0x20.
 * Raw/address backmaps:
 *   FUN_01039b16@0x01039b16
 *   sys_notify_validate = FUN_01039b88@0x01039b88
 */
#include <stdint.h>
#define validate_args FUN_01039b16

extern int FUN_01039b88(void *notification);
#define sys_notify_validate FUN_01039b88

int validate_args(const void *manager, uint8_t *client)
{
    int result;

    if (manager == 0 || client == 0) {
        return -22;
    }
    result = sys_notify_validate(client + 4);
    if (result == 0 && *(uint32_t *)(client + 8) > 3u) {
        result = -22;
    }
    return result;
}
