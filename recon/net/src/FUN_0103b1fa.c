/* CPUNET Zephyr k_queue_append @ 0x0103b1fa.
 * Raw/address back-map: FUN_0103b1fa / 0x0103b1fa.
 */
#include <stdint.h>

extern int32_t queue_insert(void *, void *, void *, int, int); /* FUN_01036660 */
#define k_queue_append FUN_0103b1fa

void k_queue_append(void *queue, void *data)
{
    (void)queue_insert(queue, 0, data, 0, 1);
}
