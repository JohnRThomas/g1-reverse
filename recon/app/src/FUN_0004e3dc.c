/* Reconstructed FUN_0004e3dc @ 0x4e3dc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
struct settings_store_recon;
void FUN_0004e3dc(struct settings_store_recon *store) {
    *(struct settings_store_recon * volatile *)0x2000a100UL = store;
}
