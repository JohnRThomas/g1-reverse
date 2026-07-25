/* Literal pool for FUN_0100eec8, net VA [0x0100ef04,0x0100ef08). */
#include <stdint.h>
/* P4 iteration 26 - RELOCATION-AWARE.  This literal pool holds a CPUNET RAM
   POINTER, and the structural pass moved the pointed-to recovered object into a
   g1_net_ram_relocs.c storage block.  Left as the raw original-image address the
   table and the linker pin for the SAME object would disagree (the pin follows
   the block, the table would not), so the cohesive build takes the relocated
   address while the byte-match path keeps the shipped word verbatim. */
#include "g1_net_ram_reloc.h"
const uint32_t rodata_0x100ef04[1]={(uint32_t)G1N_21000ec8};
