#include "g1_net_symbols.h"
/* 0x10333e4 is not a function entry.  It is the second instruction of the
 * copy loop in FUN_010333b4 (true owner extent 0x10333b4..0x10335e0).
 *
 * The fragment's live registers have these structured meanings:
 *   r3 = source cursor, r4 = destination cursor, r5 = source end.
 * Keeping a callable FUN_010333e4 would invent an ABI and lose those values.
 * This C helper documents the loop for integration into the owner; it is not
 * emitted as a firmware symbol on its own. */
#include <stdint.h>

struct g1_copy_cursor {
    const uint32_t *source;
    const uint32_t *source_end;
    uint32_t *destination;
};

static void copy_configuration_prefix(struct g1_copy_cursor *cursor)
{
    while (cursor->source != cursor->source_end) {
        cursor->destination[0] = cursor->source[0];
        cursor->destination[1] = cursor->source[1];
        cursor->source += 2;
        cursor->destination += 2;
    }
    *cursor->destination = *cursor->source;
}
