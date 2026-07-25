/* net-core FUN_010337ac @ 0x10337ac  (P4 iteration 24; parity 300/300 trials, 0 mismatches) */
/* CPUNET ESB receive-FIFO pop @ 0x010337ac  (`esb_read_rx_payload`).
 * Raw back-map: FUN_010337ac@0x010337ac; true extent 0xa2 (a `nop` pad then
 * the literal pool 0x01033850 = 0x21006459, 0x01033854 = 0x21004a34).
 *
 * The FIFO object at 0x21004a34 is the one FUN_010333b4 primes: eight entry
 * pointers 0x21005256 + 0x100*i at +0x00..+0x1c, the read index at +0x24 and
 * the pending count at +0x28.  Each entry is an ESB payload header
 * { length, pipe, rssi(signed), noack, pid } followed by the data at +5.
 */
#include <stdint.h>

extern void FUN_0103b614(void *destination, const void *source,
                         unsigned int length);

int FUN_010337ac(uint8_t *payload)
{
    volatile uint8_t *const enabled = (volatile uint8_t *)0x21006459u;
    volatile uint8_t *volatile *const entries =
        (volatile uint8_t *volatile *)0x21004a34u;
    volatile uint32_t *const read_index =
        (volatile uint32_t *)(0x21004a34u + 0x24u);
    volatile int32_t *const pending =
        (volatile int32_t *)(0x21004a34u + 0x28u);
    uint32_t basepri;
    uint32_t length;
    uint32_t next;

    if (*enabled == 0)
        return -13;
    if (payload == 0)
        return -22;
    if (*pending == 0)
        return -61;

    __asm__ volatile ("mrs %0, basepri" : "=r" (basepri));
    __asm__ volatile ("msr basepri_max, %0" :: "r" (0x40u) : "memory");
    __asm__ volatile ("isb 0xf" ::: "memory");

    length = entries[*read_index][0];
    payload[0] = (uint8_t)length;
    payload[1] = entries[*read_index][1];
    payload[2] = (uint8_t)(int8_t)entries[*read_index][2];
    payload[4] = entries[*read_index][4];
    payload[3] = entries[*read_index][3];
    FUN_0103b614(payload + 5, (const void *)(entries[*read_index] + 5), length);

    next = *read_index + 1u;
    if (next >= 8u)
        next = 0u;
    *read_index = next;
    *pending = *pending - 1;

    __asm__ volatile ("msr basepri, %0" :: "r" (basepri) : "memory");
    __asm__ volatile ("isb 0xf" ::: "memory");
    return 0;
}
