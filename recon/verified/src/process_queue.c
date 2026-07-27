/* process_queue @ 0x00082114; raw FUN_00082114.
 * NCS 2.5.1 Bluetooth ATT queue helper, CONFIG_BT_EATT=n. */
#include <stdint.h>
extern void* net_buf_get(void*, unsigned long, unsigned long, unsigned long); /*=0x000836e8*/
extern int bt_att_chan_send(void *channel, void *buffer); /*=0x00058a54*/
extern void k_queue_prepend(void *queue, void *buffer); /*=0x00086518*/
int process_queue(void *channel, void *queue)
{
    void *buffer = net_buf_get(queue, queue, 0, 0);
    if (buffer == 0) {
        return -2;
    }
    int error = bt_att_chan_send(channel, buffer);
    if (error != 0) {
        k_queue_prepend(queue, buffer);
    }
    return error;
}
