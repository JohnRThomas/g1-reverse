/* net-core FUN_0102b49c @ 0x102b49c  (P4 iteration 24; parity 300/300 trials, 0 mismatches (call_arity_by_target)) */
/* CPUNET ESB peer-sync ANNOUNCE-RESPONSE builder @ 0x0102b49c.
 * Raw back-map: FUN_0102b49c@0x0102b49c; true extent 0x60 (literal pool
 * 0x0102b4fc..0x0102b50c).  Reached only from the ESB event handler
 * FUN_0102b50c when an RX payload whose byte 5 is 0x11 arrives while this
 * lens is the PTX/master side.  Same shape as FUN_0102b3f0's fallback
 * branch but with its own staging packet at 0x21004ea1 and the fixed
 * sub-type 0x11.
 */
#include <stdint.h>

extern void FUN_0103b62e(void *destination, int value, unsigned int length);
extern void FUN_0103b614(void *destination, const void *source,
                         unsigned int length);
extern int FUN_01033660(void *packet);
extern int FUN_01033858(void);
extern void FUN_01039722(int format);

void FUN_0102b49c(void)
{
    volatile uint8_t *const packet = (volatile uint8_t *)0x21004ea1u;
    volatile int *const log_level = (volatile int *)0x21000580u;
    struct {
        uint32_t header;
        uint8_t tail[247];
    } scratch;

    scratch.header = 0;
    FUN_0103b62e(scratch.tail, 0, sizeof(scratch.tail));
    packet[1] = 0;
    packet[3] = 0;
    *(uint8_t *)&scratch.header = 0x11u;
    FUN_0103b614((void *)(packet + 5), &scratch, 0xfbu);
    packet[0] = 0xfbu;
    if (FUN_01033660((void *)packet) != 0 && *log_level > 0)
        FUN_01039722(0x103d15d);          /* "esb_write_payload failed" */
    if (FUN_01033858() != 0 && *log_level > 0)
        FUN_01039722(0x103d177);          /* "esb_start_tx failed" */
}
