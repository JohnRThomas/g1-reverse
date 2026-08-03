#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100aaac @ 0x0100aaac
 * public-name: controller_resolved_address_matches
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_ecb_run_blocking                     <= FUN_0100a7e8 @ 0x0100a7e8
 *   controller_resolved_address_matches      <= FUN_0100aaac @ 0x0100aaac
 */
/* net-core controller_resolved_address_matches @ 0x0100aaac.
 * Raw backmap: FUN_0100aaac@0x0100aaac.
 * The four-byte prefix on storage preserves the original callee-visible
 * stack address; only the following 48-byte radio workspace is observable. */
#include <stdint.h>

extern void sdc_ecb_run_blocking(void *);

uint32_t controller_resolved_address_matches(const uint32_t *state, const uint8_t *address) {
    uint8_t storage[52];
    uint8_t *workspace = storage + 4;
    uint32_t *words = (uint32_t *)workspace;

    words[0] = state[0];
    words[1] = state[1];
    words[2] = state[2];
    words[3] = state[3];
    words[4] = 0;
    words[5] = 0;
    words[6] = 0;
    workspace[28] = 0;
    workspace[29] = address[5];
    workspace[30] = address[4];
    workspace[31] = address[3];
    sdc_ecb_run_blocking(workspace);

    return address[0] == workspace[47] &&
           address[1] == workspace[46] &&
           address[2] == workspace[45];
}
