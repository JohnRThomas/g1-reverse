/* readable reconstruction; identity: FUN_00077d30 @ 0x00077d30
 * public-name: _write_r
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_errno                                  @ 0x2000cc24
 */
/* _write_r @ 0x00077d30; raw tail_77d30 */
#include <stddef.h>

extern int write(int fd, const void *buffer,
                                 size_t count); /* FUN_0004b0dc */

int _write_r(int *reent, int fd, const void *buffer, size_t count)
{
    volatile int *system_errno = (volatile int *)0x2000cc24u;
    int result;

    *system_errno = 0;
    result = write(fd, buffer, count);
    if (result == -1 && *system_errno != 0) {
        *reent = *system_errno;
    }
    return result;
}
