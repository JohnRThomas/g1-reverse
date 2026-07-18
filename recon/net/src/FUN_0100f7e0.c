/* CPUNET LL-control opcode classifier @ 0x0100f7e0.
 * Raw back-map: FUN_0100f7e0@0x0100f7e0; true executable extent 0x1e. */
#include <stdint.h>

/* Returns whether an LL-control opcode belongs to either of the two
 * controller ranges handled by the connection-event timing path. */
unsigned FUN_0100f7e0(unsigned opcode)
{
    return ((opcode - 0x0bu) <= 4u ||
            (opcode - 0x21u) <= 6u || opcode == 0x2fu);
}
